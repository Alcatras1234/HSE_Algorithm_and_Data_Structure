#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>
#include <fstream>

#include "string_quickSort.h"
#include "string_mergeSort.h"
#include "string_radix_sort.h"
#include "string_radix_sort2.h"

class StringGenerator {
public:
    StringGenerator(size_t len_str, size_t count_strs) : gen(rd()), len_str(len_str), count_strs(count_strs),
                                                         dist(0, alphabet.size() - 1) {} // Инициализация dist

    std::vector<std::string> generateStrings(int count) {
        std::vector<std::string> strings;
        for (int i = 0; i < count; ++i) {
            strings.push_back(generateString());
        }
        return strings;
    }

    std::vector<std::string> generateSortedStringsInAnotherSide(int count) {
        std::vector<std::string> strings;
        for (int i = 0; i < count; ++i) {
            strings.push_back(generateString());
        }

        std::sort(strings.begin(), strings.end(), [](const std::string &a, const std::string &b) {
            return a > b; // Переворачиваем результат сравнения
        });

        return strings;
    }

    std::vector<std::string> generateAlmostSortedStrings(int count) {
        std::vector<std::string> strings;
        for (int i = 0; i < count; ++i) {
            strings.push_back(generateString());
        }

        std::sort(strings.begin(), strings.end(), [](const std::string &a, const std::string &b) {
            return a < b;
        });

        std::uniform_int_distribution<> distSwap(0, count - 2);
        for (int i = 0; i < 20; ++i) {
            int index1 = distSwap(gen);
            int index2 = index1 + 1;
            std::swap(strings[index1], strings[index2]);
        }

        return strings;

    }

private:
    std::string generateString() {
        std::string str;
        for (int i = 0; i < len_str; ++i) {
            str += alphabet[dist(gen)];
        }
        return str;
    }

    std::random_device rd;
    std::mt19937 gen;
    size_t len_str;
    size_t count_strs;
    const std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#%:;^&*()-";
    std::uniform_int_distribution<> dist;  // Без инициализации здесь
};

int partition(std::vector<std::string> &arr, int low, int high, int &comparisonCount) {
    std::string pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        comparisonCount++;
        if (arr[j] < pivot) { // Лексикографическое сравнение строк
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSort(std::vector<std::string> &arr, int low, int high, int &comparisonCount) {
    if (low < high) {
        int pi = partition(arr, low, high, comparisonCount);
        quickSort(arr, low, pi - 1, comparisonCount);
        quickSort(arr, pi + 1, high, comparisonCount);
    }
}


void merge(std::vector<std::string> &arr, int left, int mid, int right, int& compareC) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<std::string> L(n1), R(n2);

    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
    }

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        compareC++;
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(std::vector<std::string> &arr, int left, int right, int& compareC) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid, compareC);
        mergeSort(arr, mid + 1, right, compareC);
        merge(arr, left, mid, right, compareC);
    }
}


int main() {
    StringGenerator generator(15, 250);  // Пример использования
//    auto strings = generator.generateStrings(2500);
//    auto strings3 = generator.generateAlmostSortedStrings(250);
//    auto strings2 = generator.generateSortedStringsInAnotherSide(250);
//    как происходила запись в файл, можно в конце менять название выходного файла
//    std::ofstream outputFile("C:/HSE/Second COurse HSe/Alogoritms and data structures/set7/untitled/arr35.txt");
//
//    if (outputFile.is_open()) {
//        // Записываем строки в файл
//        for (const auto &str: strings3) {
//            outputFile << str << std::endl;
//        }
//
//        outputFile.close(); // Закрываем файл
//        std::cout << "Строки успешно записаны в файл arr1.txt" << std::endl;
//    } else {
//        std::cerr << "Ошибка: не удалось открыть файл для записи." << std::endl;
//    }
//    for (const auto& str : strings) {
//        std::cout << str << std::endl;
//    }

//    auto strings2 = generator.generateSortedStringsInAnotherSide(15);
//
////    for (const auto &str: strings2) {
////        std::cout << str << std::endl;
////    }



//    for (const auto &str: strings3) {
//        std::cout << str << std::endl;
//    }
    std::vector<std::string> arr1;
    std::ifstream inputFile("C:/HSE/Second COurse HSe/Alogoritms and data structures/set7/untitled/arr1.txt");

    if (inputFile.is_open()) {
        std::string line;
        // Читаем строки из файла
        while (getline(inputFile, line)) {
            arr1.push_back(line); // Добавляем строку в массив
        }

        inputFile.close(); // Закрываем файл
        std::cout << "Get strings into arr**.txt ok!" << std::endl;
    } else {
        std::cerr << "Error." << std::endl;
    }
    int count5 = 0;
    for (int i = 0; i < 5; ++i) {
        auto start = std::chrono::high_resolution_clock::now(); // Начало замера
        msdRadixSort2(arr1, 0, arr1.size() - 1, 0, count5);
        auto end = std::chrono::high_resolution_clock::now(); // Конец замера

        std::chrono::duration<double> diff = end - start; // Разница во времени

        std::cout << "Sort sorting time on array: " << diff.count() << " " << " count = " << count5
                  << std::endl;
    }

    return 0;
}
