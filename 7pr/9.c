#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

long get_time_ms() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000L) + (tv.tv_usec / 1000L);
}

int main() {
    long start_time, end_time;

    // Початок вимірювання
    start_time = get_time_ms();

    // Фрагмент коду для вимірювання (наприклад, цикл)
    for (volatile int i = 0; i < 100000000; ++i);

    // Кінець вимірювання
    end_time = get_time_ms();

    printf("Час виконання: %ld мс\n", end_time - start_time);
    return 0;
}
