#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<vector<int>> graph;
vector<int> in;
vector<int> seq;
vector<bool> exist;
int mark = 1e5;

bool topo_sort(int idx, vector<int> &cpy_in) {
    queue<int> q;
    bool unique = true;
    for (int i = 0; i < n; i++) {
        if (cpy_in[i] == 0 && exist[i]) 
            q.push(i);
    }
    while (!q.empty()) {
        if (q.size() > 1) 
            unique = false;
        int u = q.front();
        q.pop();
        seq.push_back(u);
        for (int v : graph[u]) {
            if (--cpy_in[v] == 0) {
                q.push(v);
            }
        }
    }
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if (exist[i]) 
            cnt++;
    }
    if (seq.size() < cnt) 
        return false;
    if (seq.size() == n && unique) 
        mark = min(idx, mark);
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    graph.resize(n);
    in.resize(n, 0);
    exist.resize(n, false);
    string line;
    for (int i = 1; i <= m; i++) {
        seq.clear();
        cin >> line;
        int u = line[0] - 'A', v = line[2] - 'A';
        in[v]++;
        exist[u] = exist[v] = true;
        vector<int> cpy_in = in;
        graph[u].push_back(v);
        if (!topo_sort(i, cpy_in)) {
            cout << "Inconsistency found after " << i << 
            " relations." << '\n'; 
            return 0;
        } 
    }
    if (mark != 1e5) {
        cout << "Sorted sequence determined after " << mark <<
            " relations: ";
        for (int u : seq)
            cout << (char)(u + 'A');
    }
    else 
        cout << "Sorted sequence cannot be determined." << '\n';
}