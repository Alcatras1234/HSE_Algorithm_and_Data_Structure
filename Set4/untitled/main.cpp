#include <iostream>
#include <vector>
#include <map>



struct Node {
    int number, key;
    Node* left;
    Node* right;
    char color;
};

bool isRedBlackTree(std::map<int, Node>& nodes, Node* root, int& blackHeight) {
    if (root == nullptr) {
        blackHeight = 0;
        return true;
    }
    if (root->left->key > root->key || root->right->key < root->key) {
        return false;
    }
    int leftBlackHeight, rightBlackHeight;
    bool leftValid = isRedBlackTree(nodes, root->left, leftBlackHeight);
    bool rightValid = isRedBlackTree(nodes, root->right, rightBlackHeight);

    blackHeight = leftBlackHeight + (root->color == 'B' ? 1 : 0);

    if (!leftValid || !rightValid || leftBlackHeight != rightBlackHeight) {


        return false;
    }

    return true;
}

int main() {
    int n;
    std::cin >> n;

    if (n == 0) {
        std::cout << "NO";
        return 0;
    }

    int rootIndex;
    std::cin >> rootIndex;

    std::map<int, Node> nodes;

    for (int i = 0; i < n; ++i) {
        Node newNode;
        std::cin >> newNode.number >> newNode.key;

        int leftIndex, rightIndex;
        std::string leftStr, rightStr;
        std::cin >> leftStr >> rightStr;

        if (leftStr == "null") {
            newNode.left = nullptr;
        } else {
            leftIndex = stoi(leftStr);
            newNode.left = &nodes[leftIndex];
        }

        if (rightStr == "null") {
            newNode.right = nullptr;
        } else {
            rightIndex = stoi(rightStr);
            newNode.right = &nodes[rightIndex];
        }

        std::cin >> newNode.color;
        nodes[newNode.number] = newNode;
    }

    Node* root = &nodes[rootIndex];
    int blackHeight;

    if (isRedBlackTree(nodes, root, blackHeight)) {
        std::cout << "YES";
    } else {
        std::cout << "NO";
    }

    return 0;
}
