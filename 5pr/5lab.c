#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  // для sleep

int main() {
    const size_t block_size = 1024; // 1 KB
    while (1) {
        void *ptr = malloc(block_size);
        if (!ptr) {
            perror("malloc failed");
            break;
        }

        // "Лінива" ініціалізація - не чіпаємо пам’ять
        // Не memset(ptr, 0, block_size)!

        usleep(1000); // затримка 1 мс для уповільнення виділення
    }

    return 0;
}
