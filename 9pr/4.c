#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("Виконання команди whoami:\n");
    int status_whoami = system("whoami");

    if (status_whoami != 0) {
        fprintf(stderr, "Помилка під час виконання whoami\n");
    }

    printf("\nВиконання команди id:\n");
    int status_id = system("id");

    if (status_id != 0) {
        fprintf(stderr, "Помилка під час виконання id\n");
    }

    return 0;
}
