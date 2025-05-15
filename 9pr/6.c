#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <errno.h>

void check_permissions(const char *dir_path) {
    printf("\n Каталог: %s\n", dir_path);

    DIR *dir = opendir(dir_path);
    if (!dir) {
        perror("opendir");
        return;
    }

    struct dirent *entry;
    char path[512];
    struct stat st;

    while ((entry = readdir(dir)) != NULL) {
        snprintf(path, sizeof(path), "%s/%s", dir_path, entry->d_name);

        if (stat(path, &st) == -1) continue;

        struct passwd *pw = getpwuid(st.st_uid);
        struct group *gr = getgrgid(st.st_gid);

        printf("\nФайл: %s\n", path);
        printf("Власник: %s, Група: %s, Права: %o\n",
               pw ? pw->pw_name : "unknown",
               gr ? gr->gr_name : "unknown",
               st.st_mode & 0777);

        if (access(path, R_OK) == 0)
            printf("Читання дозволене\n");
        else
            printf("Немає доступу на читання\n");

        if (access(path, W_OK) == 0)
            printf("Запис дозволений\n");
        else
            printf("Немає доступу на запис\n");

        if (access(path, X_OK) == 0)
            printf("Виконання дозволене\n");
        else
            printf("Немає доступу на виконання\n");
    }

    closedir(dir);
}

int main() {
    char *home = getenv("HOME");
    if (!home) {
        fprintf(stderr, "Не вдалося визначити домашній каталог\n");
        return 1;
    }

    check_permissions(home);
    check_permissions("/usr/bin");
    check_permissions("/etc");

    return 0;
}
