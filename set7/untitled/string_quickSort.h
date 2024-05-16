
#ifndef UNTITLED_STRING_QUICKSORT_H
#define UNTITLED_STRING_QUICKSORT_H

#endif //UNTITLED_STRING_QUICKSORT_H

#include <iostream>
#include <vector>
#include <string>

void ternaryQuickSort(std::vector<std::string>& arr, int low, int high, int& comparisonCount) {
    if (low < high) {
        int mid = low + (high - low) / 2;
        std::swap(arr[mid], arr[high]);
        std::string pivot = arr[high];

        int i = low, j = low, k = high;
        while (j <= k) {
            comparisonCount++;
            if (arr[j] < pivot) {
                std::swap(arr[i], arr[j]);
                i++;
                j++;
            } else if (arr[j] == pivot) {
                comparisonCount++;
                j++;
            } else {
                std::swap(arr[j], arr[k]);
                k--;
            }
        }

        // **Три рекурсивных вызова:**
        ternaryQuickSort(arr, low, i - 1, comparisonCount); // Меньше опоры
        ternaryQuickSort(arr, i, j - 1, comparisonCount); // Равны опоре !!!
        ternaryQuickSort(arr, j, high, comparisonCount); // Больше опоры
    }
}
