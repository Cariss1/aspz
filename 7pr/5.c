#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

void list_files(const char *path) {
    DIR *dir = opendir(path);
    if (!dir) {
        perror(path);
        return;
    }

    struct dirent *entry;
    char fullpath[1024];

    while ((entry = readdir(dir)) != NULL) {
        // Пропускаємо . і ..
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);

        struct stat st;
        if (stat(fullpath, &st) == -1) {
            perror(fullpath);
            continue;
        }

        if (S_ISDIR(st.st_mode)) {
            // Каталог: вивести та перейти вглиб
            printf("[Каталог] %s\n", fullpath);
            list_files(fullpath);  // Рекурсивно обходимо
        } else {
            // Файл
            printf("  %s\n", fullpath);
        }
    }

    closedir(dir);
}

int main() {
    const char *start_path = ".";
    list_files(start_path);
    return 0;
}
