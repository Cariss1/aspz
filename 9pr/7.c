#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pwd.h>
#include <stdbool.h>

bool is_system_user(struct passwd *pw) {
    // Перевірка shell
    if (pw->pw_shell && 
        (strstr(pw->pw_shell, "nologin") || 
         strstr(pw->pw_shell, "false") || 
         strlen(pw->pw_shell) == 0)) {
        return true;
    }

    // Перевірка домашнього каталогу
    if (pw->pw_dir && 
        (strstr(pw->pw_dir, "/nonexistent") || 
         strstr(pw->pw_dir, "/var") ||
         strcmp(pw->pw_dir, "/") == 0)) {
        return true;
    }

    // Перевірка імені користувача
    if (strncmp(pw->pw_name, "systemd-", 8) == 0 ||
        strcmp(pw->pw_name, "daemon") == 0 ||
        strcmp(pw->pw_name, "nobody") == 0) {
        return true;
    }

    return false;
}

int main() {
    struct passwd *pw;
    setpwent(); // початок перегляду /etc/passwd

    printf("Виявлення системних користувачів за нестандартними критеріями:\n");

    while ((pw = getpwent()) != NULL) {
        if (is_system_user(pw)) {
            printf("%s (shell: %s, home: %s)\n",
                   pw->pw_name,
                   pw->pw_shell,
                   pw->pw_dir);
        }
    }

    endpwent(); // завершення перегляду

    return 0;
}
