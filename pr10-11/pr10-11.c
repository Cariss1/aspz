#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    int i, status;

    for (i = 1; i <= 5; i++) {
        pid = fork(); // Створюємо дочірній процес

        if (pid == -1) {
            perror("fork failed");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Це дочірній процес
            printf("Дочірній процес %d (PID: %d)\n", i, getpid());
            sleep(1); // Невелика затримка для демонстрації
            exit(i);  // Завершуємо процес з кодом, що дорівнює номеру
        }
    }

    // Це батьківський процес
    for (i = 1; i <= 5; i++) {
        pid = wait(&status); // Очікуємо завершення будь-якого дочірнього процесу
        
        if (WIFEXITED(status)) {
            printf("Дочірній процес %d (PID: %d) завершився з кодом %d\n", 
                   WEXITSTATUS(status), pid, WEXITSTATUS(status));
        }
    }

    printf("Усі дочірні процеси завершили роботу. Батьківський процес (PID: %d) завершується.\n", getpid());
    return 0;
}