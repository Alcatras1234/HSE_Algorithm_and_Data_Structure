#include <iostream>

bool containDigit(const std::string& str) {
    for (char c : str) {
        if (std::isdigit(c)) {
            return true;
        }
    }
    return false;
}

bool containUpper(const std::string& str) {
    for (char c : str) {
        if (std::isupper(c)) {
            return true;
        }
    }
    return false;
}

bool containLower(const std::string& str) {
    for (char c : str) {
        if (std::islower(c)) {
            return true;
        }
    }
    return false;
}

int main() {
    std::string input;
    std::cin>>input;
    if (input.length() >= 8 && containDigit(input) && containLower(input) && containUpper(input)) {
        std::cout<<"YES";
    }
    else {
        std::cout<<"NO";
    }


    return 0;
}
