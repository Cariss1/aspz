#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int main() {
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Робимо pipe непровідним (обмежений буфер)
    fcntl(pipefd[1], F_SETFL, O_NONBLOCK);

    char buffer[65536]; // 64 KB
    memset(buffer, 'A', sizeof(buffer));

    ssize_t count = write(pipefd[1], buffer, sizeof(buffer));
    if (count == -1) {
        perror("write failed");
    } else if (count < sizeof(buffer)) {
        printf("Частковий запис: лише %zd байт з %zu\n", count, sizeof(buffer));
    } else {
        printf("Повний запис %zd байт\n", count);
    }

    return 0;
}
