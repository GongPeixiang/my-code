#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<vector<int>> caves, memo;
vector<vector<int>> sccs;

class Tarjan {
public:
    int cnt;
    stack<int> s;
    vector<int> dfn, low;
    vector<bool> in_stack; 
    Tarjan() {
        cnt = 0;
        dfn.resize(n * m, -1);
        low.resize(n * m, -1);
        in_stack.resize(n * m, false);
    }

    void get_sccs() {
        for (int i = 0; i < n * m; i++) {
            if (dfn[i] == -1) 
                dfs(i);
        }
    }
private:
    void dfs(int u) {
        dfn[u] = low[u] = cnt++;
        s.push(u);
        in_stack[u] = true;

        int r = u / m, c = u % m;
        int nr, nc;
        switch (caves[r][c]) {
            case 1: nr = r, nc = c - 1; break;
            case 2: nr = r, nc = c + 1; break;
            case 3: nr = r - 1, nc = c; break;
            case 4: nr = r + 1, nc = c; break;
            default: break;
        }
        if (nr >= 0 && nr < n && nc >= 0 && nc < m) {
            int v = nr * m + nc;
            if (dfn[v] == -1) {
                dfs(v);
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
};

void process_cycle() {
    for (const auto &scc : sccs) {
        if (scc.size() == 1) 
            continue;
        for (auto idx : scc) {
            int r = idx / m, c = idx % m;
            memo[r][c] = scc.size();
        }
    }
}

int max_len(int r, int c) {
    if (memo[r][c] != -1) 
        return memo[r][c];
    int nr, nc;
    switch (caves[r][c]) {
        case 1: nr = r, nc = c - 1; break;
        case 2: nr = r, nc = c + 1; break;
        case 3: nr = r - 1, nc = c; break;
        case 4: nr = r + 1, nc = c; break;
    }
    int max_num = 1;
    if (nr >= 0 && nr < n && nc >= 0 && nc < m) {
        max_num += max_len(nr, nc);
    }
    memo[r][c] = max_num;
    return memo[r][c];
}

struct Info {
    int r, c;
    int num;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> m >> n;
    caves.resize(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> caves[i][j];
        }
    }
    memo.resize(n, vector<int>(m, -1));

    Tarjan tarjan;
    tarjan.get_sccs();
    process_cycle();

    vector<Info> all_info;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int num = max_len(i, j);
            all_info.push_back({i, j, num});
        }
    }

    sort(all_info.begin(), all_info.end(), [](const Info &a, const Info &b) {
        if (a.num != b.num) 
            return a.num > b.num;
        if (a.c != b.c) 
            return a.c < b.c;
        if (a.r != b.r) 
            return a.r < b.r;
        return false;
    });
    for (const auto &info : all_info) {
        if (info.num < all_info[0].num) 
            break;
        cout << info.c << ' ' << info.r << '\n'; 
    }
}