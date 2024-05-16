#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

const int R = 256; // Расширенный ASCII алфавит

void ternaryQuickSort2(std::vector<std::string>& arr, int low, int high, int& comparisonCount) {
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

        ternaryQuickSort2(arr, low, i - 1, comparisonCount);
        ternaryQuickSort2(arr, i, j - 1, comparisonCount);
        ternaryQuickSort2(arr, j, high, comparisonCount);
    }
}

void msdRadixSort(std::vector<std::string>& arr, int low, int high, int d, int& comparisonCount) {
    if (low >= high || d >= arr[low].size()) return;

    std::vector<int> count(R + 2);
    for (int i = low; i <= high; i++) {
        count[arr[i][d] + 2]++;
    }
    for (int r = 1; r < R + 2; r++) {
        count[r] += count[r - 1];
    }

    std::vector<std::string> aux(high - low + 1);
    for (int i = low; i <= high; i++) {
        aux[count[arr[i][d] + 1]++] = arr[i];
    }
    for (int i = low; i <= high; i++) {
        arr[i] = aux[i - low];
    }

    // Переключение на QuickSort, если подмассив маленький enough
    if (high - low + 1 <= 10) {
        ternaryQuickSort(arr, low, high, comparisonCount);
        return;
    }

    for (int r = 0; r < R + 1; r++) {
        msdRadixSort(arr, low + count[r], low + count[r + 1] - 1, d + 1, comparisonCount);
    }
}