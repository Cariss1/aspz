#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/user.h>
#include <sys/reg.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <elf.h>
#include <fcntl.h>
#include <sys/uio.h>

#define MAX_STACK_TRACE 20

// Структура для зберігання інформації про падіння
typedef struct {
    int signal;
    void* ip;
    void* bp;
    void* sp;
    void* stack_dump[20];
    int stack_depth;
} crash_info_t;

// Функція для отримання символу з адреси (спрощена версія)
const char* addr_to_symbol(void* addr) {
    static char buf[256];
    snprintf(buf, sizeof(buf), "%p", addr);
    return buf;
}

// Функція для зчитування пам'яті процесу
long read_process_memory(pid_t pid, void* addr) {
    return ptrace(PTRACE_PEEKDATA, pid, addr, NULL);
}

// Функція для збору stack trace
void collect_stack_trace(pid_t pid, crash_info_t* info) {
    struct user_regs_struct regs;
    
    // Отримуємо регістри процесу
    if (ptrace(PTRACE_GETREGS, pid, NULL, &regs) == -1) {
        perror("ptrace(GETREGS) failed");
        return;
    }

    info->ip = (void*)regs.rip;
    info->bp = (void*)regs.rbp;
    info->sp = (void*)regs.rsp;

    // Спрощений збір стеку (для x86_64)
    void* stack_ptr = info->bp;
    info->stack_depth = 0;

    for (int i = 0; i < MAX_STACK_TRACE && stack_ptr != NULL; i++) {
        long ret_addr = read_process_memory(pid, stack_ptr + sizeof(void*));
        if (ret_addr == -1 && errno != 0) break;
        
        info->stack_dump[i] = (void*)ret_addr;
        info->stack_depth++;
        
        long next_bp = read_process_memory(pid, stack_ptr);
        if (next_bp == -1 && errno != 0) break;
        
        stack_ptr = (void*)next_bp;
    }
}

// Функція для обробки падіння
void handle_crash(pid_t pid, int status, crash_info_t* info) {
    info->signal = WSTOPSIG(status);
    
    // Збираємо інформацію про стан процесу
    collect_stack_trace(pid, info);
    
    // Виводимо інформацію про падіння
    printf("\n=== Process Crash Report ===\n");
    printf("Signal: %d (%s)\n", info->signal, strsignal(info->signal));
    printf("Instruction Pointer: %s\n", addr_to_symbol(info->ip));
    printf("Stack Pointer: %s\n", addr_to_symbol(info->sp));
    printf("Base Pointer: %s\n", addr_to_symbol(info->bp));
    
    printf("\nStack Trace:\n");
    for (int i = 0; i < info->stack_depth; i++) {
        printf("#%-2d %s\n", i, addr_to_symbol(info->stack_dump[i]));
    }
    printf("==========================\n\n");
}

// Основна функція трасування
void trace_process(pid_t pid) {
    int status;
    crash_info_t crash_info;
    
    // Починаємо трасування
    if (ptrace(PTRACE_SEIZE, pid, NULL, NULL) == -1) {
        perror("ptrace(SEIZE) failed");
        exit(EXIT_FAILURE);
    }
    
    // Очікуємо зупинки процесу
    waitpid(pid, &status, 0);
    
    // Налаштовуємо ptrace для отримання сигналів
    if (ptrace(PTRACE_SETOPTIONS, pid, NULL, 
              PTRACE_O_TRACECLONE |
              PTRACE_O_TRACEEXIT |
              PTRACE_O_TRACEEXEC |
              PTRACE_O_TRACESYSGOOD) == -1) {
        perror("ptrace(SETOPTIONS) failed");
        exit(EXIT_FAILURE);
    }
    
    // Продовжуємо виконання процесу
    ptrace(PTRACE_CONT, pid, NULL, NULL);
    
    // Основний цикл трасування
    while (1) {
        waitpid(pid, &status, 0);
        
        if (WIFEXITED(status)) {
            printf("Process exited with status %d\n", WEXITSTATUS(status));
            break;
        }
        
        if (WIFSIGNALED(status)) {
            printf("Process terminated by signal %d\n", WTERMSIG(status));
            break;
        }
        
        if (WIFSTOPPED(status)) {
            int sig = WSTOPSIG(status);
            
            if (sig == SIGTRAP) {
                // Обробка точок зупинки
                ptrace(PTRACE_CONT, pid, NULL, NULL);
            } else {
                // Обробка інших сигналів
                handle_crash(pid, status, &crash_info);
                ptrace(PTRACE_CONT, pid, NULL, sig);
            }
        }
    }
}

int main(int argc, char** argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <program> [args...]\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    pid_t pid = fork();
    
    if (pid == -1) {
        perror("fork failed");
        return EXIT_FAILURE;
    }
    
    if (pid == 0) {
        // Дочірній процес
        ptrace(PTRACE_TRACEME, 0, NULL, NULL);
        execvp(argv[1], &argv[1]);
        perror("execvp failed");
        exit(EXIT_FAILURE);
    } else {
        // Батьківський процес (трасувальник)
        trace_process(pid);
    }
    
    return EXIT_SUCCESS;
}