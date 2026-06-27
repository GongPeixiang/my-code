#include <bits/stdc++.h>
using namespace std;

constexpr int MAXM = 55, MAXN = 1005;

int m, n, timber[MAXM], need[MAXN], cpy[MAXN];

bool dfs(const int div, int done, int cur) {
    if (done == div) return true;
    if (n - cur + done < div) return false;
    for (int i = 0; i < m; ++i) {
        if (timber[i] >= need[cur]) {
            timber[i] -= need[cur];
            if (dfs(div, done + 1, cur + 1)) 
                return true;
            timber[i] += need[cur];
        }
    }
    return dfs(div, done, cur + 1);
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> m;
    for (int i = 0; i < m; ++i) cin >> timber[i];
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> need[i];
    sort(need, need + n); sort(timber, timber + m);
    memcpy(cpy, timber, sizeof(timber));
    // 把问题转化成给定个数下的可行性验证
    // 利用二分, 极大地减少搜索个数
    int ans = 0;
    int l = 0, r = n;
    while (l <= r) {
        int mid = (l + r) / 2;
        memcpy(timber, cpy, sizeof(timber));
        if (dfs(mid, 0, 0)) {
            ans = mid;
            l = mid + 1;
        }
        else r = mid - 1;
    }
    cout << ans << '\n';
}