#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

#define FILENAME "/tmp/test_temp_file.txt"

void test_access() {
    printf("Перевірка доступу до файлу (%s)...\n", FILENAME);

    if (access(FILENAME, R_OK) == 0) {
        printf(" Можна читати файл.\n");
    } else {
        printf("Немає доступу на читання: %s\n", strerror(errno));
    }

    if (access(FILENAME, W_OK) == 0) {
        printf("Можна записувати у файл.\n");
    } else {
        printf("Немає доступу на запис: %s\n", strerror(errno));
    }
}

int main() {
    printf(" Створення файлу: %s\n", FILENAME);

    int fd = open(FILENAME, O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    write(fd, "initial content\n", 16);
    close(fd);

    printf("Файл створено звичайним користувачем.\n");

    printf("\nЗапустіть наступні команди від імені root в окремому терміналі:\n");
    printf("  chown root:root %s\n", FILENAME);
    printf("  chmod 0400 %s\n", FILENAME);
    printf("\nПісля цього знову запустіть програму, щоб перевірити доступ.\n");

    test_access();

    return 0;
}
