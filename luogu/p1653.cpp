#include <bits/stdc++.h>
using namespace std;

constexpr int H = 505, N = H*H;
constexpr int E = N*4;

int W, L, h[H][H];
int head[N], to[E], nxt[E], ecnt = -1;
stack<int> stk;
int dfn[N], low[N], dfncnt = 0, vis[N], scc[N], scc_cnt = 0;
int in[N], out[N];

void add_edge(int x, int y, int xx, int yy) {
    if (xx < 0 || xx >= L || yy < 0 || yy >= W) return;
    if (h[x][y] < h[xx][yy]) return;
    int u = x * W + y, v = xx * W + yy;
    to[++ecnt] = v;
    nxt[ecnt] = head[u];
    head[u] = ecnt;
}

void tar(int u) {
    dfn[u] = low[u] = ++dfncnt;
    vis[u] = 1;
    stk.push(u);
    for (int i = head[u]; ~i; i = nxt[i]) {
        int v = to[i];
        if (!dfn[v]) {
            tar(v);
            low[u] = min(low[u], low[v]);
        } else if (vis[v] == 1) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if (low[u] == dfn[u]) {
        int v;
        scc_cnt++;
        do {
            v = stk.top(); stk.pop();
            vis[v] = 2;
            scc[v] = scc_cnt;
        } while (v != u);
    }
}

int main() {
    memset(head, -1, sizeof(head));
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> W >> L;
    for (int i = 0; i < L; i++) 
        for (int j = 0; j < W; j++) 
            cin >> h[i][j];
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < W; j++) {
            add_edge(i, j, i - 1, j);
            add_edge(i, j, i + 1, j);
            add_edge(i, j, i, j - 1);
            add_edge(i, j, i, j + 1);
        }
    }
    for (int i = 0; i < W*L; i++) 
        if (!dfn[i]) tar(i);
    if (scc_cnt == 1) { cout << "0\n"; return 0; }
    for (int u = 0; u < W*L; u++) {
        for (int i = head[u]; ~i; i = nxt[i]) {
            int v = to[i];
            if (scc[u] != scc[v]) {
                in[scc[v]]++;
                out[scc[u]]++;
            }
        }
    }
    int p = 0, q = 0;
    for (int i = 1; i <= scc_cnt; i++) {
        if (!in[i]) p++;
        if (!out[i]) q++;
    }
    cout << max(p, q) << '\n';
    return 0;
}