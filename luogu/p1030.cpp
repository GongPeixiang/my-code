#include <bits/stdc++.h>
using namespace std;

constexpr int LEN = 10;

struct Node {
    char data;
    Node* left; Node* right;
    Node() : left(nullptr), right(nullptr) {}
    Node(char val) : data(val), left(nullptr), right(nullptr) {}
};
char in[LEN], post[LEN];

Node* build_tree(int is, int ie, int ps, int pe) {
    if (is > ie) return nullptr;
    char rtval = post[pe];
    Node* root = new Node(rtval);
    int pos = strchr(in, rtval) - in;
    root->left = build_tree(is, pos-1, ps, ps+pos-1-is);
    root->right = build_tree(pos+1, ie, ps+pos-is, pe-1);
    return root;
}

void dfs(Node* root) {
    if (!root) return;
    printf("%c", root->data);
    dfs(root->left);
    dfs(root->right);
}

void free_bst(Node* root) {
    if (!root) return;
    free_bst(root->left);
    free_bst(root->right);
    delete root;
}

int main() {
    scanf("%s%s", in, post);
    int len = strlen(in);
    Node* root = build_tree(0, len-1, 0, len-1);
    dfs(root);
    putchar('\n');
    free_bst(root);
    return 0;
}