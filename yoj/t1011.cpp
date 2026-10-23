// DFS序嵌套 + 树状数组
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr int N = 100005;

int n, in[N], out[N], timer = 0;
ll tree[N*2];
vector<int> g[N];

namespace bit { // bit for fenwick tree
// lowbit(x): x & -x
void add(int x, ll k) { 
    while (x <= timer) {
        tree[x] += k;
        x += x & -x;
    }
}

ll sum(int x) {
    ll s = 0;
    while (x) {
        s += tree[x];
        x -= x & -x;
    }
    return s;
}
}

void dfs(int u) {
    in[u] = ++timer;
    for (int v: g[u]) dfs(v);
    out[u] = ++timer;
}

void add(int u, ll k) {
    bit::add(in[u], k);
    bit::add(out[u], -k);
}

inline ll get_sum(int u) { return bit::sum(in[u]); }

int main() {
    int T;
    scanf("%d%d", &n, &T);
    int fa;
    for (int i = 2; i <= n; i++) {
        scanf("%d", &fa);
        g[fa].push_back(i);
    }
    dfs(1);
    char op; int x; ll k;
    while (T--) {
        scanf(" %c %d", &op, &x);
        if (op == 'q') printf("%lld\n", get_sum(x));
        else if (op == 'a') {
            scanf("%lld", &k);
            add(x, k);
        }
    }
    return 0;
}