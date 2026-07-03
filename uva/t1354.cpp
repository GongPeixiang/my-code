#include <bits/stdc++.h>
using namespace std;

constexpr int N = 6;

int n; bool vis[1<<N];
double maxr, w[N], sum[1<<N];
struct Tree { double l, r; };
vector<Tree> tree[1<<N];

void dfs(int stat) {
    if (vis[stat]) return;
    vis[stat] = true;
    bool flg = false; // has child
    for (int le = (stat-1) & stat; le; le = (le-1) & stat) { // 枚举子集
        flg = true;
        int ri = stat ^ le;
        double dl = sum[le] / sum[stat], dr = sum[ri] / sum[stat];
        dfs(le); dfs(ri);
        for (Tree tl: tree[le]) {
            for (Tree tr: tree[ri]) {
                Tree t;
                t.l = max(tl.l + dl, tr.l - dr);
                t.r = max(tr.r + dr, tl.r - dl);
                if (t.l + t.r < maxr) tree[stat].push_back(t);
            }
        }
    }
    if (!flg) tree[stat].push_back(Tree{0, 0});
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int T;
    cin >> T;
    while (T--) {
        memset(vis, 0, sizeof(vis));
        memset(sum, 0, sizeof(sum));
        cin >> maxr >> n;
        for (int i = 0; i < n; ++i) cin >> w[i];
        for (int stat = 0; stat < (1 << n); ++stat) {
            tree[stat].clear();
            for (int i = 0; i < n; ++i) {
                if ((1 << i) & stat) sum[stat] += w[i];
            }
        }
        int root = (1 << n) - 1;
        dfs(root);
        double ans = -1;
        for (auto t: tree[root]) ans = max(ans, t.l + t.r);
        if (ans != -1) cout << fixed << setprecision(10) << ans << '\n';
        else cout << "-1\n";
    }
    return 0;
}