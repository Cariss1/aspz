#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>

int is_regular_file(const char *path) {
    struct stat st;
    return (stat(path, &st) == 0 && S_ISREG(st.st_mode));
}

int main() {
    DIR *dir = opendir(".");
    if (!dir) {
        perror("opendir");
        return 1;
    }

    struct dirent *entry;
    char answer[4];

    while ((entry = readdir(dir)) != NULL) {
        const char *name = entry->d_name;

        // Пропускаємо "." і ".."
        if (strcmp(name, ".") == 0 || strcmp(name, "..") == 0)
            continue;

        if (is_regular_file(name)) {
            printf("Видалити файл '%s'? (y/n): ", name);
            if (fgets(answer, sizeof(answer), stdin)) {
                if (answer[0] == 'y' || answer[0] == 'Y') {
                    if (remove(name) == 0) {
                        printf("-> Файл видалено: %s\n", name);
                    } else {
                        perror(name);
                    }
                }
            }
        }
    }

    closedir(dir);
    return 0;
}
