#include <bits/stdc++.h>
using namespace std;

struct Node {
    int val;
    Node *left, *right;
    Node(int v, Node *l = nullptr, Node *r = nullptr):
        val(v), left(l), right(r) {}
};

vector<unique_ptr<Node>> all_nodes;

bool insert(Node *&root, int val)
{
    auto new_node = make_unique<Node>(val);
    if (root == nullptr) {
        root = new_node.get();
        all_nodes.push_back(move(new_node));
        return true;
    }

    Node *cur = root, *parent = nullptr;
    while (cur != nullptr) {
        parent = cur;
        if (val < cur->val) 
            cur = cur->left;
        else if (val > cur->val) 
            cur = cur->right;
        else 
            return false;
    }

    if (val < parent->val)
        parent->left = new_node.get();
    else if (val > parent->val) 
        parent->right = new_node.get();

    all_nodes.push_back(move(new_node));
    return true;
}

void level_traversal(Node *root)
{
    if (!root) {
        cout << "[]" << '\n';
        return;
    }
    queue<Node *> q;
    q.push(root);
    bool first = true;
    cout << '[';
    while (!q.empty()) {
        Node *node = q.front();
        q.pop();
        if (!first) cout << ',';
        first = false;

        if (node) {
            cout << node->val;
            q.push(node->left);
            q.push(node->right);
        } 
        else 
            cout << "null";
    }
    cout << ']' << '\n';
}

int main()
{
    Node *tree = nullptr;
    insert(tree, 11);
    insert(tree, 1);
    insert(tree, 4);
    insert(tree, 20);
    insert(tree, 21);
    insert(tree, 9);

    level_traversal(tree);
}