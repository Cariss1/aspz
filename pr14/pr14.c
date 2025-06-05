#include <stdio.h>
#include <time.h>
#include <unistd.h> // для sleep()

void countdown(int seconds) {
    time_t start_time = time(NULL);
    time_t end_time = start_time + seconds;
    time_t remaining;
    
    while ((remaining = end_time - time(NULL)) > 0) {
        printf("\033[2K\r");
        
        // Виводимо час у форматі HH:MM:SS
        int hours = remaining / 3600;
        int mins = (remaining % 3600) / 60;
        int secs = remaining % 60;
        
        printf("Залишилось: %02d:%02d:%02d", hours, mins, secs);
        fflush(stdout); // Важливо для негайного виведення
        
        sleep(1); // Затримка на 1 секунду
    }
    
    printf("\nПодія настала!\n");
}

int main() {
    int duration;
    printf("Введіть тривалість відліку в секундах: ");
    scanf("%d", &duration);
    
    countdown(duration);
    
    return 0;
}