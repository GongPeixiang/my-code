#include <bits/stdc++.h>
using namespace std;

int n;
string line;
vector<vector<int>> dp;

int solve() {
    dp.resize(n, vector<int>(n, 1e6));
    for (int i = 0; i < n; ++i)
        dp[i][i] = 0;
    for (int len = 2; len <= n; ++len) {
        for (int i = 0; i + len - 1 < n; ++i) {
            int j = i + len - 1;
            if (line[i] == line[j]) 
                dp[i][j] =  i + 1 <= j - 1 ? dp[i + 1][j - 1] : 0;
            else 
                dp[i][j] = min(dp[i + 1][j], dp[i][j - 1]) + 1;
        }
    }
    return dp[0][n - 1];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> line;
    n = line.size();
    int ans = solve();
    cout << ans << '\n';
}