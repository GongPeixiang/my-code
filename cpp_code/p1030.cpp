#include <bits/stdc++.h>
using namespace std;

struct Node {
    char data;
    Node *left, *right;
    Node() : left(nullptr), right(nullptr) {}
    Node(char val) : data(val), left(nullptr), right(nullptr) {}
};

string in_order, post_order;

Node *build_tree(int i_start, int i_end, int p_start, int p_end)
{
    if (i_start > i_end) 
        return nullptr;
    char root_val = post_order[p_end];
    Node *root = new Node(root_val);
    int pos = in_order.find(root_val);
    root->left = build_tree(i_start, pos - 1, p_start, p_start + pos - 1 - i_start);
    root->right = build_tree(pos + 1, i_end, p_start + pos - i_start, p_end - 1);
    return root;
}

void pre_traversal(Node *root)
{
    if (!root)
        return;
    cout << root->data;
    pre_traversal(root->left);
    pre_traversal(root->right);
}

void free_bst(Node *root)
{
    if (!root) 
        return;
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
    Node *root = build_tree(0, len - 1, 0, len - 1);
    pre_traversal(root);
    cout << '\n';
    free_bst(root);
    return 0;
}