#include <iostream>

bool simularStr(const std::string& original, const std::string& current) {
    std::string result;
    int cursor = 0;
    for (int i = 0; i < current.length(); ++i) {
        if (current[i] == '<') {
            if (i + 5 < current.length() && current.substr(i, 6) == "<left>") {
                if (cursor > 0)
                    cursor--;
                i += 5;
            } else if (i + 6 < current.length() && current.substr(i, 7) == "<right>") {
                if (cursor < result.length())
                    cursor++;
                i += 6;
            } else if (i + 7 < current.length() && current.substr(i, 8) == "<bspace>") {
                if (cursor > 0) {
                    result.erase(cursor - 1, 1);
                    cursor--;
                }
                i += 7;
            } else if (i + 7 < current.length() && current.substr(i, 8) == "<delete>") {
                if (cursor < result.length())
                    result.erase(cursor, 1);
                i += 7;
            }
        }
        else if (std::isalpha(current[i])) {
            result.insert(cursor++, 1, current[i]);

        }
    }
    return original == result;
}

int main() {
    std::string a, b;
    std::cin>>a;
    std::cin>>b;

    if(simularStr(a, b)) {
        std::cout<<"YES";
    } else {
        std::cout<<"NO";
    }

    return 0;
}
