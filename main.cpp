#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>

struct Node {
    Node* next;
    Node* previous;
    int data;

    Node() = default;
    explicit Node(int value) :  data(value), next(nullptr), previous (nullptr) {
    }
    Node(int value, Node* _next, Node* _prev) : data(value), next(_next), previous(_prev) {
    }
};

class DoublyLinkedList {
public:
    Node *head;
    Node *tail;

    DoublyLinkedList() : head(nullptr), tail(nullptr) {
    }

    DoublyLinkedList(const DoublyLinkedList &other) {
        Node *mid = other.head;
        if (mid == nullptr) {
            head = nullptr;
            tail = nullptr;
            return;
        }
        head = new Node{(*mid).data, nullptr, nullptr};

        Node *start = head;
        for (Node *i = (*mid).next; i != nullptr; i = (*i).next, start = (*start).next) {
            Node *node = new Node{(*i).data, nullptr, start};
            (*start).next = node;
        }
        tail = start;
    }

    explicit DoublyLinkedList(const std::vector<int> &vec) {
        if (vec.empty()) {
            head = nullptr;
            tail = nullptr;
            return;
        }
        head = new Node{vec.front(), nullptr, nullptr};

        Node *start = head;
        for (int i = 1; i < vec.size(); ++i) {
            Node *node = new Node{vec[i], nullptr, start};
            (*start).next = node;
            start = (*start).next;
        }
        tail = start;
    }

    ~DoublyLinkedList() {
        erase();
    }

    void pushBack(int data) { //NOLINT
        Node *node;
        if (head == nullptr) {
            node = new Node{data, nullptr, nullptr};
            head = node;
            tail = node;
        } else {
            node = new Node{data, nullptr, tail};
            (*tail).next = node;
            tail = node;
        }
    }

    void pushFront(int data) {
        Node *start;
        if (head == nullptr) {
            start = new Node{data, nullptr, nullptr};
            head = start;
            tail = start;
        } else {
            start = new Node{data, head, nullptr};
            (*head).previous = start;
            head = start;
        }
    }

    void insert(Node *prev, int data) {
        if (prev == nullptr) {
            throw std::runtime_error("Wrong position for insertion!");
        }
        if (head == nullptr) {
            return;
        }
        bool flag = true;
        Node *new_element;
        for (Node *iter = head; iter != nullptr; iter = iter->next) {
            if (iter == prev) {
                new_element = new Node{data, nullptr, prev};
                new_element->next = iter->next;
                if (iter->next != nullptr) {
                    new_element->next->previous == new_element;
                } else {
                    tail = new_element;
                }
                iter->next = new_element;
                flag = false;
                break;
            }
        }
        if (flag) {
            throw std::runtime_error("Wrong position for insertion!");
        }
    }

    void popFront() {
        if (head == nullptr) {
            throw std::runtime_error("Deletion error!");
        }
        Node *start = (*head).next;
        if (start != nullptr) {
            (*start).previous = nullptr;
        }
        delete head;
        head = start;
        if (head == nullptr) {
            tail = nullptr;
        }
    }

    void popBack() {
        if (head == nullptr) {
            throw std::runtime_error("Deletion error!”");
        }
        Node *new_tail = tail->previous;
        if (new_tail != nullptr) {
            new_tail->next = nullptr;
        }
        delete tail;
        tail = new_tail;
        if (tail == nullptr) {
            head = nullptr;
        }
    }

    void pop(Node *pos) {
        if (pos == nullptr) {
            throw std::runtime_error("Wrong position for deletion!");
        }
        bool flag = true;
        Node *start = head;
        while(start != nullptr) {
            if (start == pos) {
                flag = false;
                if (start == head) {
                    popFront();
                    break;
                } else if (start == tail) {
                    popBack();
                } else {
                    start->previous->next = (*start).next;
                    start->next->previous = start->previous;
                    (*start).next = nullptr;
                    (*start).previous = nullptr;
                    delete start;
                }
                break;
            }
            start = (*start).next;
        }
        if (flag) {
            throw std::runtime_error("Wrong position for deletion!");
        }
    }

    void erase() {
        if (head == nullptr) {
            return;
        }
        Node *start = head;
        while(start != nullptr) {
            Node *iter_na_next = (*start).next;
            (*start).next = nullptr;
            (*start).previous = nullptr;
            delete start;
            start = iter_na_next;
        }
        head = nullptr;
        tail = nullptr;
    }

    void reverse() {
        if (head == tail) {
            return;
        }
        Node *statr = head;
        while(statr != nullptr) {
            Node *node = (*statr).next;
            std::swap((*statr).previous, (*statr).next);
            statr = node;
            node = nullptr;
        }

        Node *tmp = head;
        head = tail;
        tail = tmp;
    }

    void removeDuplicates() {
        std::unordered_set<int> container;
        Node *start = head;
        while (start != nullptr) {
            if (container.find((*start).data) == container.end()) {
                container.insert((*start).data);
            } else pop(start);
            start = (*start).next;
        }
    }

    void replace(int oldElem, int newElem) {
        Node* start = head;

        while(start != nullptr) {
            if((*start).data == oldElem) {
                (*start).data = newElem;
            }
            start = (*start).next;
        }
    }

};