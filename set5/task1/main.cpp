#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <vector>

// Элемент хеш-таблицы - список объектов с одним хешем
template <class KeyType, class ValueType>
struct Node {
    KeyType key_;
    ValueType value_;
    Node *next_;

    Node(KeyType key, ValueType value) : key_(key), value_(value), next_(nullptr){};
};

// Хеш-таблица
template <class KeyType, class ValueType, class Func = std::hash<KeyType>>
class HashTable {
public:
    HashTable() : HashTable(100, 0.5) {}
    HashTable(Func function) : HashTable(100, 0.5, function) {}
    HashTable(size_t maxsizeTable, double fillingFactor, Func hasher = Func()) : maxsizeTable_(maxsizeTable), hasher_(hasher), table_(maxsizeTable, nullptr), sizeTable_(0) {
        if (fillingFactor > 0 && fillingFactor <= 1) {
            fillingFactor_ = fillingFactor;
        } else {
            fillingFactor_ = 0.5;
        }
    }



    ~HashTable() {
        for (int i = 0; i < table_.size(); ++i) {
            Node<KeyType, ValueType>* node = table_[i];
            while (node != nullptr) {
                Node<KeyType, ValueType>* temp = node->next_;
                delete node;
                node = temp;
            }
        }
    }

    void insert(KeyType key, ValueType value) {

        // Вставка элемента в конец цепочки с проверкой, если ли элементы с одинаковым ключом.
        size_t hashV = hasher_(key) % maxsizeTable_;
        if (table_[hashV] == nullptr) {
            table_[hashV] = new Node(key, value);
        } else {
            Node<KeyType, ValueType>* nodeCheck = table_[hashV];
            //Проверка идет до цикла т.к. первый элемент может иметь похожий ключ
            if (nodeCheck->key_ == key) {
                nodeCheck->value_ = value;
                return;
            }
            //затем в каждой итерации цикла и в конце, когда nodeCheck->next_ == nullptr.
            while (nodeCheck->next_ != nullptr) {
                if (nodeCheck->key_ == key) {
                    nodeCheck->value_ = value;
                    return;
                }
                nodeCheck = nodeCheck->next_;
            }
            if (nodeCheck->key_ == key) {
                nodeCheck->value_ = value;
                return;
            }
            nodeCheck->next_ = new Node(key, value);
        }
        ++sizeTable_; // кол-во элементов

        if (static_cast<double>(sizeTable_) / static_cast<double>(maxsizeTable_) > fillingFactor_) {
            table_.resize(maxsizeTable_ * 2, nullptr);
            for (size_t i = 0; i < table_.size() / 2; ++i) {
                Node<KeyType, ValueType>* last = nullptr; // создаем предыдущую ноду, для того чтобы иметь связь с нодой которая является node->next
                auto node = table_[i];
                while (node != nullptr) { // тут спускаемся пока не закончатся узлы
                    size_t hash = hasher_(node->key_) % maxsizeTable_; // new index in table_
                    if (hash == i) { // если хеш код совпал, то мы передвигаем ноду дальше, а к предыдущей ноде присваиваем значение текущей ноды
                        last = node;
                        node = node->next_;
                    } else {

                        if (last == nullptr) { // если наша надо было в самом верху цепочки, то мы говорим, что в самом верху будет node->next_
                            table_[hash] = node->next_;
                        } else { // если это не так, то удаляем связь с предыдущей нодой и связываем last с node->next
                            last->next_= node->next_;
                        }
                        Node<KeyType, ValueType>* temp = node->next_;
                        node->next_ = nullptr; // разрываем связь с цепочкой
                        if  (table_[hash] != nullptr) { // если место под новым индексом пустое и там нет цепочки, но вставляем туда наш узел
                            Node<KeyType, ValueType>* nodeONPOS = table_[hash]; // иначе берем находящийся на месте узел и двигаемся вниз пока не дойдем до пустого места
                            while(nodeONPOS->next_ != nullptr) {
                                nodeONPOS = node->next_;
                            }
                            nodeONPOS->next_ = node; // туда вставляем наш узел
                        } else {
                            table_[hash] = node;
                        }
                        node = temp;
                    }
                }
            }

        }
    }




    ValueType* find(KeyType key) {
        size_t hashv = hasher_(key) % maxsizeTable_;
        Node<KeyType, ValueType>* node = table_[hashv];
        while (node->next_ != nullptr) {
            if (node->key_ == key) {
                return &node->value_;
            }
            node = node->next_;
        }
        if (node->key_ == key) {
            return &node -> value_;
        }
        return nullptr;

    }
    void erase(KeyType key) {
        size_t hashv = hasher_(key) % table_.size();
        Node<KeyType, ValueType>* node = table_[hashv];
        if (node->key_ == key) {
            table_[hashv] = node->next_;
            delete node;
            sizeTable_ -= 1;
            return;
        }
        Node<KeyType, ValueType>* prev = node;
        node = node->next_;
        while (node->next_ != nullptr) {
            if (node->key_ == key) {
                prev->next_ = node->next_;
                delete node;
                sizeTable_ -= 1;
                return;
            }
            prev = node;
            node = node->next_;
        }
        if (node->key_ == key) {
            prev->next_ = node->next_;
            delete node;
            sizeTable_ -= 1;
            return;
        }
    }



    Node<KeyType, ValueType> &operator[](uint64_t a) {
        if (a > capacity()) {
            throw std::out_of_range("Hash code outside the table");
        } if (table_[a] == nullptr) {
            throw std::runtime_error("Run Time");
        }
        return *table_[a];
    }
    Node<KeyType, ValueType> at(uint64_t a) {
        if (a > capacity()) {
            throw std::out_of_range("Hash code outside the table");
        } if (table_[a] == nullptr) {
            throw std::runtime_error("Run Time");
        }
        return *table_[a]; // вот это я не понял че такое
    }

    size_t size() const { // возвращает кол-во элементов в таблице
        return sizeTable_;
    }
    size_t capacity() const  { // возвращает текущее значение емкости таблицы
        return maxsizeTable_;
    }



private:
    std::vector<Node<KeyType, ValueType>*> table_;
    size_t maxsizeTable_;
    size_t sizeTable_;
    double fillingFactor_;
    Func hasher_;

};

