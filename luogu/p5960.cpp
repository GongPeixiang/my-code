/* 
 * difference constraints
 * 当无负环时，最短路一定能给出一组特解(最短路的三角不等式约束)
 */
#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;

const int N = 5005, M = 5005;

int n, m, dis[N], cnt[N];
vector<pii> g[N];
bool inq[N];

bool spfa() {
    memset(dis, 0x3f, sizeof(dis));
    dis[0] = 0;
    queue<int> q;
    q.push(0);  inq[0] = 1;
    while (q.size()) {
        int u = q.front(); q.pop();
        inq[u] = 0;
        int v, w;
        for (auto& pr: g[u]) {
            tie(v,w) = pr;
            if (dis[u] + w < dis[v]) {
                dis[v] = dis[u] + w;
                cnt[v] = cnt[u] + 1;
                if (cnt[v] >= n+1) return false;
                if (!inq[v]) {
                    q.push(v);
                    inq[v] = 1;
                }
            }
        }
    }
    return true;
}

int main() {
    scanf("%d%d", &n, &m);
    int u, v, w;
    for (int i = 1; i <= n; i++) g[0].push_back(make_pair(i, 0));
    for (int i = 1; i <= m; i++) {
        scanf("%d%d%d", &u, &v, &w);
        g[v].push_back(make_pair(u, w));
    }
    bool flg = spfa();
    if (!flg) {
        printf("NO\n");
        return 0;
    }
    for (int i = 1; i <= n; i++) printf("%d%c", dis[i], " \n"[i==n]);
    return 0;
}