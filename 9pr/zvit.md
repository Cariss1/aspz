![image](https://github.com/user-attachments/assets/87834bf7-5fd9-432b-844d-0ce34fd2ffe6)

![image](https://github.com/user-attachments/assets/73bcf33d-e7fb-4a6c-8b27-c51b8048aa96)

![image](https://github.com/user-attachments/assets/277409ee-d02a-4d02-9595-0c6f57b3c87e)

![image](https://github.com/user-attachments/assets/db5648da-9947-4fad-a074-7fd33206467a)

UID 1000 — типовий поріг для звичайних користувачів у більшості сучасних дистрибутивів (наприклад, Ubuntu, Debian). У старіших (наприклад, CentOS 6) може бути 500.

Програма використовує popen() для запуску getent passwd і читає її вивід по рядках.

getpwuid(getuid()) використовується, щоб визначити ім’я поточного користувача.


![image](https://github.com/user-attachments/assets/183b6b0b-e7be-42c5-9b80-99aa4bb46ac0)

![image](https://github.com/user-attachments/assets/a4b9d952-f8d8-4144-a808-c8b9021e1b71)



![image](https://github.com/user-attachments/assets/2db01a6f-1de1-42e8-bfdf-32430149de82)

Опис експерименту

Звичайний користувач створює файл.

Програма, що запускається з правами root, копіює цей файл у домашній каталог користувача.

Потім, знову від звичайного користувача:

спроба змінити вміст файлу;

спроба видалити файл.

![image](https://github.com/user-attachments/assets/3a28a88b-0f1e-4cc3-8ce9-23cbe474f233)

![image](https://github.com/user-attachments/assets/6511913b-1ac0-4e82-90ff-7475ab7bb478)

Спроба змінити файл: Помилка Permission denied, тому що root встановив права 0400 (тільки для читання) і файл належить root.

Спроба видалити файл: Файл буде видалений, оскільки користувач має право на запис у свій домашній каталог, а це достатньо для видалення навіть "чужого" файлу.

Висновок:

Звичайний користувач не зможе змінити вміст файлу, створеного root з правами 0400.

Проте зможе видалити цей файл, якщо має права на запис у батьківську директорію — у цьому випадку домашній каталог.

Це демонструє, що видалення залежить від прав на каталог, а не на сам файл.


![image](https://github.com/user-attachments/assets/4e604ce3-cd8a-445c-9778-df4854727761)

![image](https://github.com/user-attachments/assets/a090eee8-1fb6-482f-b00f-670039db617e)

![image](https://github.com/user-attachments/assets/5acdfc21-e8f8-47e9-bf7e-16824a03252c)

whoami виводить поточне ім’я користувача.

id виводить:

uid — ідентифікатор користувача;

gid — основна група;

групи — усі групи, до яких користувач належить.

![image](https://github.com/user-attachments/assets/1557b807-93c0-41a3-a547-5a78821d470e)

![image](https://github.com/user-attachments/assets/3a34b1f6-97d2-424f-8814-93ed836be6be)

![image](https://github.com/user-attachments/assets/85f18083-5274-4e42-ac96-1d6203d68cf9)

Після chmod 0400 і chown root, файл належить root і дозволяє лише читання власнику (root).

Звичайний користувач:

не зможе читати (якщо він не власник і не має відповідних прав);

не зможе писати (оскільки прав на запис також немає).

Висновок: права доступу та власник визначають можливість читання/запису. Звичайний користувач може втратити доступ до свого ж файлу, якщо root змінить права (chmod) або власника (chown).

![image](https://github.com/user-attachments/assets/b421b0df-334f-4303-9f64-760eed381cdf)

![image](https://github.com/user-attachments/assets/7a256e84-4396-4726-b293-bdde53b8a4d8)

![image](https://github.com/user-attachments/assets/5f1dcd41-4d2d-4816-aa6d-f1cb18ddc86c)

Частина виводу:

![image](https://github.com/user-attachments/assets/5a956133-4f2e-4141-937d-6b746ab0cfa8)

Що демонструє програма:

Для кожного файлу у вказаних директоріях:

виводить власника, групу, права (восьмирічна система);

виконує перевірки: чи дозволено читання, запис, виконання.

Програма показує, які операції дозволено звичайному користувачу.

Висновок:

У домашньому каталозі ($HOME) більшість файлів належить поточному користувачеві — дозволено читання/запис/виконання залежно від прав.

У /usr/bin більшість файлів належить root, але мають 755 — дозволено виконання.

У /etc зазвичай дозволено лише читання, іноді навіть закрито (для деяких конфігурацій), а запис — лише для root.

![image](https://github.com/user-attachments/assets/13028b74-229e-46ed-896d-5ad061016ca1)

Критерії, які використовує програма:

Shell користувача - якщо /usr/sbin/nologin, /bin/false або порожній - можливо системний.

Домашній каталог - якщо /nonexistent, /var, або / - можливо системний.

Ім’я користувача - якщо виглядає службовим (наприклад, daemon, mysql, systemd-*).

Відсутність tty або пароля.

![image](https://github.com/user-attachments/assets/5f28bdb1-cd37-4337-aa9d-2361dfb76748)

![image](https://github.com/user-attachments/assets/1f8b0f21-26bb-4edc-a072-052d3f4b3651)

![image](https://github.com/user-attachments/assets/58288b06-3f36-4915-a41e-be20359283ec)

Ця програма не спирається на UID, а аналізує характерні ознаки службових облікових записів. Це підхід, подібний до того, як роблять деякі дистрибутиви Linux, коли не можна покластися на UID > 1000 як єдиний критерій.
