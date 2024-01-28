#include <iostream>
#include <vector>

int Left(int i ) { //из лекции
    int result = 2 * i + 1;
    return result;
}

int Right(int i ) {
    int result = 2 * i + 2;
    return result;
}
// это тоже из лекции, не переживаем

void MaxHeapify(std::vector<int>& A, int i, int n) {
    int Largest = i;
    int L = Left(i);
    int R = Right(i);
    if (L < n && A[L] > A[Largest]) { //в лекции опечатка, во первый там должно быть меньше, во вторых вместо R должно стоять Largest
        Largest = L;
    } else {
        Largest = i;
    }
    if (R < n && A[R] > A[Largest]) {
        Largest = R;
    }
    if (Largest != i) {
        std::swap(A[i], A[Largest]);
        MaxHeapify(A, Largest, n);
    }
}

void Buildheapint (std::vector<int>& A, int n) {
    for (int i = n/2 - 1; i >= 0; --i) {
        MaxHeapify(A, i, n);
    }
}





void heapsort(std::vector<int>& A, int n) {
    Buildheapint(A, n);
    for (int i = n - 1; i >= 0; --i) {
        std::swap(A[i], A[0]);
        MaxHeapify(A, 0, i);
    }
}



int main() {
    int n;
    std::cin>> n;
    std::vector<int> numbers;
    for (int i = 0; i < n; ++i) {
        int a;
        std::cin>> a ;
        numbers.push_back(a);
    }
    heapsort(numbers, n);
    for (int i = 0; i < numbers.size(); ++i) {
        std::cout<< numbers[i];
        std::cout<<" ";
    }
    return 0;
}
