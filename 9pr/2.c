#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("Спроба прочитати /etc/shadow через sudo...\n");

    int status = system("sudo cat /etc/shadow");

    if (status == -1) {
        perror("system");
        return 1;
    }

    if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
        printf("Команда завершилась з кодом помилки: %d\n", WEXITSTATUS(status));
        return 1;
    }

    return 0;
}
