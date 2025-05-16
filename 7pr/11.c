import os
import stat
from collections import defaultdict


LOG_FILE = 'access.log'


READ_THRESHOLD = 3
FULL_ACCESS_THRESHOLD = 5


def parse_log_file():
    file_users = defaultdict(set)  # файл -> набір унікальних користувачів

    with open(LOG_FILE, 'r') as f:
        for line in f:
            parts = line.strip().split()
            if len(parts) != 2:
                continue
            user, filepath = parts
            file_users[filepath].add(user)
    
    return file_users


def update_permissions(file_users):
    for filepath, users in file_users.items():
        try:
            if not os.path.exists(filepath):
                print(f"Файл {filepath} не існує.")
                continue

            user_count = len(users)
            if user_count >= FULL_ACCESS_THRESHOLD:
           
                os.chmod(filepath, 0o777)
                print(f"{filepath}: надано повний доступ (777)")
            elif user_count >= READ_THRESHOLD:
            
                os.chmod(filepath, 0o744)
                print(f"{filepath}: доступ лише для читання (744)")
            else:
             
                os.chmod(filepath, 0o700)
                print(f"{filepath}: мінімальний доступ (700)")
        except Exception as e:
            print(f"Помилка з файлом {filepath}: {e}")


def main():
    file_users = parse_log_file()
    update_permissions(file_users)

if __name__ == "__main__":
    main()
