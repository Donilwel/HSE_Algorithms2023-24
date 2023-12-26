x#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

struct Node {
    int _value;
    bool Check_Red;
    int l;
    int r;

    Node(int k, bool red) : _value(k), Check_Red(red), l(0), r(0) {}
};

class RedBlackTree {
public:
    std::unordered_map<int, Node *> Nodde;

    void Inserter(int number, int key, const std::string &left, const std::string &right, bool redder) {
        Nodde[number] = new Node(key, redder);
        if (right != "null")(*Nodde[number]).r = std::stoi(right);
        if (left != "null") (*Nodde[number]).l = std::stoi(left);

    }

    bool Correct(int root) {
        if (Nodde[root]->Check_Red) return false;

        for (int i = 1; i <= Nodde.size(); ++i) {
            if (((*Nodde[i]).l != 0 && (*Nodde[i])._value < (*Nodde[(*Nodde[i]).l])._value) ||
                ((*Nodde[i]).r != 0 && (*Nodde[i])._value > (*Nodde[(*Nodde[i]).r])._value)) {
                return false;
            }
        }

        std::vector<int> blackCounts;
        if (bool_ch(root, 0, blackCounts) == false) return false;
        auto checker = blackCounts[0];
        for (int i = 1; i <= blackCounts.size() - 1; ++i) if (blackCounts[i] != checker) return false;

        return true;
    }

    bool bool_ch(int thisNode, int Black_Counter, std::vector<int> &black_node_count) {
        if (thisNode == 0) {
            black_node_count.push_back(Black_Counter + 1);
            return true;
        }

        if ((*Nodde[thisNode]).Check_Red == false) Black_Counter++;

        if (Nodde[thisNode]->Check_Red &&
            ((Nodde[thisNode]->l != 0 &&
              Nodde[Nodde[thisNode]->l]->Check_Red) ||
             (Nodde[thisNode]->r != 0 && (*Nodde[(*Nodde[thisNode]).r]).Check_Red))) {
            return false;
        }

        return bool_ch((*Nodde[thisNode]).r, Black_Counter, black_node_count) &&
               bool_ch(Nodde[thisNode]->l, Black_Counter, black_node_count);}
};

int main() {

    int n;
    std::cin >> n;
    if (n == 0) { std::cout << "NO"; return 0;}
    else {
        RedBlackTree redBlackTree;

        int thisRoot;
        std::cin >> thisRoot;

        for (int i = 0; i < n; i++) {
            int number, key;
            std::string left, right, color;
            std::cin >> number >> key >> left >> right >> color;
            bool check_on_red = false;
            if (color == "R") check_on_red = true;
            redBlackTree.Inserter(number, key, left, right, check_on_red);
        }
        if (redBlackTree.Correct(thisRoot)) std::cout << "YES";
        else std::cout << "NO";
    }
//финальное решение я не понимаю почему когда я хочу облегчить его то у меня] либо тайм лимит либо просто RE но ничего страшного все равно иду на экзамен поэтому до встречи на нем :)
}
