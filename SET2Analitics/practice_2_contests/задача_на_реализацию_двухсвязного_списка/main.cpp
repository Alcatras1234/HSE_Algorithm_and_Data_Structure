#include <vector>
#include <stdexcept>
#include <iostream>

struct Node {
    Node* next;
    Node* previous;
    int data;

    Node() : next(nullptr), previous(nullptr) {}
    Node(int valiue) : next(nullptr), previous(nullptr), data(valiue){}
};

class DoublyLinkedList {
public:
    Node* head;
    Node* tail;

    DoublyLinkedList(): head(nullptr), tail(nullptr) {}
    DoublyLinkedList(const DoublyLinkedList& other) : tail(nullptr), head(nullptr) {
        Node* current = other.head;
        while (current) {
            pushBack(current->data);
            current = current->next;
        }
    }
    DoublyLinkedList(std::vector<int>& array) : head(nullptr), tail (nullptr) {
        for (int i : array) {
            pushBack(i);
        }
    }
    ~DoublyLinkedList() {
        erase();
    }

    void pushBack(int data) {
        Node* new_node = new Node(data);
        if (tail == nullptr) {
            head = new_node;
            tail = new_node;
        } else {
            tail->next = new_node;
            new_node->previous = tail;
            tail = new_node;
        }
    }
    void pushFront(int data) {
        Node* new_node = new Node(data);
        if (head == nullptr) {
            head = new_node;
            tail = new_node;
        } else {
            new_node->next = head;
            head->previous = new_node;
            head = new_node;
        }

    }
    void insert(Node* prev, int data) {
        if (prev == nullptr || prev->next == nullptr) {
            throw std::runtime_error("Wrong position for insertion!");
        }
        Node* new_node = new Node(data);
        new_node->previous = prev;
        new_node->next = prev->next;
        prev->next->previous = new_node;
        prev->next = new_node;
    }
    void popFront() {
        if (head == nullptr) {
            throw std::runtime_error("Deletion error!");
        }
        Node* temp = head;
        head = head->next;
        if (head != nullptr) {
            head->previous = nullptr;
        } else {
            tail = nullptr;
        }
        delete temp;
    }
    void popBack() {
        if (tail == nullptr) {
            throw std::runtime_error("Deletion error!");
        }

        Node* temp = tail;
        tail = tail->previous;
        if (tail != nullptr) {
            tail->next = nullptr;
        } else {
            head = nullptr;
        }
        delete temp;
    }
    void pop(Node* pos) {
        if (pos == nullptr) {
            throw std::runtime_error("Wrong position for deletion!");
        }
        if (pos == head) {
            popFront();
            return;
        } else if (pos == tail) {
            popBack();
            return;
        }
        for (Node* i = head; i != tail; i = i->next) {
            if (i == pos) {
                pos->next->previous = pos->previous;
                pos->previous->next = pos->next;
                delete pos;
                return;
            }
        }
        throw std::runtime_error("Wrong position for deletion!");
    }
    void erase() {
        while (tail) {
            popBack();
        }
    }
    void reverse() {
        Node* current = head;
        Node* temp = nullptr;
        while (current) {
            temp = current->next;
            current->next = current->previous;
            if (temp != nullptr){
                current->previous = temp;
                current = temp;
            } else {
                current->previous = nullptr;
                current = nullptr;
            }
        }
        temp = head;
        head = tail;
        tail = temp;
    }
    void removeDuplicates() {
        Node* current = head;
        while (current) {
            Node* current_next = current->next;
            while (current_next) {
                if (current->data == current_next->data) {
                    pop(current_next);
                }
                current_next = current_next->next;
            }
            current = current_next;
        }
    }
    void replace(int oldElem, int newElem) {
        Node* current = head;
        while (current) {
            if (current->data == oldElem) {
                current->data = newElem;
            }
            current = current->next;
        }
    }

};

