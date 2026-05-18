#include <bits/stdc++.h>
using namespace std;

// 预处理
void pre_process(const vector<array<bool, 6>> &connect, 
    vector<array<array<bool, 6>, 6>> &re_connect) 
{
    re_connect.resize(connect.size());
    for (int i = 0; i < connect.size(); i++) {
        for (int r = 0; r < 6; r++) {
            for (int j = 0; j < 6; j++) {
                int after_rotate = (j + r) % 6;
                re_connect[i][r][after_rotate] = connect[i][j];
            }
        }
    }
}

struct MyHash {
    size_t operator()(const pair<int, int> &p) const {
        size_t h1 = hash<int> {} (p.first);
        size_t h2 = hash<int> {} (p.second);
        return h1 ^ (h2 + 0x9e3779b9 + (h1 << 6) + (h1 >> 2));
    }
};

struct HashEqual {
    bool operator()(const pair<int, int> &p, 
        const pair<int, int> &q) const {
        return p.first == q.first && p.second == q.second;
    }
};

vector<pair<int, int>> bfs_solve(int src, int dst, 
    vector<array<int, 6>> &neighbor, vector<array<bool, 6>> &connect) {
    if (src == dst) 
        return {};

    vector<array<array<bool, 6>, 6>> re_connect;
    pre_process(connect, re_connect);

    queue<pair<int, int>> q;  // 格子编号和旋转情况
    unordered_map<pair<int, int>, pair<int, int>, 
        MyHash, HashEqual> prev;

    for (int r = 0; r < 6; r++) {
        q.push(make_pair(src, r));
        prev[make_pair(src, r)] = make_pair(-1, -1);
    }

    while (!q.empty()) {
        auto cur_state = q.front();
        int u = cur_state.first, ru = cur_state.second;
        q.pop();

        if (u == dst) {
            vector<pair<int, int>> path;
            pair<int, int> track = make_pair(u, ru);
            while (track.first != -1) {
                if (track.second != 0) 
                    path.push_back(track);
                track = prev[track];
            }
            reverse(path.begin(), path.end());
            return path;
        }
        
        const auto &un = neighbor[u];
        const auto &uc = re_connect[u][ru];

        for (int us = 0; us < 6; us++) {  // us代表6条边
            if (un[us] == -1 || !uc[us]) 
                continue;
            
            int v = un[us]; 
            int vs = (us + 3) % 6;

            for (int rv = 0; rv < 6; rv++) {
                auto const &vc = re_connect[v][rv];
                if (vc[vs]) {
                    if (!prev.count(make_pair(v, rv))) {
                        prev[make_pair(v, rv)] = make_pair(u, ru);
                        q.push(make_pair(v, rv));
                    }
                }
            }
        }
    }
    return {};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, src = -1, dst = -1;
    cin >> n;
    vector<array<int, 6>> neighbor(n);
    vector<array<bool, 6>> connect(n);
    int type;
    for (int i = 0; i < n; i++) {
        cin >> type;
        switch(type) {
            case 0: src = i; break;
            case 2: dst = i; break;
            default: break;
        }
        for (int r = 0; r < 6; r++) {
            cin >> neighbor[i][r];
            neighbor[i][r]--;
        }
        for (int r = 0; r < 6; r++) {
            int tmp; 
            cin >> tmp;
            connect[i][r] = tmp == 1 ? true : false;
        }
    }

    vector<pair<int, int>> path = bfs_solve(src, dst, neighbor, connect);
    cout << path.size() << '\n';
    for (const auto &state : path) {
        int grid = state.first + 1;
        int rotate = state.second;
        cout << grid << ' ' << 'R' << ' ' << rotate << '\n';
    }
}