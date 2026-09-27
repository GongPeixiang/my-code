#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 365;
constexpr int dx[9] = {0, 0, 0, 0, 0, 1, 2, -1, -2};
constexpr int dy[9] = {0, 1, 2, -1, -2, 0, 0, 0, 0};

int N, sched[MAXN][4][4], memo[MAXN][4][4][8][8][8][8];

bool check(int d, int cx, int cy) {
    for (int i = cx; i <= cx + 1; ++i) {
        for (int j = cy; j <= cy + 1; ++j) {
            if (sched[d][i][j]) 
                return false;
        }
    }
    return true;
}

bool dfs(int d, int cx, int cy, int tl, int tr, int bl, int br) {
    if (memo[d][cx][cy][tl][tr][bl][br] != -1) 
        return memo[d][cx][cy][tl][tr][bl][br];
    if (!check(d, cx, cy)) 
        return false;
    if (tl >= 7 || tr >= 7 || bl >= 7 || br >= 7) 
        return false;
    if (d == N - 1) 
        return true;
    bool res = false;
    for (int i = 0; i < 9; ++i) {
        int ncx = cx + dx[i], ncy = cy + dy[i];
        if (ncx < 0 || ncx > 2 || ncy < 0 || ncy > 2) 
            continue;
        int ntl = (ncx == 0 && ncy == 0) ? 0 : tl + 1;
        int ntr = (ncx == 0 && ncy == 2) ? 0 : tr + 1;
        int nbl = (ncx == 2 && ncy == 0) ? 0 : bl + 1;
        int nbr = (ncx == 2 && ncy == 2) ? 0 : br + 1;
        res |= dfs(d + 1, ncx, ncy, ntl, ntr, nbl, nbr);
    }
    memo[d][cx][cy][tl][tr][bl][br] = res;
    return res;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    while (1) {
        cin >> N;
        if (!N) 
            break;
        for (int d = 0; d < N; ++d) {
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j) {
                    cin >> sched[d][i][j];
                }
            }
        }
        memset(memo, 0xff, sizeof(memo));
        bool ans = dfs(0, 1, 1, 1, 1, 1, 1);
        cout << ans << '\n';
    }
}