#include <bits/stdc++.h>
using namespace std;

int n, s, d;
vector<vector<int>> road;
int min_len = numeric_limits<int>::max();
vector<int> final_path;

// check if current path is lexicographically smaller.
bool judge(const vector<int> &path) {
    int la = path.size(), lb = final_path.size();
    int l = min(la, lb);
    for (int i = 0; i < l; i++) {
        if (path[i] < final_path[i]) 
            return true;
        else if (path[i] > final_path[i]) 
            return false;
    }
    return false;
}

void dfs(int cur, vector<bool> &visited, vector<int> &path, int len) {
    if (len > min_len) 
        return;

    if (cur == d) {
        if (len < min_len) {
            min_len = len;
            final_path = path;
        }
        else if (len == min_len && judge(path)) {
            final_path = path;
        }
        return;
    }

    for (int i = 0; i < n; i++) {
        if (road[cur][i] == -1 || visited[i]) 
            continue;

        visited[i] = true;
        path.push_back(i);

        dfs(i, visited, path, len + road[cur][i]);

        path.pop_back();
        visited[i] = false;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    road.resize(n, vector<int> (n));
    cin >> s >> d;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> road[i][j];
        }
    }

    vector<bool> visited(n,false);
    vector<int> path;

    visited[s] = true;
    path.push_back(s);

    dfs(s, visited, path, 0);

    int len = final_path.size();
    if (len == 0) 
        cout << -1 << '\n';
    else {
        for (int i = 0; i < len - 1; i++) 
            cout << final_path[i] << "->";
        cout << final_path[len - 1] << '\n';
    }

    return 0;
}