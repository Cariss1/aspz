![image](https://github.com/user-attachments/assets/793544c3-1c83-406a-823f-81762af9c677)

Так, виклик може повернути значення, менше за nbytes — це називається частковий (partial) запис.

Чому це може статися?
1. Нестача місця в буфері ядра (наприклад, сокет або pipe)
2. Запис у файл через мережу або FIFO
3. Переривання сигналом (EINTR)
4. Обмеження I/O (наприклад, обмеження запису через ulimit)

![image](https://github.com/user-attachments/assets/fcf5e857-b865-457f-981e-0ae2618b9aaa)
lseek(fd, 3, SEEK_SET); переміщує покажчик файлу на 3-й байт (тобто починаючи з індексу 3, відлік з нуля). Тобто read(fd, &buffer, 4); читає байти з позицій:

[3] = 2  

[4] = 3  

[5] = 3  

[6] = 7

отже buffer буде містити: 2, 3, 3, 7

![image](https://github.com/user-attachments/assets/a8c4ed7b-cdde-4229-bc7c-d0fd9733ead6)


![image](https://github.com/user-attachments/assets/efaed090-ef76-4dec-b676-2aa50c8ef93a)



Найгірші вхідні дані для класичного quicksort: вже відсортований масив, відсортований у зворотному порядку, всі елементи однакові

Але стандартна qsort() у libc зазвичай оптимізована, тож найгірші випадки треба навантажити великим розміром

код:
1. Створює масив SIZE цілих чисел

2. Заповнює його 4 різними способами

3. Викликає qsort()

4. Вимірює час роботи

5. Перевіряє правильність сортування

![image](https://github.com/user-attachments/assets/7a6a6e15-462d-475f-bba0-32e2726555d9)


![image](https://github.com/user-attachments/assets/e4bcebdd-7712-40a3-82ee-159d27735db1)

![image](https://github.com/user-attachments/assets/5bd5bfa4-9f60-409c-809f-21fd1e334b60)

Що робить fork()?
Створює копію поточного процесу

Повертає:

0 — у дочірньому процесі

PID дочірнього процесу — у батьківському процесі

-1 — у разі помилки (тут не перевіряється)

![image](https://github.com/user-attachments/assets/ea8cb828-060a-48e2-9ecd-ae314bf4ea8a)

![image](https://github.com/user-attachments/assets/0f5c3b63-7c88-420e-a90d-f5d3ed886d1e)

(Порядок залежить від ОС і планувальника — хто швидше виконає printf())


Завершений код програми

![image](https://github.com/user-attachments/assets/e86ce8f9-7c16-44d0-b92f-7466e3b521f0)

![image](https://github.com/user-attachments/assets/d02b62af-f080-45ec-b795-8d625f41f798)


![image](https://github.com/user-attachments/assets/25c64ec2-cc83-460b-a77b-1972d07ac1c4)

План експерименту

Створити програму на C, яка створює кілька дочірніх процесів (fork()).

Кожен процес багаторазово викликає write() у спільний файл.

Запустити експеримент у двох режимах:

з використанням open(..., O_WRONLY | O_CREAT | O_APPEND, ...)

з використанням open(..., O_WRONLY | O_CREAT, ...) (без O_APPEND)

Порівняти результати у файлі: чи змішалися дані різних процесів.

Очікувані результати

З O_APPEND: кожен запис буде доданий у кінець файлу атомарно — рядки не будуть перемішані.

Без O_APPEND: можливе перемішування байтів між записами різних процесів (наприклад, "Proces0ess 1..." замість повних рядків) — це демонструє, що write() без O_APPEND не гарантує цілісності при спільному записі.

![image](https://github.com/user-attachments/assets/2f58334b-08d5-4134-8b03-dbb4e24fbe90)

O_APPEND забезпечує, що кожен виклик write() додає дані у кінець файлу атомарно, що критично для багатопроцесних або багатопотокових програм. Без O_APPEND необхідно вручну реалізовувати механізми синхронізації (локи, семафори тощо).

