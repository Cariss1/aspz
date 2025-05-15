#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    const char filename[] = "testfile.bin";
    unsigned char data[] = {4, 5, 2, 2, 3, 3, 7, 9, 1, 5};
    unsigned char buffer[4];

    // Створюємо файл з байтами
    int fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd == -1) { perror("open"); return 1; }
    write(fd, data, sizeof(data));
    close(fd);

    // Відкриваємо для читання
    fd = open(filename, O_RDONLY);
    if (fd == -1) { perror("open"); return 1; }

    // lseek + read
    if (lseek(fd, 3, SEEK_SET) == -1) {
        perror("lseek");
        return 1;
    }

    if (read(fd, buffer, 4) != 4) {
        perror("read");
        return 1;
    }

    close(fd);

    printf("Прочитано: ");
    for (int i = 0; i < 4; i++) {
        printf("%d ", buffer[i]);
    }
    printf("\n");

    return 0;
}
