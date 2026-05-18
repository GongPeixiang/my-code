#include <bits/stdc++.h>
using namespace std;

// ===============================
// 旋转 connect 数组（顺时针 r 次）
// connect: 长度 6 的数组
// 顺时针旋转 = 数组右移 r 位
// ===============================
array<int,6> rotate_connect(const array<int,6>& c, int r) {
    r %= 6;
    array<int,6> res;
    for (int i = 0; i < 6; i++) {
        res[(i + r) % 6] = c[i];
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // ======================
    // 1. 输入读取
    // ======================
    int n;
    cin >> n;

    vector<int> type(n);
    vector<array<int,6>> neighbor(n);
    vector<array<int,6>> connect(n);

    for (int i = 0; i < n; i++) {
        cin >> type[i];
        for (int j = 0; j < 6; j++) cin >> neighbor[i][j];
        for (int j = 0; j < 6; j++) cin >> connect[i][j];
    }

    // ======================
    // 2. 找到水源和生命之树
    // ======================
    int s = -1, t = -1;
    for (int i = 0; i < n; i++) {
        if (type[i] == 0) s = i;
        if (type[i] == 2) t = i;
    }
    // 题目保证一定存在

    // ======================
    // 3. 预计算每个格子所有 6 个旋转结果
    // rotated[cell][r] = array<int,6>
    // ======================
    vector<array<array<int,6>,6>> rotated(n);
    for (int i = 0; i < n; i++) {
        for (int r = 0; r < 6; r++) {
            rotated[i][r] = rotate_connect(connect[i], r);
        }
    }

    // ======================
    // 4. BFS 状态 dist[cell][rot]
    //
    // dist 保存：
    //  {parent_cell, parent_rotation}
    //
    // 若 dist[cell][rot] = {-1,-1,-1} 表示 BFS 起点
    // 若标签为 (int, int, int) 表示有效父亲
    // 若为 {-2,-2,-2} 表示未访问
    // ======================
    struct Node {
        int pcell, prot;
    };

    vector<vector<Node>> dist(n, vector<Node>(6, {-2, -2}));

    queue<pair<int,int>> q;

    // 水源所有旋转角度均作为起点
    for (int r = 0; r < 6; r++) {
        dist[s][r] = {-1, -1};
        q.push({s, r});
    }

    // BFS 目标状态
    pair<int,int> found = {-1,-1};

    // ======================
    // 5. BFS 搜索
    // ======================
    while (!q.empty() && found.first == -1) {
        auto [u, ru] = q.front();
        q.pop();

        const auto &uc = rotated[u][ru];

        // 遍历 6 个方向
        for (int d = 0; d < 6; d++) {
            if (uc[d] == 0) continue;   // 无管道

            int v = neighbor[u][d];
            if (v == 0) continue;       // 无邻居
            v--;                        // 输入是 1-based，这里改为 0-based

            int back = (d + 3) % 6; // 要求邻居v在这个方向上必须有管道

            // 尝试邻居的所有 6 种旋转方式
            for (int rv = 0; rv < 6; rv++) {
                const auto &vc = rotated[v][rv];

                if (vc[back] == 1) {  // 可以连通
                    if (dist[v][rv].pcell == -2) {  // 还未访问
                        dist[v][rv] = {u, ru};
                        q.push({v, rv});

                        if (v == t) {
                            found = {v, rv};
                            break;
                        }
                    }
                }
            }
            if (found.first != -1) break;
        }
    }

    // BFS 理论上必然找到
    if (found.first == -1) {
        cout << 0 << "\n";
        return 0;
    }

    // ======================
    // 6.  回溯路径
    // ======================
    unordered_map<int,int> final_rot;  // cell -> rotation
    int cell = found.first;
    int rot  = found.second;

    while (cell != -1) {
        final_rot[cell] = rot;

        Node parent = dist[cell][rot];
        cell = parent.pcell;
        rot  = parent.prot;
    }

    // ======================
    // 7. 转换旋转操作
    //
    // rot <= 3   → R rot
    // rot >  3   → L (6-rot)
    // ======================
    vector<tuple<int,char,int>> ops;

    for (auto &p : final_rot) {
        int c = p.first;   // 0-based
        int r = p.second;

        if (r == 0) continue;

        if (r <= 3) ops.push_back({c+1, 'R', r});
        else        ops.push_back({c+1, 'L', 6 - r});
    }

    // ======================
    // 8. 输出
    // ======================
    cout << ops.size() << "\n";
    for (auto &op : ops) {
        int cid, num;
        char dir;
        tie(cid, dir, num) = op;
        cout << cid << " " << dir << " " << num << "\n";
    }

    return 0;
}
