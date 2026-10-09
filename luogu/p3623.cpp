#include <bits/stdc++.h>
using namespace std;

constexpr int N = 20005, M = 100005;

int n, m, k, fa[N];
struct Edge {
    int u, v, w;
} e[M];
vector<int> ans;
bool vis[M];

void init() { for (int i = 1; i <= n; i++) fa[i] = i; }

int find(int x) { return x == fa[x] ? x : fa[x]=find(fa[x]); }

/* 3遍kruskal
 * 第一遍先判断是否连通，并确定必须加的石子路；
 * 第二遍确定必须加的水泥路；
 * 第三遍补全 */
int main() {
    scanf("%d%d%d", &n, &m, &k);
    int tot = 0, cnt1 = 0;
    init();
    for (int i = 1; i <= m; i++) {
        scanf("%d%d%d", &e[i].u, &e[i].v, &e[i].w);
        if (!e[i].w) continue;
        int fu = find(e[i].u), fv = find(e[i].v);
        if (fu != fv) {
            fa[fv] = fu;
            tot++;
        }
    }
    for (int i = 1; i <= m; i++) {
        if (e[i].w) continue;
        int fu = find(e[i].u), fv = find(e[i].v);
        if (fu != fv) {
            fa[fv] = fu;
            ans.push_back(i);
            tot++;
            cnt1++;
        }
        if (cnt1 > k) {
            printf("no solution\n");
            return 0;
        }
    }
    if (tot != n-1) { //不连通
        printf("no solution\n");
        return 0;
    }

    init();
    int cnt2 = 0;
    for (int i = 1; i <= m; i++) {
        if (e[i].w) continue;
        int fu = find(e[i].u), fv = find(e[i].v);
        if (fu != fv) fa[fv] = fu;
    }
    for (int i = 1; i <= m; i++) {
        if (!e[i].w) continue;
        int fu = find(e[i].u), fv = find(e[i].v);
        if (fu != fv) {
            fa[fv] = fu;
            ans.push_back(i);
            cnt2++;
        }
        if (cnt2 > n-1-k) {
            printf("no solution\n");
            return 0;
        }
    }

    init();
    for (int eid: ans) {
        vis[eid] = 1;
        int fu = find(e[eid].u), fv = find(e[eid].v);
        if (fu != fv) fa[fv] = fu;
    }
    for (int i = 1; i <= m; i++) {
        if (vis[i]) continue;
        int fu = find(e[i].u), fv = find(e[i].v);
        if (e[i].w && cnt2 < n-1-k && fu != fv) {
            fa[fv] = fu;
            ans.push_back(i);
            cnt2++;
        } else if (!e[i].w && cnt1 < k && fu != fv) {
            fa[fv] = fu;
            ans.push_back(i);
            cnt1++;
        }
    }
    for (int eid: ans) printf("%d %d %d\n", e[eid].u, e[eid].v, e[eid].w);
    return 0;
}