#include <iostream>
#include <vector>


struct Node {
public:
    int key;
    Node* left;
    Node* right;
    Node* parent;

    // your code
    explicit Node (int k) : key(k), left(nullptr), right(nullptr), parent(nullptr) {}
private:
    // your code
};

class SplayTree {
public:

    SplayTree() : root(nullptr) {}

    explicit SplayTree(std::vector<int> list) : nodes(list), root(nullptr) {
        for (const int key : nodes) {
            insert(key);
        }
    }

    ~SplayTree() {
        deleteTree(root);

    }

    void deleteTree(Node* node) {
        if (node == nullptr) {
            return;
        }
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;

    }

    void insert(int key) {
        if (root == nullptr) {
            root = new Node(key);
            return;
        }
        Node* newNode = new Node(key);
        Node* current = root;
        Node* parent = nullptr;

        while(current != nullptr) {
            parent = current;
            if (newNode->key == current->key) {
                return;
            } else if (newNode->key > current->key) {
                current = current->right;
            } else {
                current = current->left;
            }

        }
        newNode->parent = parent;
        if (newNode->key < parent->key) {
            parent->left = newNode;
        } else {
            parent->right = newNode;
        }
      //  splay(newNode);
    }

    Node* find(int key) const {
        Node* current = root;
        while (current != nullptr) {
            if (key == current->key) {
                return current;
            } else if (key < current->key) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        return nullptr;
    }

    int splay(Node * node) {
        int rotate = 0;
        if (node == nullptr) {
            return 0; // Возврат 0, если узел или его родитель равны nullptr
        }

            while (node->parent != nullptr) {
                Node* parent = node->parent;
                Node* grandParent = parent->parent;
                if (grandParent == nullptr) {
                    if (node == parent->left) {
                        rotateRight(parent);

                    } else {
                        rotateLeft(parent);

                    }
                    rotate++;
                } else {
                    if (node == parent->left && parent == grandParent->left) {
                        rotateRight(grandParent);
                        rotateRight(parent);

                    } else if (node == parent->right && parent == grandParent->right) {
                        rotateLeft(grandParent);
                        rotateLeft(parent);
                    } else {
                        if (node == parent->left) {
                            rotateRight(parent);
                            rotateLeft(grandParent);

                        }  else {
                            rotateLeft(parent);
                            rotateRight(grandParent);

                        }
                    }
                    rotate++;
                }
            }

        //root = node;
        return rotate;
    }

   void rotateRight(Node* y) { //у - родитель.

        Node* x = y->left;

        y->left = x->right;

        if (x->right != nullptr) {
            x->right->parent = y;
        }
        x->parent = y->parent;
        if (y->parent == nullptr) {
            root = x;
        } else if (y == y->parent->left) {
            y->parent->left = x;
        } else {
            y->parent->right = x;
        }

        x->right = y;
        y->parent = x;
    }

   void rotateLeft(Node* y) {
       Node* x = y->right;
        y->right = x->left;

        if (x->left != nullptr) {
            x->left->parent = y;
        }
        x->parent = y->parent;
        if (y->parent == nullptr) {
            root = x;
        } else if(y == y->parent->left) {
            y->parent->left = x;
        } else {
            x->parent->right = y;
        }

        x->left = y;
        y->parent = x;
    }



    int getHeight() const {
        int height = get_height(root);
        return height;
    }
    int get_height(Node* node) const {
        if (node == nullptr) {
            return -1;
        }
        return 1 + std::max(get_height(node->left), get_height(node->right));
    }



private:
    std::vector<int> nodes;
    Node* root{};
};
