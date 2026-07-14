#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 25;

int n, max_sum, bomb[MAXN];
vector<int> path, final_path;
vector<pair<int, int>> adj[MAXN];

void dfs(int sum, int u) {
    auto uc = adj[u];
    if (uc.empty()) {
        if (sum > max_sum) {
            max_sum = sum;
            final_path = path;
        }
        return;
    }
    int len = uc.size();
    for (int i = 0; i < len; i++) {
        int v = uc[i].second;
        path.push_back(v);
        dfs(sum + bomb[v], v);
        path.pop_back();
    }
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) 
        cin >> bomb[i];
    for (int i = 0; i < n; i++) {
        int tmp;
        for (int j = i + 1; j < n; j++) {
            cin >> tmp;
            if (tmp == 1) adj[i].push_back({i, j});
        }
    }
    for (int u = 0; u < n; u++) {
        path.push_back(u);
        dfs(bomb[u], u);
        path.pop_back();
    }
    for (auto u : final_path) 
        cout << u + 1 << ' ';
    cout << '\n' << max_sum << '\n';
    return 0;
}