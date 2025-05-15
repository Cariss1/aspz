#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>

#define NUM_PROCESSES 5
#define NUM_WRITES 10
#define USE_APPEND 1  // 1 = з O_APPEND, 0 = без

void write_data(int fd, int id) {
    char buffer[64];
    for (int i = 0; i < NUM_WRITES; i++) {
        snprintf(buffer, sizeof(buffer), "Process %d, line %d\n", id, i);
        write(fd, buffer, strlen(buffer));
        usleep(10000);  // Затримка для імітації змагання
    }
}

int main() {
    int flags = O_WRONLY | O_CREAT;
    if (USE_APPEND) {
        flags |= O_APPEND;
    }

    int fd = open("output.txt", flags, 0644);
    if (fd < 0) {
        perror("open");
        exit(1);
    }

    for (int i = 0; i < NUM_PROCESSES; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            write_data(fd, i);
            close(fd);
            exit(0);
        }
    }

    for (int i = 0; i < NUM_PROCESSES; i++) {
        wait(NULL);
    }

    close(fd);
    return 0;
}
