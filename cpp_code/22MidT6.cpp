#include <bits/stdc++.h>
using namespace std;

int n, m, max_val = 0;
vector<vector<int>> board;

void new_pos(int &nr, int &nc, int r, int c, int new_dir) {
    switch(new_dir) {
        case 0: nr = r - 1; nc = c; return;
        case 1: nr = r; nc = c + 1; return;
        case 2: nr = r + 1; nc = c; return;
        case 3: nr = r; nc = c - 1; return;
    }
}

int single(int r, int c) {
    board[r][c] = (board[r][c] + 1) % 4;
    int nr, nc, sum = 90;
    new_pos(nr, nc, r, c, board[r][c]);
    if (nr >= 0 && nr < n && nc >= 0 && nc < n) {
        sum += single(nr, nc);
    }
    return sum;
}

void search(int cnt, int total_sum) {
    if (cnt == m) {
        max_val = max(total_sum, max_val);
        return;
    }
    for (int idx = 0; idx < n * n; idx++) {
        vector<vector<int>> board_dup = board;
        int r = idx / n, c = idx % n;
        search(cnt + 1, total_sum + single(r, c));
        board = board_dup;
    }
}

int main() {
    cin >> n >> m;
    board.resize(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> board[i][j];
        }
    }
    search(0, 0);
    cout << max_val << '\n';
    return 0;
}