#include <bits/stdc++.h>
using namespace std;

string str;
struct Node {
    int w;
    Node* le; Node* ri;
    Node(int w, Node* l, Node* r): w(w), le(l), ri(r) {}
};

Node* build_tree(int &dep) {
    if (dep >= str.size()) return nullptr;
    if (isdigit(str[dep])) {
        int w = 0;
        while (isdigit(str[dep])) {
            w = w * 10 + (str[dep] - '0');
            ++dep;
        }
        return new Node(w, nullptr, nullptr);
    } 
    else if (str[dep] == '[') {
        ++dep;
        Node* node = new Node(0, nullptr, nullptr);
        node->le = build_tree(dep);
        ++dep;  //跳过逗号
        node->ri = build_tree(dep);
        ++dep;  //跳过 ']'
        node->w = node->le->w + node->ri->w;
        return node;
    }
    return nullptr;
}

void print_tree(Node* root) {
    if (!root) return;
    cout << root->w << ' ';
    print_tree(root->le);
    print_tree(root->ri);
}

void clean(Node* node) {
    if (!node) return;
    clean(node->le);
    clean(node->ri);
    delete node;
}

int main() {
    str = "[[2,3],[4,5]]";
    int idx = 0;
    Node* root = build_tree(idx);
    print_tree(root);
    cout << '\n';
    clean(root);
    return 0;
}