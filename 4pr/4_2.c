#include <stdio.h>
#include <stdlib.h>

int main() {
    int i = 0;
    void *ptr = NULL;

    while (i < 3) {
        // Звільнення перед перевиділенням
        if (ptr) {
            free(ptr);
            ptr = NULL;
        }

        ptr = malloc(100);
        if (!ptr) {
            perror("malloc failed");
            break;
        }

        printf("Allocated ptr = %p (iteration %d)\n", ptr, i);
        i++;
    }

    free(ptr);  // Фінальне звільнення
    return 0;
}