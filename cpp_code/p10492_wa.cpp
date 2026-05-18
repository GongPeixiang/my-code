#include <bits/stdc++.h>
using namespace std;

int n;
vector<array<array<bool, 4>, 4>> schedules;
array<array<int, 4>, 4> dry_days = {};

const vector<pair<int, int>> moves = {
    {0, 0}, 
    {-1, 0}, {1, 0}, {0, -1}, {0, 1},
    {-2, 0}, {2, 0}, {0, -2}, {0, 2}
};

inline bool is_valid(int r, int c) {
    return r >= 0 && r <= 2 && c >= 0 && c <= 2;
}

bool check_schedule(int r, int c, int dep) {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            int nr = r + i, nc = c + j;
            if (schedules[dep][nr][nc]) 
                return false;
        }
    }
    return true;
}

bool check_dry() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (dry_days[i][j] > 6) 
                return false;
        }
    }
    return true;
}

using ull = unsigned long long;

ull encode_dry_days() {
    ull code = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            code = code * 7 + dry_days[i][j];
        }
    }
    return code;
}

struct StateHash {
    size_t operator()(const tuple<int, int, int, ull>& t) const {
        auto [r, c, dep, state] = t;
        return ((r * 3 + c) * 365 + dep) * 1000000007 + state;
    }
};

// 用 unordered_map 记录状态是否已访问过
unordered_map<tuple<int, int, int, ull>, bool, StateHash> memo;

bool dfs(int r, int c, int dep) {
    if (dep == n) 
        return true;
    ull state = encode_dry_days();
    auto key = make_tuple(r, c, dep, state);
    if (memo.count(key)) 
        return memo[key];
    for (const auto& [dr, dc] : moves) {
        int nr = r + dr, nc = c + dc;
        if (!is_valid(nr, nc) || !check_schedule(nr, nc, dep)) 
            continue;
        auto old_dry_days = dry_days;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                dry_days[i][j]++;
            }
        }
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                dry_days[nr + i][nc + j] = 0;
            }
        }
        if (check_dry() && dfs(nr, nc, dep + 1)) {
            memo[key] = true;
            return true;
        }
        dry_days = old_dry_days;
    }
    memo[key] = false;
    return false;
}

bool solve() {
    memo.clear();
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            dry_days[i][j] = 0;
        }
    }
    int start_r = 1, start_c = 1;
    if (!check_schedule(start_r, start_c, 0)) 
        return false;
    return dfs(start_r, start_c, 0);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> n && n) {
        schedules.resize(n);
        for (int i = 0; i < n; i++) {
            for (int r = 0; r < 4; r++) {
                for (int c = 0; c < 4; c++) {
                    cin >> schedules[i][r][c];
                }
            }
        }
        cout << solve() << '\n';
    }
}