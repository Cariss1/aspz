#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <string.h>
#include <unistd.h>

int main() {
    size_t size = 100 * 1024 * 1024; // 100 MB
    void *mem = malloc(size);
    if (!mem) {
        perror("malloc");
        return 1;
    }

    memset(mem, 0, size);

    if (mlock(mem, size) == 0) {
        printf("Успішно зафіксовано %zu байт у пам’яті\n", size);
    } else {
        perror("mlock");
    }

    pause(); // чекаємо, щоб перевірити top або pmap

    free(mem);
    return 0;
}
