#include <stdio.h>
#include <stdlib.h>

int main() {
    // realloc з NULL
    int *p1 = realloc(NULL, 100 * sizeof(int));
    if (p1 != NULL) {
        printf("realloc(NULL, size): успіх, пам’ять виділена\n");
        free(p1);
    } else {
        printf("realloc(NULL, size): помилка виділення\n");
    }

    // realloc з розміром 0
    int *p2 = malloc(50 * sizeof(int));
    int *p3 = realloc(p2, 0);
    if (p3 == NULL) {
        printf("realloc(ptr, 0): пам’ять звільнена, повернуто NULL\n");
    } else {
        printf("realloc(ptr, 0): реалізація повернула непорожній вказівник (НЕБЕЗПЕЧНО)\n");
        free(p3); // на всяк випадок
    }

    return 0;
}
