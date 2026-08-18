#include <bits/stdc++.h>
using namespace std;

constexpr int N = 65;

int n, s, d, g[N][N], minlen = 0x3f3f3f3f;
bool vis[N];
vector<int> path, ans;

// check if current path is lexicographically smaller.
bool check() {
    int l = min(path.size(), ans.size());
    for (int i = 0; i < l; i++) {
        if (path[i] < ans[i]) return true;
        else if (path[i] > ans[i]) return false;
    }
    return false;
}

void dfs(int cur, int len) {
    if (len > minlen) return;
    if (cur == d) {
        if (len < minlen) {
            minlen = len;
            ans = path;
        }
        else if (len == minlen && check()) ans = path;
        return;
    }
    for (int i = 0; i < n; i++) {
        if (~g[cur][i] || !vis[i]) {
            vis[i] = true;
            path.push_back(i);
            dfs(i, len + g[cur][i]);
            path.pop_back();
            vis[i] = false;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> s >> d;
    for (int i = 0; i < n; i++) 
        for (int j = 0; j < n; j++) 
            cin >> g[i][j];
    vis[s] = true;
    path.push_back(s);
    dfs(s, 0);
    if (ans.size() == 0) cout << "-1\n";
    else {
        cout << ans[0];
        for (int i = 1; i < ans.size(); i++) cout << "->" << ans[i];
    }
    return 0;
}