#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE 1000000  // кількість елементів

int cmp_int(const void *a, const void *b) {
    int x = *(const int*)a;
    int y = *(const int*)b;
    return (x > y) - (x < y); // еквівалентно x - y, але без переповнення
}

void fill_sorted(int *arr, size_t size) {
    for (size_t i = 0; i < size; i++) arr[i] = i;
}

void fill_reversed(int *arr, size_t size) {
    for (size_t i = 0; i < size; i++) arr[i] = size - i;
}

void fill_equal(int *arr, size_t size) {
    for (size_t i = 0; i < size; i++) arr[i] = 42;
}

void fill_random(int *arr, size_t size) {
    for (size_t i = 0; i < size; i++) arr[i] = rand();
}

int is_sorted(int *arr, size_t size) {
    for (size_t i = 1; i < size; i++) {
        if (arr[i-1] > arr[i]) return 0;
    }
    return 1;
}

void benchmark(const char *name, void (*filler)(int*, size_t)) {
    int *data = malloc(SIZE * sizeof(int));
    if (!data) {
        perror("malloc");
        exit(1);
    }

    filler(data, SIZE);

    clock_t start = clock();
    qsort(data, SIZE, sizeof(int), cmp_int);
    clock_t end = clock();

    double seconds = (double)(end - start) / CLOCKS_PER_SEC;

    printf("%-20s : %.3f сек. - %s\n", name, seconds, is_sorted(data, SIZE) ? "OK" : "❌ ПОМИЛКА");

    free(data);
}

int main() {
    srand((unsigned) time(NULL));

    benchmark("Відсортований", fill_sorted);
    benchmark("Обернений", fill_reversed);
    benchmark("Однакові", fill_equal);
    benchmark("Випадкові", fill_random);

    return 0;
}
