#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <algorithm>

class StringGenerator {
public:
    StringGenerator() : gen(rd()), distLen(10, 200), distCount(100, 3000) {}


    std::vector<std::string> generateStrings(int count) {
        std::vector<std::string> strings;
        for (int i = 0; i < count; ++i) {
            strings.push_back(generateString());
        }
        return strings;
    }

private:

    std::string generateString() {
        int len = distLen(gen);
        std::string str;
        for (int i = 0; i < len; ++i) {
            str += alphabet[distChar(gen)];
        }
        return str;
    }

    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<> distLen;
    std::uniform_int_distribution<> distCount;
    std::uniform_int_distribution<> distChar{0, (int)alphabet.size() - 1};
    const std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#%:;^&*()-";

};

int main() {
    StringGenerator generator;

    // Генерация максимальных массивов
    auto unsortedStrings = generator.generateStrings(3000);




    return 0;
}
