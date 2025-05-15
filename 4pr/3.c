#include <stdio.h>
#include <stdlib.h>

void test_malloc_zero() {
    void *ptr = malloc(0);
    printf("malloc(0) returned: %p\n", ptr);

    if (ptr == NULL) {
        printf("Pointer is NULL\n");
    } else {
        printf("Pointer is NOT NULL (can be passed to free)\n");
        free(ptr); // Коректно, навіть якщо ptr != NULL
    }
}

int main() {
    test_malloc_zero();
    return 0;
}