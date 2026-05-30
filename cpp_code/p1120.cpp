#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 70;

int n, sum = 0, frag[MAXN];
bool vis[MAXN];

bool dfs(int done, int curl, int pos, const int div, const int len) {
    if (done == div) return true;
    if (curl == len) 
        return dfs(done + 1, 0, 0, div, len);
    int skip = 0;
    for (int i = pos; i < n ; ++i) {
        if (vis[i] || frag[i] == skip) 
            continue;
        if (frag[i] + curl <= len) {
            vis[i] = true;
            if (dfs(done, curl + frag[i], i + 1, div, len)) 
                return true;
            skip = frag[i];
            vis[i] = false;
            if (curl == 0 || curl + frag[i] == len) 
                return false;
        }
    }
    return false;
}

int solve() {
    int start = max(sum / n , frag[0]);
    for (int len = start; len <= sum / 2; ++len) {
        if (sum % len != 0) continue;
        int div = sum / len;
        memset(vis, 0, sizeof(vis));
        if (dfs(0, 0, 0, div, len)) 
            return len;
    }
    return sum;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> frag[i];
        sum += frag[i];
    }
    sort(frag, frag + n, greater<int>());
    int ans = solve();
    cout << ans << '\n';
}