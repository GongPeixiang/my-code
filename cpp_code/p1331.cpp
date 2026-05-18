#include <bits/stdc++.h>
using namespace std;

const array<array<int, 2>, 4> dir = {{ {-1, 0}, {0, -1}, {1, 0}, {0, 1} }};

vector<vector<char>> board;
vector<vector<bool>> vis;
int R, C; // 又是变量名，非常易错！(递归中的r,c 和 行数R,列数C)

void dfs(int r, int c, int &up_limit, int &low_limit, 
    int &left_limit, int &right_limit) {
    vis[r][c] = true;
    for (int i = 0; i < 4; i++) {
        int nr = r + dir[i][0], nc = c + dir[i][1];
        if (nr < 0 || nr >= R || nc < 0 || nc >= C || vis[nr][nc]
            || board[nr][nc] != '#') 
            continue;

        if (nr < low_limit) low_limit = nr;
        if (nr > up_limit) up_limit = nr;
        if (nc < left_limit) left_limit = nc;
        if (nc > right_limit) right_limit = nc;
        
        dfs(nr, nc, up_limit, low_limit, left_limit, right_limit);
    }
}

bool check(int up_l, int low_l, int left_l, int right_l) {
    for (int i = low_l; i <= up_l; i++) {
        for (int j = left_l; j <= right_l; j++) {
            if (!vis[i][j]) 
                return false;
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> R >> C;
    board.resize(R, vector<char>(C));
    vis.resize(R, vector<bool>(C, false));
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            cin >> board[i][j];
        }
    }

    int ships_cnt = 0;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (board[i][j] == '#' && !vis[i][j]) {
                int up_l = i, low_l = i, left_l = j, right_l = j;
                dfs(i, j, up_l, low_l, left_l, right_l);
                if (!check(up_l, low_l, left_l, right_l)) {
                    cout << "Bad placement." << '\n';
                    return 0;
                }
                ships_cnt++;
            }
        }
    }

    cout << "There are " << ships_cnt << " ships." << '\n';
}