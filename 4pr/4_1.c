#include <stdio.h>
#include <stdlib.h>

int main() {
    int i = 0;
    void *ptr = NULL;

    // Умова: 3 ітерації
    while (i < 3) {
        if (!ptr) {
            ptr = malloc(100);
            printf("Allocated ptr = %p\n", ptr);
        }

        // Імітація використання пам'яті
        if (ptr) {
            printf("Using ptr at iteration %d\n", i);
        }

        free(ptr); // Звільнення пам'яті
        i++;
    }

    return 0;
}