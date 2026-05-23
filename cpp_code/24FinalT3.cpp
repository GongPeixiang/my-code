#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 15;

int n, row_std[MAXN], col_std[MAXN], row_cnt[MAXN];
bool found = false, board[MAXN][MAXN];

inline bool final_judge() {
    return memcmp(row_cnt, row_std, sizeof(row_std)) == 0;
}

// prunning
bool to_cut() {
    for (int i = 0; i < n; ++i) {
        if (row_cnt[i] > row_std[i]) 
            return true;
    }
    return false;
}

void color(int dep, int s, int len) {
    for (int i = s; i < s + len; ++i) {
        board[i][dep] = true;
        ++row_cnt[i];
    }
}

void decolor(int dep, int s, int len) {
    for (int i = s; i < s + len; ++i) {
        board[i][dep] = false;
        --row_cnt[i];
    }
}

void dfs(int dep) {
    if (found) return;
    if (to_cut()) return;
    if  (dep == n) {
        if (final_judge()) {
            found = true;
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) 
                    cout << board[i][j] << ' ';
                cout << '\n';
            }
        }
        return;
    }
    int end = n - col_std[dep];
    for (int i = 0; i <= end; ++i) {
        color(dep, i, col_std[dep]);
        dfs(dep + 1);
        decolor(dep, i, col_std[dep]);
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    memset(board, 0, sizeof(board));
    cin >> n;
    for (int i = 0; i < n; ++i) 
        cin >> row_std[i];
    for (int i = 0; i < n; ++i) 
        cin >> col_std[i];
    dfs(0);
    return 0;
}