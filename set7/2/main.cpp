#include <iostream>
#include <vector>

int prefix_size(std::string str) {
    std::vector<size_t> prefixFunction;
    size_t i = 1;
    size_t j = 0;
    prefixFunction.push_back(0);
    while ( i < str.length()) {
        if (str[i] == str[j]) {
            prefixFunction.push_back(j + 1);
            ++i;
            ++j;

        } else if (j > 0) {
            j = prefixFunction[j - 1];
        } else {
            prefixFunction.push_back(0);
            i = i + 1;
        }
    }
    return str.length() - prefixFunction.back();


}

int main() {
    std::string str;
    std::cin>>str;
    std::cout<< prefix_size(str);
    return 0;
}
