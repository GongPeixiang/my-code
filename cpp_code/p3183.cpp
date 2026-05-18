#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<vector<int>> graph;
vector<bool> has_father, has_son;
vector<int> memo;

int dfs(int start) {
    if (memo[start] != -1) 
        return memo[start];
    if (!has_son[start]) 
        return 1;

    int cnt = 0;
    for (int son : graph[start]) {
        cnt += dfs(son);
    }
    memo[start] = cnt;
    return memo[start];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    graph.resize(n);
    has_father.resize(n, false);
    has_son.resize(n, false);
    memo.resize(n, -1);
    while (m--) {
        int from, to;
        cin >> from >> to;
        from--;
        to--;
        has_father[to] = true;
        has_son[from] = true;
        graph[from].push_back(to);
    }

    vector<int> sources;
    for (int i = 0; i < n; i++) {
        if (!has_father[i]) {
            sources.push_back(i);
        }
    }
    int ans = 0;
    for (int src : sources) {
        if (has_son[src]) {
            ans += dfs(src);
        }
    }
    cout << ans << '\n';
}