#include <iostream>
#include <map>
#include <vector>

void prefix_function(std::string str) {
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

    for (int i = 0; i < prefixFunction.size(); ++i) {
        std::cout<<prefixFunction[i]<<" ";
    }
}

int main() {
    std::string str;
    std::cin>>str;
    prefix_function(str);
    return 0;
}
