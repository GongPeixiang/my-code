#include <bits/stdc++.h>
using namespace std;

int n;
vector<vector<int>> board;
vector<int> row_std, col_std;
vector<int> row_cnt;
bool found = false;

bool final_judge() {
    for (int i = 0; i < n; i++) {
        if (row_cnt[i] != row_std[i]) return false;
    }
    return true;
}

// 剪枝
bool cut() {
    for (int i = 0; i < n; i++) {
        if (row_cnt[i] > row_std[i]) return true;
    }
    return false;
}

void color(int depth, const int &start, const int &length) {
    for (int i = start; i < start + length; i++) {
        board[i][depth] = 1;
        row_cnt[i]++;
    }
}

void decolor(int depth, const int &start, const int &length) {
    for (int i = start; i < start + length; i++) {
        board[i][depth] = 0;
        row_cnt[i]--;
    }
}

void dfs(int depth) {
    if (found) return;
    if (cut()) return;
    if  (depth == n) {
        if (final_judge()) {
            found = true;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) cout << board[i][j] << " ";
                cout << '\n';
            }
        }
        return;
    }

    int end = n - col_std[depth];
    for (int i = 0; i <= end; i++) {
        color(depth, i, col_std[depth]);
        dfs(depth+1);
        decolor(depth, i, col_std[depth]);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    board.resize(n, vector<int>(n,0));
    row_cnt.resize(n,0);
    col_std.resize(n);
    row_std.resize(n);
    for (int i = 0; i < n; i++) 
        cin >> row_std[i];
    for (int i = 0; i < n; i++) 
        cin >> col_std[i];
        
    dfs(0);
    return 0;
}