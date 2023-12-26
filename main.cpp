#include <iostream>
#include <cmath>

struct Node {
    int data;
    Node* left;
    Node* right;
};

class BinaryTree {
private:
    Node* root;

    Node* insertNode(Node* root, int data) {
        if (root == nullptr) {
            Node* newNode = new Node();
            newNode->data = data;
            newNode->left = nullptr;
            newNode->right = nullptr;
            return newNode;
        }

        if (data < root->data) {
            root->left = insertNode(root->left, data);
        } else if (data > root->data) {
            root->right = insertNode(root->right, data);
        }

        return root;
    }

    int getHeight(Node* node) {
        if (node == nullptr) {
            return -1;
        }

        int leftHeight = getHeight(node->left);
        int rightHeight = getHeight(node->right);

        return 1 + std::max(leftHeight, rightHeight);
    }

    bool isBalanced(Node* node) {
        if (node == nullptr) {
            return true;
        }

        int leftHeight = getHeight(node->left);
        int rightHeight = getHeight(node->right);

        int heightDiff = std::abs(leftHeight - rightHeight);

        if (heightDiff > 1) {
            return false;
        }

        return isBalanced(node->left) && isBalanced(node->right);
    }

public:
    BinaryTree() {
        root = nullptr;
    }

    void insert(int data) {
        root = insertNode(root, data);
    }

    bool isAVL() {
        return isBalanced(root);
    }
};

int main() {
    BinaryTree tree;
    int num;
    do {
        std::cin >> num;
        if (num != 0) {
            tree.insert(num);
        }
    } while (num != 0);

    if (tree.isAVL()) {
        std::cout << "YES" << std::endl;
    } else {
        std::cout << "NO" << std::endl;
    }

    return 0;
}
