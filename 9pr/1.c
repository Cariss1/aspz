#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>

#define UID_THRESHOLD 1000  // Змініть на 500, якщо ваш дистрибутив так визначає звичайних користувачів

int main() {
    FILE *fp = popen("getent passwd", "r");
    if (!fp) {
        perror("popen");
        return 1;
    }

    uid_t current_uid = getuid();
    struct passwd *current_user = getpwuid(current_uid);
    if (!current_user) {
        perror("getpwuid");
        return 1;
    }

    char line[1024];
    int found = 0;

    while (fgets(line, sizeof(line), fp)) {
        char *username = strtok(line, ":");
        strtok(NULL, ":"); // skip password placeholder
        char *uid_str = strtok(NULL, ":");

        if (!username || !uid_str)
            continue;

        uid_t uid = (uid_t)atoi(uid_str);

        if (uid >= UID_THRESHOLD && uid != current_uid) {
            printf("Знайдено іншого звичайного користувача: %s (UID: %d)\n", username, uid);
            found = 1;
        }
    }

    pclose(fp);

    if (!found) {
        printf("Інших звичайних користувачів (UID > %d) не знайдено.\n", UID_THRESHOLD);
    }

    return 0;
}
