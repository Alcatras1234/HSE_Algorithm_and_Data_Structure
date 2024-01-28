#include <iostream>
#include <vector>
#include <climits>

int max(std::vector<int>& A, int n) {
    int maxi = INT_MIN;
    for (int i = 0; i < n; ++i) {
        if (A[i] > maxi) {
            maxi = A[i];
        }
    }
    return maxi;
}

int min(std::vector<int>& A, int n) {
    int mini = INT_MAX;
    for(int i = 0; i < n; ++i) {
        if (mini > A[i]) {
            mini = A[i];
        }
    }
    return mini;
}

void countingSort(std::vector<int>& A, int n) {
    int maxi;
    maxi = max(A, n);
    int mini = min(A, n);
    int range = maxi - mini + 1;
    if (range < 0) {
        range = INT_MAX;
    }
    std::vector<int> holes(range); // вектор векторов
    for (int i = 0; i < n; ++i) {
        holes[A[i] - mini] += 1;
    }
    for (int i = 0; i < range; ++i) {
        if (holes[i] == 0)
            continue;
        for (int j = 0; j < holes[i]; ++j) {
            std::cout<<i + mini<<" ";
        }
    }

}

int main() {
    int n;
    std::cin>> n;
    if (n == 0) {
        return 0;
    }
    if (n < 0) {
        n = abs(n);
    }
    if (n < INT_MIN) {

    }
    std::vector<int> numbers;
    for (int i = 0; i < n; ++i) {
        int a;
        std::cin>> a ;
        numbers.push_back(a);
    }
    countingSort(numbers, n);
    return 0;
}
