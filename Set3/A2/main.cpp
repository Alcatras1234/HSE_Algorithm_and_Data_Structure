#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <chrono>

std::vector<int> generateRandomArray(int size, int rangeStart, int rangeEnd) {
    std::vector<int> randomArray;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(rangeStart, rangeEnd);

    for (int i = 0; i < size; ++i) {
        randomArray.push_back(dis(gen));
    }

    return randomArray;
}

std::vector<int> generateReversedArray(int size, int rangeStart, int rangeEnd) {
    std::vector<int> reversedArray;
    for (int i = rangeEnd; i >= rangeStart; --i) {
        reversedArray.push_back(i);
    }
    return reversedArray;
}

std::vector<int> generateAlmostSortedArray(int size, int rangeStart, int rangeEnd, int numSwaps) {
    std::vector<int> almostSortedArray;
    for (int i = rangeStart; i <= rangeEnd; ++i) {
        almostSortedArray.push_back(i);
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, size - 1);
    for (int i = 0; i < numSwaps; ++i) {
        int idx1 = dis(gen);
        int idx2 = dis(gen);
        std::swap(almostSortedArray[idx1], almostSortedArray[idx2]);
    }

    return almostSortedArray;
}

void merge(std::vector<int>& A, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid; // не учитываем mid

    std::vector<int> L(n1);
    std::vector<int> R(n2);
    for (int i = 0; i < n1; ++i) {
        L[i] = A[left + i];
    }
    for (int i = 0; i < n2; ++i) {
        R[i] = A[mid + i + 1];
    }

    int i = 0;
    int j = 0;
    int k = left;
    while (i < n1 && j < n2){
        if (L[i] < R[j]) {
            A[k] = L[i];
            i++;
        } else {
            A[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        A[k++] = L[i++];
    }
    while (j < n2) {
        A[k++] = R[j++];
    }
}

void MergeSort (std::vector<int>& A, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        MergeSort(A, left, mid);
        MergeSort(A, mid + 1, right);
        merge(A, left, mid, right);
    }
}

void mergeSortInsertionSort (std::vector<int>& A, int left, int right, int board) {
    if (left < right) {
        if (right - left <= board) {
            for (int i = left + 1; i <=right; ++i) {
                int key = A[i];
                int j = i - 1;
                while (j >= left && A[j] > key) {
                    A[j + 1] = A[j];
                    --j;
                }
                A[j + 1] = key;
            }
        } else {
            int mid = left + (right - left) / 2;
            mergeSortInsertionSort(A, left, mid, board);
            mergeSortInsertionSort(A, mid + 1, right, board);
            merge(A, left, mid, right);
        }
    }
}


int main() {
    int size = 1000;  // Размер массива
    int start = 0;  // Начальное значение диапазона
    int end= 3000;  // Конечное значение диапазона
    int numSwaps = 10;  // Количество пар элементов для почти отсортированного массива

    std::vector<int> randomArray = generateRandomArray(size, start, end);
    std::vector<int> reversedArray = generateReversedArray(size, start, end);
    std::vector<int> almostSortedArray = generateAlmostSortedArray(size, start, end, numSwaps);

    auto start_time = std::chrono::high_resolution_clock::now();
    mergeSortInsertionSort(almostSortedArray, 10, 60, 50);
    //MergeSort(almostSortedArray,0,50);
    auto elapsed = std::chrono::high_resolution_clock::now() - start_time;
    long long millisec = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();

    std::cout<<millisec;
    return 0;
}

