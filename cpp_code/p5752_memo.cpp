#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 15;

int n, board[8][8], dp[9][9];
double sum = 0, ave = 0, memo[MAXN][8][8][8][8];
bool vis[MAXN][8][8][8][8];

void preprocess() {
    memset(dp, 0, sizeof(dp));
    for (int i = 1; i <= 8; ++i) {
        for (int j = 1; j <= 8; ++j) {
            dp[i][j] = dp[i-1][j] + dp[i][j-1] - dp[i-1][j-1] + board[i-1][j-1];
        }
    }
}

inline int get_sum(int l, int r, int t, int b) {
    int r1 = l + 1, r2 = r + 1, c1 = t + 1, c2 = b + 1;
    return dp[r2][c2] - dp[r1-1][c2] - dp[r2][c1-1] + dp[r1-1][c1-1];
}

double dfs(int k, int l, int r, int t, int b) {
    if (vis[k][l][r][t][b]) 
        return memo[k][l][r][t][b];
    if (k == 0) {
        double s = get_sum(l, r, t, b);
        return memo[k][l][r][t][b] = (s - ave) * (s - ave);
    }
    double res = 1e9;
    for (int i = l; i < r; i++) {
        res = min(res, (get_sum(l, i, t, b) - ave) * (get_sum(l, i, t, b) - ave) + 
            dfs(k - 1, i + 1, r, t, b));
        res = min(res, (get_sum(i + 1, r, t, b) - ave) * (get_sum(i + 1, r, t, b) - ave) 
            + dfs(k - 1, l, i, t, b));
    }
    for (int j = t; j < b; j++) {
        res = min(res, (get_sum(l, r, t, j) - ave) * (get_sum(l, r, t, j) - ave) 
                + dfs(k - 1, l, r, j + 1, b));
        res = min(res, (get_sum(l, r, j + 1, b) - ave) * (get_sum(l, r, j + 1, b) - ave) 
                + dfs(k - 1, l, r, t, j));
    }
    vis[k][l][r][t][b] = true;
    return memo[k][l][r][t][b] = res;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            cin >> board[i][j];
            sum += board[i][j];
        }
    }
    ave = sum / n;
    preprocess();
    memset(vis, 0, sizeof(vis));
    double min_sqr =  dfs(n - 1, 0, 7, 0, 7);
    auto min_msd = sqrt(min_sqr / n);
    cout << fixed << setprecision(3) << min_msd << '\n';
}