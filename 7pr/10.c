#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Функція для генерації випадкового числа в діапазоні [0.0, 1.0]
double random_0_1() {
    return (double)rand() / (double)RAND_MAX;
}

// Функція для генерації випадкового числа в діапазоні [0.0, n]
double random_0_n(double n) {
    return random_0_1() * n;
}

int main() {
    double n;
    int count;

    // Ініціалізуємо генератор випадкових чисел унікальним значенням (час)
    srand((unsigned int)time(NULL));

    printf("Введіть n (дійсне число > 0): ");
    if (scanf("%lf", &n) != 1 || n <= 0.0) {
        fprintf(stderr, "Помилка: некоректне значення n.\n");
        return 1;
    }

    printf("Введіть кількість чисел для генерації: ");
    if (scanf("%d", &count) != 1 || count <= 0) {
        fprintf(stderr, "Помилка: некоректна кількість.\n");
        return 1;
    }

    printf("\n(a) Числа в діапазоні [0.0, 1.0]:\n");
    for (int i = 0; i < count; ++i) {
        printf("%.6f\n", random_0_1());
    }

    printf("\n(b) Числа в діапазоні [0.0, %.2f]:\n", n);
    for (int i = 0; i < count; ++i) {
        printf("%.6f\n", random_0_n(n));
    }

    return 0;
}
