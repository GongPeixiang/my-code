#include <bits/stdc++.h>

constexpr int MAXM = 50;
constexpr int MAXN = 1000;

int n, m;
int timber[MAXM], cpy[MAXM], need[MAXN];

bool dfs(const int k, int done, int cur) {
    if (done == k) 
        return true;
    if (done + n - cur < k) 
        return false;
    for (int i = cur; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (timber[j] >= need[i]) {
                timber[j] -= need[i];
                if (dfs(k, done + 1, i + 1)) 
                    return true;
                timber[j] += need[i];
            }
        }
    }
    return false;
}

int solve() {
    int l = 0, r = n;
    memcpy(cpy, timber, sizeof(timber));
    while (l <= r) {
        int mid = l + (r - l) / 2;
        memcpy(timber, cpy, sizeof(timber));
        if (dfs(mid, 0, 0)) 
            l = mid + 1;
        else 
            r = mid - 1;
    }
    return l - 1;
}

int main() {
    std::cin >> m;
    for (int i = 0; i < m; ++i) 
        std::cin >> timber[i];
    std::cin >> n;
    for (int i = 0; i < n; ++i) 
        std::cin >> need[i];
    int ans = solve();
    std::cout << ans << '\n';
    return 0;
}