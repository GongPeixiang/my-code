#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> graph;
int cnt = 0;
vector<vector<int>> sccs;

void dfs(int u, vector<int> &dfn, vector<int> &low, vector<bool> in_stack, 
    stack<int> &s) {
    dfn[u] = low[u] = cnt++;
    s.push(u);
    in_stack[u] = true;

    for (int v : graph[u]) {
        if (dfn[v] == -1) {
            dfs(v, dfn, low, in_stack, s);
            low[u] = min(low[u], low[v]);
        }
        else if (in_stack[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }

    if (low[u] == dfn[u]) {
        vector<int> scc;
        while (1) {
            int w = s.top(); s.pop();
            scc.push_back(w);
            in_stack[w] = false;
            if (w == u) 
                break;
        }
        sccs.push_back(scc);
    }
}

void tarjan_solve(const int n, const vector<pair<int, int>> &edges) {
    stack<int> s;
    vector<int> dfn(n, -1), low(n, -1);
    vector<bool> in_stack(n, false);
    graph.resize(n);

    for (const auto &[u, v] : edges) 
        graph[u].push_back(v);
    
    for (int i = 0; i < n; i++) {
        if (dfn[i] == -1) {
            dfs(i, dfn, low, in_stack, s);
        }
    }
}

int main() {
    vector<pair<int, int>> edges = { {0, 1}, {0, 3}, {1, 2}, {2, 0}, 
    {3, 4}, {4, 5}, {5, 3} };

    tarjan_solve(6, edges);

    for (const auto &scc : sccs) {
        for (int v : scc) 
            cout << v << ' ';
        cout << '\n';
    }
}