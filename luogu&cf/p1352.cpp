#include <bits/stdc++.h>
using namespace std;

class TreeDP {
private:
    int n;
    vector<int> value;
    vector<vector<int>> graph;

    vector<bool> has_father; //记录是否有父节点（上司）
    vector<array<int, 2>> dp;

    int get_root() {
        int root = 0;
        while (has_father[root]) 
            root++;
        return root;
    }

    void dfs(int u, int father) {
        dp[u][1] = value[u];
        for (auto v : graph[u]) {
            if (v == father) 
                continue;
            dfs(v, u);
            dp[u][0] += max(dp[v][0], dp[v][1]);
            dp[u][1] += dp[v][0];
        }
    }

public:
    TreeDP(int n, vector<int> v, vector<vector<int>> g, vector<bool> hf): 
    n(n), value(v), graph(g), has_father(hf) {
        dp.resize(n, {0, 0}); // 0和1两种状态，对应选和不选，全部初始化为0
    }

    int max_value() {
        int root = get_root();
        dfs(root, -1);
        return max(dp[root][0], dp[root][1]);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    vector<int> value(n);
    vector<vector<int>> graph(n); // 一般使用无向图，方便后面进阶的换根等等进阶操作
    vector<bool> has_father(n, false);
    for (int i = 0; i < n; i++) 
        cin >> value[i];
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> v >> u;
        graph[v - 1].push_back(u - 1); //记得减1，因为我的索引是从0开始的
        graph[u - 1].push_back(v - 1);
        has_father[v - 1] = true;
    }

    TreeDP solver(n, value, graph, has_father);
    int ans = solver.max_value();
    cout << ans << '\n';

    return 0;
}