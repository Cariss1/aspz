#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp;
    const char *cmd = "rwho | more";

    printf("Запуск команди: %s\n\n", cmd);

    fp = popen(cmd, "r");
    if (fp == NULL) {
        perror("popen");
        return 1;
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        fputs(buffer, stdout);
    }

    int status = pclose(fp);
    printf("\nКоманда завершена з кодом: %d\n", status);

    return 0;
}
