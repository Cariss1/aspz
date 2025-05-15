#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork error");
        return 1;
    }

    printf("fork() returned: %d (in process %d)\n", pid, getpid());
    return 0;
}
