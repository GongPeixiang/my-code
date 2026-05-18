#include <bits/stdc++.h>
using namespace std;

int n, max_sum;
vector<int> bomb, final_path;
vector<vector<pair<int, int>>> adj;

void dfs(int sum, vector<int> &path, int u) {
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
        dfs(sum + bomb[v], path, v);
        path.pop_back();
    }
}

int main() {
    cin >> n;
    bomb.resize(n); adj.resize(n);
    for (int i = 0; i < n; i++) cin >> bomb[i];
    for (int i = 0; i < n; i++) {
        int tmp;
        for (int j = i + 1; j < n; j++) {
            cin >> tmp;
            if (tmp == 1) 
                adj[i].push_back({i, j});
        }
    }
    vector<int> path;
    for (int u = 0; u < n; u++) {
        path.push_back(u);
        dfs(bomb[u], path, u);
        path.pop_back();
    }
    for (auto u : final_path) 
        cout << u + 1 << ' ';
    cout << '\n' << max_sum << '\n';
    return 0;
}