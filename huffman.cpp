// huffman-tree 模板
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr int N = 500005;

char buf[N];
string dict[128];
ll cnt[N], ans = 0;
struct Node {
    char c;
    ll w;
    Node* lc; Node* rc;
    Node(char _c, ll _w): c(_c), w(_w) { lc = rc = nullptr; }
};
vector<Node*> all;

Node* huffman() {
    auto cmp = [](Node* x, Node* y) { return x->w > y->w; };
    priority_queue<Node*, vector<Node*>, decltype(cmp)> pq(cmp);
    int n = 0;
    for (int c = 0; c < 128; c++) {
        if (!cnt[c]) continue;
        Node* node = new Node(c, cnt[c]);
        pq.push(node);
        all.push_back(node);
        n++;
    }
    while (pq.size() > 1) {
        Node* x = pq.top(); pq.pop();
        Node* y = pq.top(); pq.pop();
        Node* z = new Node(n++ ,(x->w)+(y->w));
        z->lc = x; z->rc = y;
        pq.push(z);
        all.push_back(z);
    }
    return pq.top();
}

void dfs(Node* p, string code) {
    if (!(p->lc) && !(p->rc)) {
        dict[p->c] = code;
        ans += code.size() * cnt[p->c];
        return;
    }
    dfs(p->lc, code + '0');
    dfs(p->rc, code + '1');
}

int main() {
    scanf("%s", buf);
    for (char *cp = buf; *cp; cp++) {
        char c = *cp;
        cnt[c]++;
    }
    Node* root = huffman();
    dfs(root, "");
    printf("%lld\n", ans);
    for (int c = 0; c < 128; c++) {
        if (!cnt[c]) continue;
        printf("%c %s\n", (char)c, dict[c].c_str());
    }
    for (Node* x: all) delete(x);
    return 0;
}