#include <bits/stdc++.h>
using namespace std;

constexpr int MAXR = 1005;
constexpr int dir[4][2] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

int R, C; //易错(递归中的r,c和行数R,列数C)
char board[MAXR][MAXR];
bool vis[MAXR][MAXR];

void dfs(int r, int c, int& upl, int& lol, int& lel, int& ril) {
    vis[r][c] = true;
    for (int i = 0; i < 4; ++i) {
        int nr = r + dir[i][0], nc = c + dir[i][1];
        if (nr < 0 || nr >= R || nc < 0 || nc >= C ) continue;
        if (vis[nr][nc] || board[nr][nc] != '#') continue;
        if (nr < lol) lol = nr;
        if (nr > upl) upl = nr;
        if (nc < lel) lel = nc;
        if (nc > ril) ril = nc;
        dfs(nr, nc, upl, lol, lel, ril);
    }
}

bool check(int up_l, int lo_l, int le_l, int ri_l) {
    for (int i = lo_l; i <= up_l; ++i) 
        for (int j = le_l; j <= ri_l; ++j) 
            if (!vis[i][j]) return false;
    return true;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> R >> C;
    for (int i = 0; i < R; ++i) 
        for (int j = 0; j < C; ++j) 
            cin >> board[i][j];
    int ships = 0;
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            if (board[i][j] == '#' && !vis[i][j]) {
                int upl = i, lol = i, lel = j, ril = j;
                dfs(i, j, upl, lol, lel, ril);
                if (!check(upl, lol, lel, ril)) {
                    cout << "Bad placement.\n";
                    return 0;
                }
                ++ships;
            }
        }
    }
    cout << "There are " << ships << " ships." << '\n';
}