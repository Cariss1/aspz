#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    size_t size = 1024 * 1024 * 100; // 100 MB
    void *blocks[100];
    int i;

    for (i = 0; i < 100; i++) {
        blocks[i] = malloc(size);
        if (blocks[i] == NULL) {
            printf("malloc failed at iteration %d (%.2f GB allocated)\n", i, i * 0.1);
            break;
        } else {
            memset(blocks[i], 0, size); // форсуємо фізичне виділення
            printf("Allocated block %d (%.2f GB)\n", i + 1, (i + 1) * 0.1);
        }
    }

    // очищення
    for (int j = 0; j < i; j++) {
        free(blocks[j]);
    }

    return 0;
}
