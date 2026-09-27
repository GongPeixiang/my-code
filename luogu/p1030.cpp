#include <bits/stdc++.h>
using namespace std;

struct Node {
    char data;
    Node* left; Node*right;
    Node() : left(nullptr), right(nullptr) {}
    Node(char val) : data(val), left(nullptr), right(nullptr) {}
};

string in_order, post_order;

Node* build_tree(int is, int ie, int ps, int pe) {
    if (is > ie) return nullptr;
    char root_val = post_order[pe];
    Node* root = new Node(root_val);
    int pos = in_order.find(root_val);
    root->left = build_tree(is, pos - 1, ps, ps + pos - 1 - is);
    root->right = build_tree(pos + 1, ie, ps + pos - is, pe - 1);
    return root;
}

void pre_traversal(Node* root) {
    if (!root) return;
    cout << root->data;
    pre_traversal(root->left);
    pre_traversal(root->right);
}

void free_bst(Node* root) {
    if (!root) return;
    free_bst(root->left);
    free_bst(root->right);
    delete root;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> in_order >> post_order;
    int len = in_order.size();
    Node* root = build_tree(0, len - 1, 0, len - 1);
    pre_traversal(root);
    cout << '\n';
    free_bst(root);
    return 0;
}