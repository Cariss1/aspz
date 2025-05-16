#include <stdio.h>
#include <stdlib.h>

#define LINES_PER_PAGE 20
#define MAX_LINE 1024

void show_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror(filename);
        return;
    }

    char line[MAX_LINE];
    int line_count = 0;

    while (fgets(line, sizeof(line), file)) {
        fputs(line, stdout);
        line_count++;

        if (line_count >= LINES_PER_PAGE) {
            printf("-- Натисніть Enter для продовження --");
            while (getchar() != '\n');  // Очікування натискання Enter
            line_count = 0;
        }
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Використання: %s <файл1> [файл2 ...]\n", argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; ++i) {
        printf("======== %s ========\n", argv[i]);
        show_file(argv[i]);
    }

    return 0;
}
