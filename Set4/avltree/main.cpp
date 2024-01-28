#include <iostream>
#include <vector>
#include <cmath>

class Node {
public:
    int key;
    Node* left;
    Node* right;
    Node (int value) {
        key = value;
        left = nullptr;
        right = nullptr;
    }
};

class BinaryTree {
public:
    Node* root;
    BinaryTree() {
        root = nullptr;
    }

    void insert_root(int key) {
        root = insert(root, key);
    }

    Node* insert(Node* node_root, int key) {
        if (node_root == nullptr) {
            return new Node(key);
        }
        if (key < node_root->key) {
            node_root->left = insert(node_root->left, key);
        } else if (key > node_root->key) {
            node_root->right = insert(node_root->right, key);
        }

        return node_root;
    }


    int height(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return 1 + std::max(height(node->left), height(node->right));
    }
    bool root_is_AVL() {
        return check_AVL(root);
    }
    bool check_AVL(Node* node) {
        if (node == nullptr) {
            return true;
        }
        int left_h = height(node->left);
        int right_h = height(node->right);

        if (abs(left_h - right_h) <= 1 && check_AVL(node->left) && check_AVL(node->right)) {
            return true;
        } else {
            return false;
        }
    }

};


int main() {
    BinaryTree tree;
    int a;
    while (true) {
        std::cin>>a;
        if (a != 0) {
            tree.insert_root(a);
        } else {
            break;
        }
    }
    if (tree.root_is_AVL()) {
        std::cout<<"YES";
    } else {
        std::cout<<"NO";
    }
    return 0;
}
