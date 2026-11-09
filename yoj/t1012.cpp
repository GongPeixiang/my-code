// 由前序遍历序列建树("#"表示nullptr)
#include <bits/stdc++.h>
using namespace std;

const int N = 10005;

int n = 0, ans = INT_MIN;
char buf[N*100], arr[N][100];
struct Node {
    int val;
    Node* lc; Node* rc;
    Node(int _v): val(_v) { lc = rc = nullptr; }
};
Node* root;

Node* build(int& p) {
    if (strcmp(arr[p], "#")==0) {
        p++;
        return nullptr;
    }
    Node* node = new Node(stoi(arr[p]));
    p++;
    node->lc = build(p);
    node->rc = build(p);
    return node;
}

int dfs(Node* node) {
    if (!node) return 0;
    int lmax = max(0, dfs(node->lc)), rmax = max(0, dfs(node->rc));
    int cur_sum = node->val + lmax + rmax;
    ans = max(ans, cur_sum);
    return node->val + max(lmax, rmax);
}

void _del(Node* node) {
    if (!node) return;
    _del(node->lc); _del(node->rc);
    delete node;
}

int main() {
    fgets(buf, sizeof(buf), stdin);
    buf[strcspn(buf,"\n")] = '\0';
    char* tok = strtok(buf, ",");
    while (tok) {
        memcpy(arr[n], tok, sizeof(arr[n]));
        n++;
        tok = strtok(nullptr, ",");
    }
    int p = 0;
    root = build(p);
    dfs(root);
    printf("%d\n", ans);
    _del(root);
    return 0;
}