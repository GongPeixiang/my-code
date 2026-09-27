#include <bits/stdc++.h>
using namespace std;

constexpr int N = 105;

int n, p;
struct Node { int c, u; } node[N];
struct Edge {
    int i, j, w;
} edge[N*N]; // 链式前向星

int tot = -1, head[N], nxt[N], in[N], out[N];
bool first[N];

inline void add_edge(int i, int j, int w) {
    edge[++tot] = Edge{i, j, w};
    nxt[tot] = head[i];
    head[i] = tot;
    ++in[j], ++out[i];
}

void toposort() {
    queue<int> q;
    for (int i = 1; i <= n; ++i) {
        if (!in[i]) {
            q.push(i);
            first[i] = true;
        }
    }
    while (!q.empty()) {
        int i = q.front(); q.pop();
        if (!first[i]) 
            node[i].c -= node[i].u;
        if (node[i].c > 0) {
            for (int k = head[i]; ~k; k = nxt[k]) {
                int j = edge[k].j, wij = edge[k].w;
                node[j].c += node[i].c * wij;
                if (--in[j] == 0) 
                    q.push(j);
            }
        }
    }
}

int main() {
    memset(head, 0xff, sizeof(head));
    memset(nxt, 0xff, sizeof(nxt));
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> p;
    for (int i = 1; i <= n; ++i) 
        cin >> node[i].c >> node[i].u;
    int i, j, w;
    for (int k = 0; k < p; ++k) {
        cin >> i >> j >> w;
        add_edge(i, j, w);
    }
    toposort();
    bool flg = false;
    for (int i = 1; i <= n; ++i) {
        if (!out[i] && node[i].c > 0) {
            cout << i << ' ' << node[i].c << '\n';
            flg = true;
        } 
    }
    if (!flg) cout << "NULL\n";
    return 0;
}