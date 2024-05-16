#include <iostream>
#include <vector>



void prefix(std::string str, std::vector<size_t> &prefixFunction) {
    size_t i = 1;
    size_t j = 0;

    prefixFunction.push_back(0);
    while ( i < str.length()) {
        if (str[i] == str[j]) { // i - is next, j - is current

            prefixFunction.push_back(j + 1);
            ++i;
            ++j;

        } else if (j > 0) {
            j = prefixFunction[j - 1];
        } else {
            prefixFunction.push_back(0);
            i = i + 1;
        }
    }
    prefixFunction.erase(prefixFunction.begin(), prefixFunction.begin() + str.length());
    // уточненные границы
    for (size_t i = 0; i <= str.length(); ++i) {
        if (prefixFunction[i] > 0 && prefixFunction[i] < prefixFunction[i + 1]) {
            prefixFunction[i] = 0;
        }
    }
}

std::vector<size_t> KMPSearch(std::vector<size_t>& prefixFunction, std::string pattern, std::string text) {
    size_t txtIndex = 0;
    size_t patIndex = 0;
    size_t M = pattern.length();
    size_t N = text.length();
    std::vector<size_t> occurrences;
    int count = 0;

    while (txtIndex < N) { // Используем while для поиска всех вхождений
        if (text[txtIndex] == pattern[patIndex]) {
            if (patIndex == M - 1) {
                count++;
                occurrences.push_back(txtIndex - patIndex); // Добавляем позицию вхождения
                patIndex = prefixFunction[patIndex]; // Сдвигаем patIndex
                ++txtIndex; // Продолжаем поиск
            } else {
                ++txtIndex;
                ++patIndex;
            }
        } else {
            if (patIndex > 0) {
                patIndex = prefixFunction[patIndex - 1];
            } else {
                ++txtIndex;
            }
        }
    }
    occurrences.push_back(count);
    return occurrences;
}

int main() {
    std::string text, pattern;
    std::cin>>pattern>>text;
    std::vector<size_t> prefixFunction(pattern.length());
    prefix(pattern, prefixFunction);
    std::vector<size_t> answer = KMPSearch(prefixFunction, pattern, text);
    std::cout<<answer[answer.size() - 1]<<'\n';
    for (size_t i = 0; i < answer.size() - 1; ++i) {
        std::cout<<answer[i]<<'\n';
    }
    return 0;
}
