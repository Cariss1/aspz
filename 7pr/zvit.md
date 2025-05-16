![image](https://github.com/user-attachments/assets/54277823-9552-4678-9bb0-06114973deff)

![image](https://github.com/user-attachments/assets/bb0624a8-0412-47b4-9ecd-0d8d6d6c35cd)

![image](https://github.com/user-attachments/assets/62204587-6649-41ed-b831-333b8a2ea0b1)

програма зчитує вміст поточного каталогу; для кожного файла визначає тип, права доступу, власника, групу, розмір, час модифікації та ім’я; виводить у форматі, подібному до ls -l

![image](https://github.com/user-attachments/assets/acfa9268-56f2-4603-9544-677ac9f12f68)

![image](https://github.com/user-attachments/assets/02cd4abd-2783-4dc4-a049-c68909f428d3)

![image](https://github.com/user-attachments/assets/d2b9255a-e30c-45a1-96d2-95b300974d0b)

readdir() читає імена файлів у поточному каталозі;

stat() отримує інформацію про кожен файл;

getpwuid() та getgrgid() повертають імена власника та групи;

strftime() форматує час;

print_permissions() формує рядок прав доступу (аналог -rw-r--r--).

![image](https://github.com/user-attachments/assets/17e910d8-4b31-4d3c-ac53-291395c0c99f)

![image](https://github.com/user-attachments/assets/31509946-41df-463d-8894-7fb8c5c54f86)

Програма очікує два аргументи: слово для пошуку та ім’я файлу.

Вона читає файл пострічково (fgets) і перевіряє, чи містить кожен рядок вказане слово через strstr().

Якщо знаходить — друкує рядок.

![image](https://github.com/user-attachments/assets/3ce879d2-1777-4495-b895-f68099905688)

![image](https://github.com/user-attachments/assets/96e46b6e-c366-4b84-95a6-eb51d03407b7)

![image](https://github.com/user-attachments/assets/e68ea51c-8e33-438d-81d0-a003935f9667)

![image](https://github.com/user-attachments/assets/6e6c9ddb-cccb-46b3-8d7a-8a358eec29b6)

![image](https://github.com/user-attachments/assets/8a81ed08-265c-42a5-8207-4f5eb2599cdb)

![image](https://github.com/user-attachments/assets/22b793b9-ccdc-4bde-9c5c-a17c7e7a24e2)

вивід:

![image](https://github.com/user-attachments/assets/df5afdd6-5082-43be-8679-ada314add8ca)

Починає з поточного каталогу (".").

Для кожного підкаталогу викликає list_files() рекурсивно.

Виводить [Каталог] /шлях/до/каталогу і файли під ним.

![image](https://github.com/user-attachments/assets/3a689c42-eea2-4e11-b367-401777730784)

![image](https://github.com/user-attachments/assets/6b14c85a-88a3-4250-b78e-2d09c663be58)

![image](https://github.com/user-attachments/assets/3c27caf5-6082-4483-b826-f1153d4895df)

програма:

Ігнорує "." та "..";

Перевіряє, чи об’єкт є каталогом через stat;

Зберігає імена у масив;

Сортує алфавітно через qsort;

Виводить список каталогів.

![image](https://github.com/user-attachments/assets/672f4655-892e-4cae-a01c-34a1b83a40d5)

![image](https://github.com/user-attachments/assets/e9cb04d1-14d8-45fb-9433-54fd327c4100)

![image](https://github.com/user-attachments/assets/f05feb30-834b-4830-9c9d-45ad983645d3)

програма:

Шукає виконувані файли у домашньому каталозі ($HOME);

Для кожного питає, чи надати іншим дозвіл на читання;

Якщо користувач відповів "y", додає read-дозвіл для інших через chmod.

![image](https://github.com/user-attachments/assets/9b83363d-c088-4ff0-afa3-00093b9db4ec)

![image](https://github.com/user-attachments/assets/809ee14e-4abd-4422-9e53-a2842d462685)

![image](https://github.com/user-attachments/assets/d5f719c1-d384-4dc1-a6e6-2adfc6a28072)

програма:

Перевіряє, чи об'єкт — звичайний файл (S_ISREG);

Пропускає . і ..;

Запитує у користувача підтвердження перед видаленням кожного файлу;

Видаляє файл, якщо отримано підтвердження.

![image](https://github.com/user-attachments/assets/e6b9c1e0-6787-4fd0-bb2f-5a70ba8e4c4b)

![image](https://github.com/user-attachments/assets/e8b3c554-a6f3-462e-b904-35df37e41a7a)

програма:

Використовує gettimeofday() для отримання часу з точністю до мікросекунд;

Обчислює різницю між початковим і кінцевим часом у мілісекундах;

Виводить тривалість виконання коду.

![image](https://github.com/user-attachments/assets/9e180aa7-7555-4d5a-9c6a-7ae89a0d14a0)

![image](https://github.com/user-attachments/assets/5971c9c2-0b3a-45aa-b717-9f5318acc049)

![image](https://github.com/user-attachments/assets/440b43c9-de12-4b29-870f-4e959551c23e)

![image](https://github.com/user-attachments/assets/2bcb0adb-c4b4-4ee0-ad9f-2d6cc031a413)

програма:

Генерує випадкові числа типу double у двох діапазонах;

Ініціалізує srand() за поточним часом (time(NULL)), щоб послідовність була унікальною;

Виводить результати з точністю до шести знаків після коми;

Обробляє помилки введення.

![image](https://github.com/user-attachments/assets/b949a945-39a7-4a08-a9d5-080f17ba6acb)

![image](https://github.com/user-attachments/assets/66ee2514-a516-4e3e-b661-3a70467befde)

![image](https://github.com/user-attachments/assets/a4ff35b7-da49-4977-9c89-7e7b9445b0a3)

![image](https://github.com/user-attachments/assets/9b57b199-cf30-4563-8400-457bf309644a)
