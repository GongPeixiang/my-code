#include <bits/stdc++.h>
using std::vector;
using std::array;

int n;
double sum_all = 0, ave = 0, min_msd = 1e7;
vector<int> path;
array<array<int, 9>, 9> dp = {0};

void preprocess(const array<array<int, 8>, 8>& board) {
    for (int i = 1; i <= 8; ++i) {
        for (int j = 1; j <= 8; ++j) {
            dp[i][j] = dp[i - 1][j] + dp[i][j - 1] - dp[i - 1][j - 1] 
                    + board[i - 1][j - 1];
        }
    }
}

inline int get_sum(int l, int r, int t, int b) {
    int r1 = l + 1, r2 = r + 1, c1 = t + 1, c2 = b + 1;
    return dp[r2][c2] - dp[r1 - 1][c2] - dp[r2][c1 - 1] + dp[r1 - 1][c1 - 1];
}

inline double get_msd() {
    double res = 0;
    for (int i = 0; i < n; ++i) 
        res += (path[i] - ave) * (path[i] - ave);
    return sqrt(res / n);
}

void dfs(int dep, int l, int r, int t, int b) {
    if (dep == n - 1) {
        path.push_back(get_sum(l, r, t, b));
        double cur = get_msd();
        min_msd = std::min(min_msd, cur);
        path.pop_back();
        return;
    }
    for (int i = l; i < r; ++i) {
        path.push_back(get_sum(l, i, t, b));
        dfs(dep + 1, i + 1, r, t, b);
        path.pop_back();
        
        path.push_back(get_sum(i + 1, r, t, b));
        dfs(dep + 1, l, i, t, b);
        path.pop_back();
    }
    for (int j = t; j < b; ++j) {
        path.push_back(get_sum(l, r, t, j));
        dfs(dep + 1, l, r, j + 1, b);
        path.pop_back();

        path.push_back(get_sum(l, r, j + 1, b));
        dfs(dep + 1, l, r, t, j);
        path.pop_back();
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    array<array<int, 8>, 8> board;
    std::cin >> n;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            std::cin >> board[i][j];
            sum_all += board[i][j];
        }
    }
    ave = sum_all / n;
    preprocess(board);
    dfs(0, 0, 7, 0, 7);
    std::cout << std::fixed << std::setprecision(3) << min_msd << '\n';
}