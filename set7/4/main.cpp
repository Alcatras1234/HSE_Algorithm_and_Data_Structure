#include <iostream>
#include <vector>
#include <algorithm>

std::vector<size_t> prefix (std::string str) {
    size_t length = 1;
    std::string copy = str;
    //std::reverse(copy.begin(), copy.end());
    std::vector<size_t> table(27, 0);
    for (int i = str.length() - 2; i > -1;  --i) {
        if (table[copy[i] - 97] == 0) {
            table[copy[i] - 97] = length++;
        }
    }
    if (table[str[str.length() - 1] - 'a'] == 0 ) {
        table[str[str.length() - 1] - 'a'] = str.length();
    }
    table[26] = str.length();
    return table;
}
std::vector<size_t> BMH(std::string &pattern, std::string &text) {
    std::vector<size_t> table = prefix(pattern);
    int i = pattern.length() - 1; // pattern
    int j = pattern.length() - 1; // text
    size_t count = 0;
    std::vector<size_t> answer;
    int last_j = j;
    int text_l = text.length();


    while (j < text_l) {
        if (pattern[i] == text[j] && i >= 0)  { // проверяем предыдущие символы на равенство i>= 0 для проверки в случае, если текс и патерн равны
                i--;
                j--;
        } else if (i == -1) { // если слова стали равными
            count++;
            j = last_j;
            int k = j - pattern.length() + 1;
            answer.push_back(k);

            j += 1; // прибавляем длину
            last_j = j;
            i = pattern.length() - 1;

        }

        else {
            if (j != last_j) {
                // если слова не стали равными

                j = last_j;
                j += table[pattern[i] - 'a'];
                i = pattern.length() - 1;
                last_j = j;



            } else {
                if (table[text[j] - 'a'] == 0) { // если символа нет в префикс таблице
                    j += pattern.length();
                    last_j = j;
                } else { // если есть
                    j += table[text[j] - 'a'];
                    last_j = j;
                }
            }
        }





//        if (pattern[i] != text[j]) {
//            if (table[text[j] - 'a'] == 0) { // если символа нет в префикс таблице
//                j += pattern.length();
//            } else { // если есть
//                j += table[text[j] - 'a'];
//            }//i += table[text[i] - 'a'];
//        }
//        else {
//            int j1 = j;
//            int i1 = i;
//            // сравниваем последующие символы
//            while (pattern[i1] == text[j1]) {
//                i1--;
//                j1--;
//            }
//
//            // если слова равны, то ищем номер позиции с которого начинается очередное вхождение строки
//            if (i1 == -1) {
//                count++;
//                int k = j - pattern.length() + 1;
//                answer.push_back(k);
//                j += table[text[j] - 'a'];
//            } else { // если же нет, прибавляем к j то значение буквы из таблицы, которое не совпало
//                j += table[pattern[i1] - 'a'];
//            }



    }
    answer.push_back(count); // кол-во вхождений
    return answer;
}

int main() {
    std::string text, pattern;
    std::cin >> pattern >> text;
    if (pattern.empty() || text.empty()) {
        std::cout<< 0 << std::endl;
        return 0;
    }
    std::vector<size_t> a = BMH(pattern, text);
    std::cout << a[a.size() - 1] << std::endl;
    for (size_t i = 0; i < a.size() - 1; ++i) {
        std::cout << a[i] << std::endl;
    }


    return 0;
}
