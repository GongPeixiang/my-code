// khan算法
#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<vector<int>> aov_graph;
vector<int> in;

bool topo_sort() {
    vector<int> seq;
    queue<int> s;
    for (int i = 0; i < n; i++) {
        if (!in[i]) 
            s.push(i);
    }
    while (!s.empty()) {
        int u = s.front();
        s.pop();
        seq.push_back(u);
        for (int v : aov_graph[u]) {
            if (--in[v] == 0) 
                s.push(v);
        }
    }
    if (seq.size() == n) {
        for (int u : seq) 
            cout << u << ' ';
        return true;
    }
    return false;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    aov_graph.resize(n);
    in.resize(n, 0);
    int u, v;
    for (int i = 0; i < m; i++) {
        cin >> u >> v;
        in[v]++;
        aov_graph[u].push_back(v);
    }
    topo_sort();
}