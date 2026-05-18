#include <bits/stdc++.h>
using namespace std;

const array<array<int, 2>, 8> dir = {{ {-2, -1}, {-2, 1}, {-1, 2}, {-1, -2}, {1, 2}, {1,  -2}, {2, -1}, {2, 1} }};
const int INF = numeric_limits<int>::max();

const array<array<char, 5>, 5> target = {{
    {'1','1','1','1','1'},
    {'0','1','1','1','1'},
    {'0','0','*','1','1'},
    {'0','0','0','0','1'},
    {'0','0','0','0','0'}
}};
array<array<char, 5>, 5> board;

int heuristic() {
    int cnt = 0;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (board[i][j] != target[i][j] && board[i][j] != '*')
                cnt++;
        }
    }
    return cnt;
}

void find_space(int &sr, int &sc) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (board[i][j] == '*') {
                sr = i;
                sc = j;
                return;
            }
        }
    }
}

bool ida_star(int depth, const int max_depth, int prev_move, int &min_exceed) {
    if (depth == max_depth) {
        if (board == target)
            return true;
        return false;
    }
    int h = heuristic();
    if (depth + h > max_depth) {
        min_exceed = min(min_exceed, depth + h);
        return false;
    }
    int sr, sc;
    find_space(sr, sc);
    for (int i = 0; i < 8; i++) {
        if (i == 7 - prev_move) 
            continue;
        int nr = sr + dir[i][0], nc = sc + dir[i][1];
        if (nr < 0 || nr >= 5 || nc < 0 || nc >= 5) 
            continue;
        swap(board[sr][sc], board[nr][nc]);
        if (ida_star(depth + 1, max_depth, i, min_exceed)) 
            return true;
        swap(board[sr][sc], board[nr][nc]);
    }
    return false;
}

int solve() {
    if (board == target)
        return 0;
    for (int max_depth = 1; max_depth <= 15; max_depth++) {
        int min_exceed = INF;
        if (ida_star(0, max_depth, -1, min_exceed)) 
            return max_depth;
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                cin >> board[i][j];
            }
        }
        int ans = solve();
        cout << ans << '\n';
    }
    return 0;
}