#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 2006;

struct Fill {
    int r, c, d;
    int blk_left;
};

int m, n, len, blk = 0;
char board[MAXN][MAXN], word[MAXN];
Fill ans = Fill{-1, -1, -1, -1};

static inline bool is_bnd(int r, int c) {
    return r == m - 1 || !r || c == n - 1 || !c;
}

int cnt_blk(int r, int c, int d) {
    int cnt = (board[r][c] == '0');
    int tr = r, tc = c;
    for (int i = 1; i < len; ++i) {
        switch (d) {
            case 0: tc = c + i; break;
            case 1: tc = c - i; break;
            case 2: tr = r + i; break;
            case 3: tr = r - i; break;
        }
        if (board[tr][tc] == '0') ++cnt;
    }
    return blk - cnt;
}

bool dfs(int dep, int r, int c, int d) {
    if (dep == len - 1) {
        char bc = board[r][c];
        if (!(bc == '0' || bc == word[dep] || bc == '*')) 
            return false;
        if (!is_bnd(r, c)) {
            switch (d) {
                case 0: return board[r][c+1] == '1';
                case 1: return board[r][c-1] == '1';
                case 2: return board[r+1][c] == '1';
                case 3: return board[r-1][c] == '1';
            }
        }
        return true;
    }
    if (r < 0 || r >= m || c < 0 || c >= n) 
        return false;
    char bc = board[r][c];
    if (bc == '0' || bc == word[dep] || bc == '*') {
        switch (d) {
            case 0: return dfs(dep + 1, r, c + 1, d);
            case 1: return dfs(dep + 1, r, c - 1, d);
            case 2: return dfs(dep + 1, r + 1, c, d);
            case 3: return dfs(dep + 1, r - 1, c, d);
        }
    } 
    return false;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> m >> n;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> board[i][j];
            if (board[i][j] == '0') 
                ++blk;
        }
    }
    cin >> word;
    len = strlen(word);
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            char bc = board[i][j];
            if (bc == '0' || bc == word[0] || bc == '*') {
                bool flg[4] = {false};
                for (int d = 0; d < 4; ++d) { 
                     if (!is_bnd(i, j)) {
                        switch (d) {
                            case 0: if (board[i][j-1] != '1') continue; break;
                            case 1: if (board[i][j+1] != '1') continue; break;
                            case 2: if (board[i-1][j] != '1') continue; break;
                            case 3: if (board[i+1][j] != '1') continue; break;
                        }
                    }
                    if (dfs(0, i, j, d)) 
                        flg[d] = true;
                }
                if (flg[0] && flg[1]) flg[1] = false;
                if (flg[2] && flg[3]) flg[3] = false;
                for (int d = 0; d < 4; ++d) {
                    if (flg[d]) {
                        int bl = cnt_blk(i, j, d);
                        if (bl > ans.blk_left) 
                            ans = {i, j, d, bl};
                    }
                }
            }
        }
    }
    if (ans.blk_left == -1) 
        cout << "No" << '\n';
    else {
        int er = ans.r, ec = ans.c;
        for (int i = 1; i < len; ++i) {
            switch (ans.d) {
                case 0: ++ec; break;
                case 1: --ec; break;
                case 2: ++er; break;
                case 3: --er; break;
            }
        }
        cout << ans.r << ' ' << ans.c << '\n' << er << ' ' << ec << '\n';
    }
    return 0;
}