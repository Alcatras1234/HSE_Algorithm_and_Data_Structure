#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

const int R2 = 256; // Расширенный ASCII алфавит

void msdRadixSort2(std::vector<std::string>& arr, int low, int high, int d, int& comparisonCount) {
    if (low >= high) { // Base case: подмассив пуст или состоит из одного элемента
        return;
    }

    std::vector<int> count(R2 + 2, 0); // Инициализируем count нулями
    for (int i = low; i <= high; i++) {
        if (d < arr[i].size()) { // Проверяем, что символ существует в строке
            count[arr[i][d] + 2]++; // Увеличиваем счетчик для символа
        } else {
            count[1]++; // Считаем строки, где символ отсутствует (как пустой символ)
        }
    }
    for (int r = 1; r < R + 2; r++) {
        count[r] += count[r - 1];
    }

    std::vector<std::string> aux(high - low + 1);
    for (int i = low; i <= high; i++) {
        if (d < arr[i].size()) {
            aux[count[arr[i][d] + 1]++] = arr[i];
        } else {
            aux[count[0]++] = arr[i]; // Обрабатываем строки с отсутствующим символом
        }
    }
    for (int i = low; i <= high; i++) {
        arr[i] = aux[i - low];
    }

    for (int r = 0; r < R2 + 1; r++) {
        msdRadixSort2(arr, low + count[r], low + count[r + 1] - 1, d + 1, comparisonCount);
    }
}