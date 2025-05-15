![image](https://github.com/user-attachments/assets/0be5c232-5c92-4a5d-8b3a-cdcc75eb8609)

![image](https://github.com/user-attachments/assets/ebf2d8ca-b95d-4ad8-af06-e7eb3b9a9dae)

arr[5] виходить за межі масиву з 5 елементів (індекси: 0–4). Такий доступ — невизначена поведінка (UB):

Може вивести «сміття»

Або звернутись до чужої памʼяті

Або спричинити краш (особливо в valgrind або asan)

![image](https://github.com/user-attachments/assets/eafd8661-88d6-4110-8223-97c477b08ada)

Перевірка за допомогою Valgrind

![image](https://github.com/user-attachments/assets/027fb2a7-fe87-4e92-906f-967276a755a9)

![image](https://github.com/user-attachments/assets/565d54b2-aa0c-4524-994f-4a507fa68d67)

Виправлений код

![image](https://github.com/user-attachments/assets/b829413b-88de-4f34-ab10-ab717565f9d4)


