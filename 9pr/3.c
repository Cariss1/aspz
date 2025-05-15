#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <pwd.h>
#include <string.h>
#include <errno.h>

int main() {
    const char *source = "/tmp/test_by_user.txt";
    const char *dest_relative = "/test_copy_by_root.txt";

    // Отримуємо ім’я користувача, який запустив програму
    uid_t original_uid = getuid();
    struct passwd *pw = getpwuid(original_uid);
    if (!pw) {
        perror("getpwuid");
        return 1;
    }

    char dest[256];
    snprintf(dest, sizeof(dest), "%s%s", pw->pw_dir, dest_relative);

    printf("Копіювання %s -> %s\n", source, dest);

    int src = open(source, O_RDONLY);
    if (src < 0) {
        perror("open source");
        return 1;
    }

    int dst = open(dest, O_WRONLY | O_CREAT | O_TRUNC, 0400); // тільки для читання, root встановлює права
    if (dst < 0) {
        perror("open dest");
        close(src);
        return 1;
    }

    char buf[1024];
    ssize_t bytes;
    while ((bytes = read(src, buf, sizeof(buf))) > 0) {
        write(dst, buf, bytes);
    }

    close(src);
    close(dst);

    printf("Файл скопійовано з правами root. Спробуйте змінити або видалити його від звичайного користувача.\n");

    return 0;
}
