#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 2005;

int n, src, dst, neighbor[MAXN][6];
bool connect[MAXN][6], re_connect[MAXN][6][6], vis[MAXN][6];
struct State {
    int u, rot;
    bool operator==(const State &other) const {
        return u == other.u && rot == other.rot;
    }
} pre[MAXN][6];
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

// bfs
void solve() {
    memset(vis, 0, sizeof(vis));
    memset(pre, 0xff, sizeof(pre));
    queue<State> q;  // 格子编号和旋转情况
    for (int r = 0; r < 6; ++r) {
        q.push({src, r});
        vis[src][r] = true;
    }
    while (!q.empty()) {
        auto cur_stat = q.front();
        int u = cur_stat.u, ru = cur_stat.rot;
        q.pop();
        if (u == dst) {
            State trk = {u, ru};
            while (1) {
                if (trk.u == -1) break;
                if (trk.rot != 0)
                    path.push_back(trk);
                trk = pre[trk.u][trk.rot];
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
                    if (!vis[v][rv]) {
                        vis[v][rv] = true;
                        pre[v][rv] = {u, ru};
                        q.push({v, rv});
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
    for (const auto &sta: path) {
        int idx = sta.u + 1, rot = sta.rot;
        cout << idx << ' ' << 'R' << ' ' << rot << '\n';
    }
}