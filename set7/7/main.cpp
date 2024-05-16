#include <iostream>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <fstream>
#include <map>

struct Node {
    char ch;
    int freq; // частота
    Node *left;
    Node *right;

    Node(char ch, int freq, Node *left, Node *right) : ch(ch), freq(freq), left(left), right(right) {}

//    // Сравнение по частоте, нужно для priority_queue
//    bool operator<(const Node& other) const {
//        if (freq != other.freq) {
//            return freq > other.freq;
//        } else {
//            return ch > other.ch;
//        }
//    }
};

struct CompareNodes {
    bool operator()(const Node *a, const Node *b) const {
        return a->freq > b->freq;
    }
};


Node *buildHafmanTree(std::map<char, int> &freqList) {
    std::priority_queue<Node *, std::vector<Node *>, CompareNodes> pq;
    for (auto &pair: freqList) {
        if (pair.second > 0) {
            pq.push(new Node(pair.first, pair.second, nullptr, nullptr));
        }
    }
    while (pq.size() > 1) {
        //Слияние двух деревьев с наименьшей частотой
        Node *x = pq.top();
        pq.pop();
        Node *y = pq.top();
        pq.pop();

        Node *parent = new Node('#', x->freq + y->freq, x, y);
        if (x->ch <= y->ch && (x->ch != '#' && y->ch != '#')) {
            parent->left = x;
            parent->right = y;
        } else if (x->ch >= y->ch && (x->ch != '#' && y->ch != '#')) {
            parent->left = y;
            parent->right = x;
        }
        pq.push(parent);
    }

    return pq.top(); // возвращаем корень дерева.
}

void generateCodes(Node *root, std::string code, std::map<char, std::string> &codes) {
    if (!root) {
        return;
    }
    if (root->ch != '#') {
        if (code == "") {
            codes[root->ch] = '0';
        } else {
            codes[root->ch] = code;
        }
    } else {

        generateCodes(root->left, code + '0', codes);
        generateCodes(root->right, code + '1', codes);
    }
}

void deleteTree(Node *root) {
    if (root) {
        deleteTree(root->left);
        deleteTree(root->right);
        delete root;
    }
}

std::string Encode(std::map<char, std::string> &codes, std::string &str) {
    std::string result;
    for (auto ch: str) {
        result += codes[ch];
    }
    return result;
}

int main() {
    std::string a;
    std::cin >> a;

    // подсчитаем частоты символов

    std::map<char, int> freqList;
    for (char &ch: a) {
        freqList[ch]++;
    }


    // построим дерево
    Node *root = buildHafmanTree(freqList);

    std::map<char, std::string> codes;

    generateCodes(root, "", codes);


    std::string code = Encode(codes, a);


    std::cout << freqList.size() << " " << code.length() << std::endl;
    for (auto pair: codes) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
    std::cout << code;

    deleteTree(root);

    return 0;
}
