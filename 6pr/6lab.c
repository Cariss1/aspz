#include <stdio.h>

int main() {
    int arr[5] = {10, 20, 30, 40, 50};

    // Читання поза межами масиву — переповнення
    for (int i = 0; i <= 5; i++) {
        printf("arr[%d] = %d\n", i, arr[i]);  // arr[5] — ПЕРЕПОВНЕННЯ
    }

    return 0;
}
