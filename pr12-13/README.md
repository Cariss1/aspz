![image](https://github.com/user-attachments/assets/3699517a-cdde-4682-b5c4-30890746a53e)

![image](https://github.com/user-attachments/assets/538ff6d6-34c6-4fc9-a793-dac42f52b025)

![image](https://github.com/user-attachments/assets/ad387f9f-d483-4301-becb-49439d341b7e)

![image](https://github.com/user-attachments/assets/640bfcc7-75ca-4564-bbc4-525d7cb8f86a)

![image](https://github.com/user-attachments/assets/66787125-cd12-4314-a108-77b8febe7417)

Пояснення роботи програми:

Ініціалізація трасування:

Програма створює дочірній процес, який виконує цільову програму

Використовує ptrace(PTRACE_TRACEME) для дозволу трасування

Основний цикл трасування:

Очікує події від дочірнього процесу за допомогою waitpid()

Обробляє різні стани процесу (вихід, сигнали, зупинки)

Збір інформації при падінні:

Використовує ptrace(PTRACE_GETREGS) для отримання регістрів процесу

Збирає стек викликів, читаючи пам'ять процесу через ptrace(PTRACE_PEEKDATA)

Формує звіт про падіння з інформацією про сигнал, регістри та стек викликів

Обробка сигналів:

Перехоплює сигнали, що призводять до падіння (SIGSEGV, SIGABRT тощо)

Генерує звіт перед передачею сигналу дочірньому процесу

![image](https://github.com/user-attachments/assets/cb68016c-7e54-4257-ac9b-fb961e462938)


