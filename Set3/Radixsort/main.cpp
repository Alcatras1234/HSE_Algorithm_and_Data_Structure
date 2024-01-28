#include <iostream>
#include <vector>
#include <climits>
#import <cmath>

int max(std::vector<int>& A, int n) {
    int maxi = INT_MIN;
    for (int i = 0; i < n; ++i) {
        if (A[i] > maxi) {
            maxi = A[i];
        }
    }
    return std::to_string(maxi).size();
}


void RadixSort(std::vector<int>& A, int n) {
    int maxi = max(A, n);
    int base = 256;

    std::vector<std::vector<int>> bins(base, std::vector<int>());

    for (int i = 0; i < maxi; ++i) {
        for (int x : A) {
            int digit = (x / static_cast<int>(pow(base, i))) % base;
            bins[digit].push_back(x);
        }

        A.clear();
        for (std::vector<int>& queue : bins) {
            for (int x : queue) {
                A.push_back(x);
            }
            queue.clear();
        }
    }
}

void get_plus(std::vector<int>& A, int n) {
    for (int i = 0; i < n; ++i) {
        A[i] = abs(A[i]);
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
    std::vector<int> numbers;
    for (int i = 0; i < n; ++i) {
        int a;
        std::cin>> a ;
        numbers.push_back(a);
    }
    get_plus(numbers, n);
    RadixSort(numbers, n);
    for (int i = 0; i < n; ++i) {
        std::cout<<numbers[i]<<" ";
    }
    return 0;
}
