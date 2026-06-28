#include <bits/stdc++.h>
using namespace std;

struct DetectCycle {
    enum class Status : int {to_visit, visiting, visited};
    const int n;
    const vector<vector<int>> &graph;
    vector<Status> vis;
    DetectCycle(const vector<vector<int>> &g):
        n(g.size()), graph(g), vis(n, Status::to_visit) {}

    bool dfs(int u) {
        vis[u] = Status::visiting;
        for (int v : graph[u]) {
            if (vis[v] == Status::visiting) 
                return true;
            else if (vis[v] == Status::to_visit) {
                if (dfs(v)) 
                    return true;
            }
        }
        vis[u] = Status::visited;
        return false;
    }

    bool check_cycle() {
        for (int i = 0; i < n; i++) {
            if (vis[i] == Status::to_visit) {
                if (dfs(i)) 
                    return true;
            }
        }
        return false;
    }
};