#include <stdlib.h>

struct sbar {
    int x;
    double y;
};

int main() {
    struct sbar *ptr, *newptr;

    // calloc для ініціалізації
    ptr = calloc(1000, sizeof(struct sbar));

    // більш безпечне виділення: перевірка переповнення
    newptr = reallocarray(ptr, 500, sizeof(struct sbar));

    if (!newptr) {
        // пам'ять не виділено — ptr залишається дійсним
        free(ptr);
        return 1;
    }

    // далі можна працювати з newptr
    free(newptr);
    return 0;
}
