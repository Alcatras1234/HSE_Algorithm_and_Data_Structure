#include <iostream>
#include <vector>

int count_identificator(char buf[], int size) {
    int count = 0;
    bool word_started = false;

    for (ssize_t i = 0; i < size; i++) {
        if (isalpha(buf[i])) {
            word_started = true;
        } else if (word_started && !isalnum(buf[i])) {
            word_started = false;
            count++;
        }

    }

    return count;
}

int main() {
    char input[] = "jtgyhiuy87 96 967 jkg rfdgfjk897 hjg9"; // Ваша строка
    int identifiers = 0; // Вектор для хранения идентификаторов


    int count = count_identificator(input, sizeof(input));

    // Выводим найденные идентификаторы
    std::cout << "Найденные идентификаторы: " << count<< std::endl;

    std::cout<<identifiers;
    return 0;
}
