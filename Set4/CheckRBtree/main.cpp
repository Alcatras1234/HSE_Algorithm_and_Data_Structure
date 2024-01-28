#include <iostream>
#include <map>
#include <climits>

struct Node {
public:
    int position;
    int key;
    Node* left;
    Node* right;
    char color;

};

bool isBinarySearchTree(Node* root, int minValue, int maxValue) {
    if (root == nullptr) {
        return true;
    }

    if (root->key < minValue || root->key > maxValue) {
        return false;
    }

    return isBinarySearchTree(root->left, minValue, root->key) &&
           isBinarySearchTree(root->right, root->key, maxValue);
}

bool is_RBtree(std::map<int, Node>& items, Node* root, int& blacknodes) {
    if (root == nullptr) {
        blacknodes = 0;
        return true;
    }

    int leftBlackH, rightBlackH;
    bool left = is_RBtree(items, root->left, leftBlackH);
    bool right = is_RBtree(items, root->right, rightBlackH);
    blacknodes = leftBlackH + (root->color == 'B' ? 1: 0);

    if (!left || !right || leftBlackH != rightBlackH) {
        return false;
    }
    return true;
}

int main() {
    int height;
    int root_index;
    std::cin>>height>>root_index;
    if (height == 0) {
        std::cout << "NO";
        return 0;
    }
    std::map<int, Node> elements;
    for (int i = 0; i < height; ++i) { //enter elemets in array
        Node newNode;
        std::string nullchl;
        std::string nullchr;
        int number;
        int key;
        char color;
        std::cin >> newNode.position >> newNode.key >> nullchl >> nullchr >> newNode.color;
        if (nullchl == "null") {
            newNode.left = nullptr;
        } else {

            newNode.left = &elements[std::stoi(nullchl)];
        }
        if (nullchr == "null") {
            newNode.right = nullptr;
        } else {
            newNode.right = &elements[std::stoi(nullchr)];
        }
        elements[newNode.position] = newNode;
    }
    int blacknodes = 0;
    Node* root = &elements[root_index];
    bool flag = is_RBtree(elements, root, blacknodes);
    if (flag && isBinarySearchTree(root, INT_MIN, INT_MAX)) {
        std::cout<<"YES";
    } else {
        std::cout<<"NO";
    }
    return 0;
}
