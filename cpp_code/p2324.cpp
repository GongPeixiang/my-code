#include <bits/stdc++.h>
using namespace std;

constexpr int dx[8] = {-2, -2, -1, -1, 1, 1, 2, 2}, dy[8] = {-1, 1, 2, -2, 2, -2, -1, 1};
constexpr char tgt[5][5] = {
    {'1','1','1','1','1'},
    {'0','1','1','1','1'},
    {'0','0','*','1','1'},
    {'0','0','0','0','1'},
    {'0','0','0','0','0'}
};

char board[5][5];

int hrstic() {
    int cnt = 0;
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (board[i][j] != tgt[i][j] && board[i][j] != '*')
                ++cnt;
        }
    }
    return cnt;
}

void find_space(int &sr, int &sc) {
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (board[i][j] == '*') {
                sr = i;
                sc = j;
                return;
            }
        }
    }
}

bool dfs(int dep, int prev_mov, const int max_dep, int &min_exc) {
    if (dep == max_dep) 
        return memcmp(board, tgt, sizeof(tgt)) == 0;
    int h = hrstic();
    if (dep + h > max_dep) {
        min_exc = min(min_exc, dep + h);
        return false;
    }
    int sr, sc;
    find_space(sr, sc);
    for (int i = 0; i < 8; ++i) {
        if (i == 7 - prev_mov) 
            continue;
        int nr = sr + dx[i], nc = sc + dy[i];
        if (nr < 0 || nr >= 5 || nc < 0 || nc >= 5) 
            continue;
        swap(board[sr][sc], board[nr][nc]);
        if (dfs(dep + 1, i, max_dep, min_exc)) 
            return true;
        swap(board[sr][sc], board[nr][nc]);
    }
    return false;
}

int solve() {
    if (memcmp(board, tgt, sizeof(tgt)) == 0)
        return 0;
    for (int max_dep = 1; max_dep <= 15; ++max_dep) {
        int min_exc = 0x3f3f3f3f;
        if (dfs(0, -1, max_dep, min_exc)) 
            return max_dep;
    }
    return -1;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int T;
    cin >> T;
    while (T--) {
        for (int i = 0; i < 5; ++i) 
            for (int j = 0; j < 5; ++j) 
                cin >> board[i][j];
        int ans = solve();
        cout << ans << '\n';
    }
    return 0;
}