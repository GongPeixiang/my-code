#include <bits/stdc++.h>
using namespace std;

constexpr int N = 2005, M = 10005;

int n, m, in[N], cpy[N], t[N], ans[N];
vector<int> rg[N]; // rev-graph

auto cmp = [](int a, int b) { return t[a] < t[b]; }; // big-heap

void topo() {
    int cnt = 0;
    priority_queue<int,vector<int>, decltype(cmp)> pq(cmp);
    for (int i = 1; i <= n; i++) 
        if (in[i] == 0) pq.push(i);
    while (!pq.empty()) {
        int cur = pq.top(); pq.pop();
        ans[cnt++] = cur;
        for (int to: rg[cur]) {
            if (--in[to] == 0) pq.push(to);
        }
    }
    for (int i = cnt - 1; i >= 0; i--) printf("%d%c", ans[i], " \n"[i == 0]);
}

int calc(int x) {
    int tot = 0;
    memcpy(in, cpy, sizeof(in));
    priority_queue<int,vector<int>, decltype(cmp)> pq(cmp);
    for (int i = 1; i <= n; i++) if (!in[i]) pq.push(i);
    while (!pq.empty()) {
        int cur = pq.top(); pq.pop();
        if (cur == x) continue;
        if (n - tot > t[cur]) break;
        tot++;
        for (int to: rg[cur]) 
            if (--in[to] == 0) pq.push(to);
    }
    return n - tot;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", &t[i]);
    int a, b;
    for (int i = 0; i < m; i++) {
        scanf("%d%d", &a, &b);
        rg[b].push_back(a);
        in[a]++;
    }
    memcpy(cpy, in, sizeof(in));
    topo();
    for (int i = 1; i <= n; i++) printf("%d ", calc(i));
    putchar('\n');
    return 0;
}