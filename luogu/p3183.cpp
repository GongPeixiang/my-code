#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 100005, MAXM = 200005;

int n, m, memo[MAXN];
vector<int> graph[MAXN];
bool has_father[MAXN], has_son[MAXN];

int dfs(int start) {
    if (memo[start] != -1) return memo[start];
    if (!has_son[start]) return 1;
    int cnt = 0;
    for (int son : graph[start]) 
        cnt += dfs(son);
    memo[start] = cnt;
    return memo[start];
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    memset(has_father, 0, sizeof(has_father));
    memset(has_son, 0, sizeof(has_son));
    memset(memo, 0xff, sizeof(memo));
    while (m--) {
        int from, to;
        cin >> from >> to;
        has_father[--to] = true;
        has_son[--from] = true;
        graph[from].push_back(to);
    }

    vector<int> sources;
    for (int i = 0; i < n; i++) 
        if (!has_father[i]) sources.push_back(i);
    int ans = 0;
    for (int src: sources) 
        if (has_son[src]) ans += dfs(src);

    cout << ans << '\n';
}