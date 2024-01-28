#include <iostream>

enum class Color { RED, BLACK };

template <typename T>
struct Node {
    T key;
    Node<T> *left;
    Node<T> *right;
    Node<T> *parent;
    Color color;

    Node(const T &key) : key(key), left(nullptr), right(nullptr), parent(nullptr), color(Color::RED) {}
};

template <typename T>
class RBTree {
public:
    RBTree() : root(nullptr) {}
    RBTree(std::initializer_list<T> list) : nodes(list) {
        for(const auto& key : list) {
            insert(key);
        }
    }
    ~RBTree() {
        deleteTree (root);
        root = nullptr;
    }
    void deleteTree(Node<T>* node) {
        if (node == nullptr)
            return;
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }

    void insert(T key) {
        Node<T> *newNode = new Node<T>(key);
        if (root == nullptr) {
            root = newNode;
            root->color = Color::BLACK;
            return;
        }
        Node<T>* current = root;
        Node<T>* parent = nullptr;
        while (current != nullptr) {
            parent = current;
            if (newNode->key > current->key) {
                current = current->right;
            } else if (newNode->key < current->key){
                current = current->left;
            } else {
                delete newNode;
                return;
            }
        }
        newNode->parent = parent;
        if (parent == nullptr) {
            root = newNode;
        } else if (newNode->key < parent->key) {
            parent->left = newNode;
        } else {
            parent->right = newNode;
        }

    }
    int size() const {
        return sizect(root);
    }
    int sizect (Node<T>* node) const{
        if (node == nullptr) {
            return 0;
        }
        return 1 + sizect(node->left) + sizect(node->right);
    }

    bool empty() const {
        return root == nullptr;
    }

    T *lowerBound(T key) const {
        Node<T>* current = root;
        Node<T>* lowerBoundNode = nullptr;
        while (current != nullptr) {
            if (key <= current->key) {
                lowerBoundNode = current;
                current = current->left;
            } else {
                current = current->right;
            }
        }

        if (lowerBoundNode == nullptr) {
            return nullptr;
        } else {
            return &(lowerBoundNode->key);
        }
    }

    T *find(T key) const {
        Node<T>* current = root;
        while (current != nullptr) {
            if (key == current->key) {
                return &(current->key);
            } else if (key > current->key) {
                current = current->right;
            } else {
                current = current->left;
            }
        }
        return nullptr;
    }

    Node<T> *root{};
private:
    std::initializer_list<T> nodes;
};



int main() {

    RBTree<int> tree {4, 5 ,6 ,1 ,2, 9, 10};
    auto find = tree.size();
    return 0;
}
