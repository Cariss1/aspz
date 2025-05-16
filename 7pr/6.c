#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/dirent.h>

#define MAX_ITEMS 1024

int is_directory(const char *path) {
    struct stat st;
    return (stat(path, &st) == 0 && S_ISDIR(st.st_mode));
}

int compare(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

int main() {
    DIR *dir = opendir(".");
    if (!dir) {
        perror("opendir");
        return 1;
    }

    struct dirent *entry;
    char *dirs[MAX_ITEMS];
    int count = 0;

    while ((entry = readdir(dir)) != NULL && count < MAX_ITEMS) {
        if (entry->d_type == DT_DIR &&
            strcmp(entry->d_name, ".") != 0 &&
            strcmp(entry->d_name, "..") != 0) {
            
            if (is_directory(entry->d_name)) {
                dirs[count] = strdup(entry->d_name);
                count++;
            }
        }
    }

    closedir(dir);

    qsort(dirs, count, sizeof(char *), compare);

    printf("Підкаталоги (у алфавітному порядку):\n");
    for (int i = 0; i < count; i++) {
        printf("%s\n", dirs[i]);
        free(dirs[i]);
    }

    return 0;
}
