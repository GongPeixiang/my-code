// NOI2001
// 种类并查集
#include <bits/stdc++.h>
using namespace std;

const int N = 50005;

int n, m, fa[N*3];

void init() { for (int i = 1; i <= n*3; i++) fa[i] = i; }

int find(int x) { return x == fa[x] ? x : fa[x]=find(fa[x]); }

int main() {
    scanf("%d%d", &n, &m);
    init();
    int d, u, v;
    int ans = 0;
    while (m--) {
        scanf("%d%d%d", &d, &u, &v);
        if (u > n || v > n) { ans++; continue; }
        if (d == 1) {
            if (find(u)==find(v+n) || find(u+n)==find(v)) { ans++; continue; }
            fa[find(v)] = find(u);
            fa[find(v+n)] = find(u+n);
            fa[find(v+2*n)] = find(u+2*n);
        } else if (d == 2) {
            if (find(u)==find(v) || find(u+n)==find(v)) { ans++; continue; }
            fa[find(v)] = find(u+2*n);
            fa[find(v+n)] = find(u);
            fa[find(v+2*n)] = find(u+n);
        }
    }
    printf("%d\n", ans);
    return 0;
}