#include <stdio.h>
#include <stdlib.h>

int main() {
    size_t huge_size = (size_t) -1; // максимально можливий розмір
    int *ptr = malloc(10 * sizeof(int));

    if (!ptr) {
        printf("Помилка malloc\n");
        return 1;
    }

    int *tmp = realloc(ptr, huge_size); // ймовірно зазнає невдачі

    if (tmp == NULL) {
        printf("realloc не вдалося: пам’ять не виділено\n");
        // старий ptr все ще дійсний — звільняємо
        free(ptr);
    } else {
        ptr = tmp;
        printf("Пам’ять успішно перевиділена\n");
        free(ptr);
    }

    return 0;
}
