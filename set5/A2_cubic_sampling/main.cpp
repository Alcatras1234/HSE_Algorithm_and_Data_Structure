#include <iostream>
#include <vector>
#include <cmath>

class SquareSampling {
private:
    std::vector<int> num_;
    std::vector<int> hash_table;
    int collision;

    size_t M_;
public:
    SquareSampling(std::vector<int> numbers, size_t M) : collision(0){
        num_ = std::vector<int>(numbers.size());
        num_ = numbers;
        M_ = M;
        hash_table = std::vector<int>(M_, -1);
    }

    void filler() {
        for (size_t i = 0; i < M_; ++i) {
            int number = num_[i];
            if (number < 0)
                return;
            int hashV = hasher(number, M_);
            if (hash_table[hashV] == -1) {
                hash_table[hashV] = number;
            } else {
                ++collision;
                size_t j = hashV % M_;
                while (hash_table[j] != -1) {
                    ++collision;
                    j = (number + hash_code(++j)) % M_;
                }
                hash_table[j] = number;
            }

        }
    }

    int Clasters() {
        size_t clusters = 0;
        size_t current_cluster_length = 0;

        for (size_t i = 0; i < M_; ++i) {
            if (hash_table[i] != -1) {

                current_cluster_length++;
            } else {

                if (current_cluster_length > 0) {
                    clusters++;
                    current_cluster_length = 0;
                }
            }
        }


        if (current_cluster_length > 0) {
            clusters++;
        }

        return clusters;
    }

    int Collision() {
        return collision;
    }

    int hasher (int a, size_t M) {
        return a % static_cast<int>(M);
    }

    int hash_code(size_t i) {
        return static_cast<size_t>( i + i * i);

    }

};


class CubeSampling {
private:
    std::vector<int> num_;
    std::vector<int> hash_table;
    int collision;

    size_t M_;
public:
    CubeSampling(std::vector<int> numbers, size_t M) : collision(0){
        num_ = std::vector<int>(numbers.size());
        num_ = numbers;
        M_ = M;
        hash_table = std::vector<int>(M_, -1);
    }

    void filler() {
        for (size_t i = 0; i < M_; ++i) {
            int number = num_[i];
            if (number < 0)
                return;
            int hashV = number % M_;
            if (hash_table[hashV] == -1) {
                hash_table[hashV] = number;
            } else {
                ++collision;
                size_t j = hashV % M_;
                while (hash_table[j] != -1) {
                    ++collision;
                    j = (number + hash_code(++j)) % M_;
                }
                hash_table[j] = number;

            }

        }
    }

    size_t Clasters() {
        size_t clusters = 0;
        size_t current_cluster_length = 0;

        for (size_t i = 0; i < M_; ++i) {
            if (hash_table[i] != -1) {

                current_cluster_length++;
            } else {

                if (current_cluster_length > 0) {
                    clusters++;
                    current_cluster_length = 0;
                }
            }
        }


        if (current_cluster_length > 0) {
            clusters++;
        }

        return clusters;
    }

    int Collision() {
        return collision;
    }


    int hash_code(size_t i) {
        return static_cast<size_t>( i * i * i + i * i + i);
    }

};


int main() {
    std::vector<int> numbers {87, 86, 74, 543, 532, 41, 10, 219, 109, 87,876, 65, 64, 43, 32, 1, 0, 13, 24, 3






    };
    int M = 100;

    for (size_t i = 0; i < numbers.size(); ++i) {
        std::cout << numbers[i] << " ";
    }
    CubeSampling d (numbers, M);
    std::cout<<"##############################\n";
    std::cout<<"CubeSamplind\n";
    d.filler();
    int e = d.Clasters();
    std::cout << "Clasters: " << e << std::endl;
    std::cout << "Collisions: " << d.Collision() << std::endl;

    std::cout << "##############################\n";
    std::cout << "SquareSampling\n";

    SquareSampling b(numbers, M);
    b.filler();
    int w = b.Clasters();
    std::cout << "Clasters: " << w << std::endl;
    std::cout << "Collision: " << b.Collision();
    return 0;
}
