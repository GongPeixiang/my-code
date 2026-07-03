#include <bits/stdc++.h>
using namespace std;

constexpr int N = 205;

int tgt, cap[3], ans[N];
bool vis[N][N];
struct Node {
    int v[3], dist;
    bool operator<(const Node& other)const { return dist > other.dist; }
};

int solve() {
    memset(vis, 0, sizeof(vis));
    memset(ans, 0xff, sizeof(ans));
    priority_queue<Node, vector<Node>> pq;
    Node init;
    init.v[0] = init.v[1] = 0, init.v[2] = cap[2];
    init.dist = 0;
    pq.push(init);
    while (!pq.empty()) {
        Node cur = pq.top(); pq.pop();
        for (int i = 0; i < 3; ++i) {
            int w = cur.v[i];
            if (ans[w] == -1 || cur.dist < ans[w]) ans[w] = cur.dist;
        }
        if (~ans[tgt]) break;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (i == j) continue;
                Node u = cur;
                int vol = min(cap[j], u.v[i] + u.v[j]) - u.v[j];
                u.dist += vol;
                u.v[i] -= vol, u.v[j] += vol;
                if (!vis[u.v[0]][u.v[1]]) {
                    vis[u.v[0]][u.v[1]] = true;
                    pq.push(u);
                }
            }
        }
    }
    if (ans[tgt] == -1) {
        int d = tgt;
        while (d-- && d >= 0) if (~ans[d]) return d;
    }
    return tgt;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int T;
    cin >> T;
    while (T--) {
        cin >> cap[0] >> cap[1] >> cap[2] >> tgt;
        int d = solve();
        cout << ans[d] << ' ' << d << '\n';
    }
    return 0;
}