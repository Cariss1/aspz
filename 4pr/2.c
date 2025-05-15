#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void test_malloc_overflow(int xa, int xb) {
    int num = xa * xb; // Може бути переповнення!
    printf("xa = %d, xb = %d\n", xa, xb);
    printf("num (signed) = %d\n", num);
    printf("num (size_t) = %zu\n", (size_t)num);

    void *ptr = malloc(num);
    if (ptr == NULL) {
        perror("malloc failed");
    } else {
        printf("malloc(%d) succeeded!\n", num);
        free(ptr);
    }
}

int main() {
    // 1. Від’ємний аргумент (перетворюється на велике size_t)
    test_malloc_overflow(-1, 1); // num = -1 → size_t = 2^64-1 (x86_64)

    // 2. Переповнення int (призводить до від’ємного num)
    test_malloc_overflow(INT_MAX, 2); // num = -2 (на 32/64-бітних)

    // 3. Велике додатнє значення (але занадто для ОС)
    test_malloc_overflow(1 << 30, 1 << 30); // num = 2^60 (ексабайт)

    return 0;
}