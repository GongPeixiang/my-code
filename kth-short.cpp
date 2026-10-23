#include <bits/stdc++.h>
using namespace std;

using pii = pair<int,int>;

constexpr int N = 5005;

int n, m, k, dis[N], cnt[N]; // dis[u]是节点u到终点的最短路(从终点反向跑一遍dij)
vector<pii> G[N];
struct Node {
    int u, g, f;
    bool operator<(const Node& other) const { return f > other.f; }
};

int kth_short() {
    priority_queue<Node, vector<Node>> pq;
    pq.push((Node){0, 0, dis[0]});
    while (pq.size()) {
        Node cur = pq.top(); pq.pop();
        int u = cur.u, g = cur.g, f = cur.f;
        cnt[u]++;
        if (u == n-1 && cnt[u] == k) return f;
        if (cnt[u] > k) continue;
        for (auto& vw: G[u]) {
            int v = vw.first, w = vw.second;
            int ng = g + w;
            pq.push((Node){v, ng, ng+dis[v]});
        }
    }
    return -1;
}

void rev_dij() {
    memset(dis, 0x3f, sizeof(dis));
    dis[n-1] = 0;
    auto cmp = [](pii& a, pii &b){ return a.second > b.second; };
    priority_queue<pii, vector<pii>, decltype(cmp)> pq(cmp);
    pq.push(make_pair(n-1, 0));
    while (pq.size()) {
        pii cur = pq.top(); pq.pop();
        int u = cur.first, d = cur.second;
        if (d > dis[u]) continue;
        for (auto& vw: G[u]) {
            int v = vw.first, w = vw.second;
            if (d + w < dis[v]) {
                dis[v] = d + w;
                pq.push(make_pair(v, dis[v]));
            }
        }
    }
}

int main() {
    scanf("%d%d%d", &n, &m, &k);
    int u, v, w;
    for (int i = 0; i < m; i++) {
        scanf("%d%d%d", &u, &v, &w);
        u--; v--;
        G[u].push_back(make_pair(v, w));
        G[v].push_back(make_pair(u, w));
    }
    rev_dij();
    int ans = kth_short();
    printf("%d\n", ans);
    return 0;
}