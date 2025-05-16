#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <pwd.h>

int is_executable_by_user(const char *path) {
    struct stat st;
    return (stat(path, &st) == 0) && (st.st_mode & S_IXUSR) && S_ISREG(st.st_mode);
}

void grant_read_permission(const char *path) {
    struct stat st;
    if (stat(path, &st) != 0) {
        perror("stat");
        return;
    }

    // Додаємо дозвіл на читання для "інших"
    mode_t new_mode = st.st_mode | S_IROTH;
    if (chmod(path, new_mode) != 0) {
        perror("chmod");
    } else {
        printf("Дозвіл на читання надано: %s\n", path);
    }
}

int main() {
    // Отримати домашній каталог користувача
    const char *home = getenv("HOME");
    if (!home) {
        struct passwd *pw = getpwuid(getuid());
        if (pw) home = pw->pw_dir;
        else {
            fprintf(stderr, "Неможливо визначити домашній каталог.\n");
            return 1;
        }
    }

    DIR *dir = opendir(home);
    if (!dir) {
        perror("opendir");
        return 1;
    }

    struct dirent *entry;
    char filepath[1024];

    while ((entry = readdir(dir)) != NULL) {
        snprintf(filepath, sizeof(filepath), "%s/%s", home, entry->d_name);

        if (is_executable_by_user(filepath)) {
            printf("Знайдено виконуваний файл: %s\nНадати іншим дозвіл на читання? (y/n): ", filepath);
            char response[4];
            if (fgets(response, sizeof(response), stdin)) {
                if (response[0] == 'y' || response[0] == 'Y') {
                    grant_read_permission(filepath);
                }
            }
        }
    }

    closedir(dir);
    return 0;
}
