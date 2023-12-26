#include <initializer_list>
#include "algorithm"
enum class Color { RED, BLACK };

template<typename T>
struct Node {
    T key;
    Node* left;
    Node* right;
    Node* parent;
    Color color;
    Node() : left(nullptr), right(nullptr), parent(nullptr), color(Color::RED) {}
    Node(T key) : key(key), left(nullptr), right(nullptr), parent(nullptr), color(Color::RED) {}
};

template<typename T>
class RBTree {
public:
    int _size = 0;
    Node<T>* root{};

    RBTree() {Node<T>* root = nullptr;}

    RBTree(std::initializer_list<T> list) {
        std::for_each(list.begin(), list.end(), [this](const T& key) { insert(key);});
    }

    void delete_tree(Node<T>* _value) {
        if (_value == 0) return;
        delete_tree((*_value).left), delete_tree((*_value).right),
                delete _value;
    }

    ~RBTree() {
        _size = 0;
        delete_tree(root);
    }

    bool empty() const {
        return root == 0;
    }


    void insert(T _value) {
        if (find(_value) != 0) return;
        _size++;
        Node<T>* New_Node = new Node<T>(_value);
        Node<T>* first = 0;
        Node<T>* second = this->root;

        while (second != 0) {
            first = second;
            if (New_Node->key < second->key) second = (*second).left;
            else second = (*second).right;
        }

        (*New_Node).parent = first;
        if (first == 0) this->root = New_Node;
        else if ((*New_Node).key < (*first).key) (*first).left = New_Node;
        else (*first).right = New_Node;

        if ((*New_Node).parent == 0) {
            (*New_Node).color = Color::BLACK;
            return;
        }

        if ((*New_Node).parent->parent == 0) return;
        fixInsert(New_Node);
    }

    void fixInsert(Node<T>* _value) {
        Node<T>* experiment;
        while ((*_value).parent != 0 && (*_value).parent->color == Color::RED) {
            if ((*_value).parent == (*_value).parent->parent->right) {
                experiment = (*_value).parent->parent->left;
                if (experiment != 0 && (*experiment).color == Color::RED ) {
                    (*experiment).color = Color::BLACK;
                    (*(*_value).parent).color = Color::BLACK;
                    (*(*(*_value).parent).parent).color = Color::RED;
                    _value = (*(*_value).parent).parent;
                } else {
                    if (_value == (*(*_value).parent).left) _value = (*_value).parent, rotateRight(_value);
                    (*(*_value).parent).color = Color::BLACK;
                    (*(*(*_value).parent).parent).color = Color::RED;
                    rotateLeft((*(*_value).parent).parent);
                }
            } else {
                experiment = (*_value).parent->parent->right;

                if (experiment != 0 && (*experiment).color == Color::RED) {
                    (*experiment).color = Color::BLACK;
                    (*_value).parent->color = Color::BLACK;
                    (*_value).parent->parent->color = Color::RED;
                    _value = (*_value).parent->parent;
                } else {
                    if (_value == (*_value).parent->right) _value = (*_value).parent, rotateLeft(_value);
                    (*(*_value).parent).color = Color::BLACK;
                    (*(*(*_value).parent).parent).color = Color::RED;
                    rotateRight((*(*_value).parent).parent);
                }
            }
            if (_value == root) break;
        }
        (*root).color = Color::BLACK;
    }

    void rotateLeft(Node<T>* _value) {
        Node<T>* second = (*_value).right;
        (*_value).right = (*second).left;
        if ((*second).left != 0) (*(*second).left).parent = _value;
        (*second).parent = (*_value).parent;

        if ((*_value).parent == 0) this->root = second;
        else if (_value == (*(*_value).parent).left) (*(*_value).parent).left = second;
        else (*(*_value).parent).right = second;

        (*second).left = _value;
        (*_value).parent = second;
    }

    void rotateRight(Node<T>* _value) {
        Node<T>* second = (*_value).left;
        (*_value).left = (*second).right;

        if ((*second).right != 0) (*(*second).right).parent = _value;
        (*second).parent = (*_value).parent;

        if ((*_value).parent == 0) this->root = second;
        else if (_value == (*(*_value).parent).right) (*(*_value).parent).right = second;
        else (*(*_value).parent).left = second;

        (*second).right = _value;
        (*_value).parent = second;
    }

    int size() const { return _size; }

    T* lowerBound(T key) const {
        Node<T>* NODDE = root;
        T* lowerBound = 0;

        while (NODDE != 0) {
            if ((*NODDE).key < key) NODDE = (*NODDE).right;
            else lowerBound = &(*NODDE).key, NODDE = (*NODDE).left;
        }
        return lowerBound;
    }

    T* find(T _value) const {
        Node<T>* current = root;
        while (current != 0) {
            if ((*current).key == _value) return &(*current).key;
            if ((*current).key > _value) current = (*current).left;
            else current = (*current).right;
        }
        return nullptr;
    }
};
//финальное решение
