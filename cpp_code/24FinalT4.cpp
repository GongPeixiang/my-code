#include <bits/stdc++.h>
using namespace std;

using State = pair<int, int>;
constexpr int MAXN = 2005;

int n, src, dst, neighbor[MAXN][6];
bool connect[MAXN][6], re_connect[MAXN][6][6];
vector<State> path;

// 预处理
void preprocess() {
    for (int i = 0; i < n; ++i) {
        for (int r = 0; r < 6; ++r) {
            for (int j = 0; j < 6; ++j) {
                int after_rot = (j + r) % 6;
                re_connect[i][r][after_rot] = connect[i][j];
            }
        }
    }
}

struct StatHash {
    size_t operator()(const State &s) const {
        size_t h1 = hash<int>{}(s.first);
        size_t h2 = hash<int>{}(s.second);
        return h1 ^ (h2 + 0x9e3779b9 + (h1 << 6) + (h1 >> 2));
    }
};

struct HashEqual {
    bool operator()(const State &a, const State &b) const {
        return a.first == b.first && a.second == b.second;
    }
};

// bfs
void solve() {
    queue<State> q;  // 格子编号和旋转情况
    unordered_map<State, State, StatHash, HashEqual> prev;
    for (int r = 0; r < 6; ++r) {
        q.push(make_pair(src, r));
        prev[make_pair(src, r)] = make_pair(-1, -1);
    }
    while (!q.empty()) {
        auto cur_stat = q.front();
        int u = cur_stat.first, ru = cur_stat.second;
        q.pop();
        if (u == dst) {
            State track = make_pair(u, ru);
            while (track.first != -1) {
                if (track.second != 0) 
                    path.push_back(track);
                track = prev[track];
            }
            reverse(path.begin(), path.end());
            return;
        }
        for (int us = 0; us < 6; ++us) {  // us代表6条边
            if (neighbor[u][us] == -1 || !re_connect[u][ru][us]) 
                continue;
            int v = neighbor[u][us]; 
            int vs = (us + 3) % 6;
            for (int rv = 0; rv < 6; ++rv) {
                if (re_connect[v][rv][vs]) {
                    if (!prev.count(make_pair(v, rv))) {
                        prev[make_pair(v, rv)] = make_pair(u, ru);
                        q.push(make_pair(v, rv));
                    }
                }
            }
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    int type;
    for (int i = 0; i < n; ++i) {
        cin >> type;
        switch(type) {
            case 0: src = i; break;
            case 2: dst = i; break;
            default: break;
        }
        for (int r = 0; r < 6; ++r) {
            cin >> neighbor[i][r];
            --neighbor[i][r];
        }
        for (int r = 0; r < 6; ++r) 
            cin >> connect[i][r];
    }

    preprocess();
    solve();

    cout << path.size() << '\n';
    for (const auto &stat: path) {
        int idx = stat.first + 1, rot = stat.second;
        cout << idx << ' ' << 'R' << ' ' << rot << '\n';
    }
}