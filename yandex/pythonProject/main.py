import re

def count_identifiers(text):
    # Компилируем регулярное выражение для поиска идентификаторов
    pattern = r'\b[A-Za-z][A-Za-z0-9]*\b'
    regex = re.compile(pattern)

    # Используем множество для хранения уникальных идентификаторов
    identifiers = set()

    # Находим все идентификаторы в тексте
    matches = regex.findall(text)

    # Добавляем найденные идентификаторы в множество
    for match in matches:
        identifiers.add(match)
    print(identifiers)

    return len(identifiers)

def main():
    # Считываем ASCII-строку с консоли
    text = input("Введите ASCII-строку: ")

    # Определяем количество различных идентификаторов
    count = count_identifiers(text)

    # Выводим результат
    print("Количество различных идентификаторов:", count)

if __name__ == "__main__":
    main()
