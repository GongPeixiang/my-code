#include <bits/stdc++.h>
using namespace std;

const array<array<int, 2>, 4> dir = {{ {-1, 0}, {0, -1}, {0, 1}, {1, 0} }};
int n, m;
vector<vector<int>> maze;
vector<vector<bool>> vis;

struct Node {
    int r, c;
    int dir_record;
    Node(int r, int c, int d = 0): 
        r(r), c(c), dir_record(d) {}
};

inline bool is_valid(int r, int c) {
    return r >= 0 && r < n && c >= 0 && c < m;
}

vector<pair<int, int>> solve() {
    stack<Node> stk;
    stk.push(Node(0, 0, 0));

    while (!stk.empty()) {
        Node &cur_node = stk.top(); // 引用!
        int r = cur_node.r, c = cur_node.c;
        int &i = cur_node.dir_record;
        vis[r][c] = true;

        if (r == n - 1 && c == m - 1) {
            vector<pair<int, int>> path;
            while (!stk.empty()) {
                path.push_back({stk.top().r, stk.top().c});
                stk.pop();
            }
            reverse(path.begin(), path.end());
            return path;
        }

        if (i < 4) {
            for (; i < 4; i++) {
                int nr = r + dir[i][0], nc = c + dir[i][1];
                if (!is_valid(nr, nc) || !maze[nr][nc] || vis[nr][nc]) 
                    continue;
                stk.push(Node(nr, nc, 0));
                break;
            }
        }
        else {
            vis[r][c] = false;
            stk.pop();
        }
    }

    return {}; // 不存在路径
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    maze.resize(n, vector<int>(m));
    vis.resize(n, vector<bool>(m, false));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> maze[i][j];
        }
    }
    
    vector<pair<int, int>> path = solve();

    for (const auto &[r, c] : path) {
        cout << '(' << r << ',' << c << ')' << '\n';
    }
}