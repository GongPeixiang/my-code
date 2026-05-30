#include <bits/stdc++.h>
using namespace std;

constexpr int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};

char board[4][4];
int row[4][2], col[4][2], diag[2][2];

void find_spc(int r[2], int c[2]) 
{
    int cnt = 0;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (board[i][j] == 'O') {
                r[cnt] = i, c[cnt] = j;
                ++cnt;
            }
        }
    }
}

int hrstic() 
{
    int max_cnt = 0;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 2; ++j) {
            max_cnt = max(max_cnt, max(row[i][j], col[i][j]));
        }
    }
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            max_cnt = max(max_cnt, diag[i][j]);
        }
    }
    return 4 - max_cnt;
}

bool dfs(int dep, const int max_dep, int prev) {
    if (dep == max_dep) 
        return hrstic() == 0;
    if (dep + hrstic() > max_dep) 
        return false;
    int r[2], c[2];
    find_spc(r, c);
    for (int k = 0; k < 2; ++k) {
        int sr = r[k], sc = c[k];
        for (int i = 0; i < 4; ++i) {
            int nr = sr + dx[i], nc = sc + dy[i];
            if (nr < 0 || nr > 3 || nc < 0 || nc > 3 || board[nr][nc] == 'O') 
                continue;
            int cur = board[nr][nc] == 'W' ? 0 : 1;
            if (cur == prev) continue;

            swap(board[nr][nc], board[sr][sc]);
            --row[nr][cur], --col[nc][cur];
            ++row[sr][cur], ++col[sc][cur];
            if (nr == nc) --diag[0][cur];
            if (nr == 3 - nc) --diag[1][cur];
            if (sr == sc) ++diag[0][cur];
            if (sr == 3 - sc) ++diag[1][cur];
            
            if (dfs(dep + 1, max_dep, cur)) 
                return true;

            swap(board[nr][nc], board[sr][sc]);
            ++row[nr][cur], ++col[nc][cur];
            --row[sr][cur], --col[sc][cur];
            if (nr == nc) ++diag[0][cur];
            if (nr == 3 - nc) ++diag[1][cur];
            if (sr == sc) --diag[0][cur];
            if (sr == 3 - sc) --diag[1][cur];
        }
    }
    return false;
}

int solve() {
    for (int max_dep = 0; ; ++max_dep) 
        if (dfs(0, max_dep, -1)) 
            return max_dep;
    return -1;
}

int main() {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            cin >> board[i][j];
            if (board[i][j] == 'O') continue;
            int c = (board[i][j] == 'W') ? 0 : 1;
            ++row[i][c], ++col[j][c];
            if (i == j) ++diag[0][c];
            if (i == 3 - j) ++diag[1][c];
        }
    }
    int ans = solve();
    cout << ans << '\n';
    return 0;
}