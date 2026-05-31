#include <bits/stdc++.h>
using namespace std;

int lcs_len(const string &a, const string &b) {
    int m = a.size(), n = b.size();
    //dp[i][j] 表示a[0...i-1] 和 b[0...j-1] 的LCS长度
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (a[i-1] == b[j-1]) {
                dp[i][j] = dp[i-1][j-1] + 1;
            }
            else {
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }
    return dp[m][n];
}

int main() {
    string a, b;
    cin >> a >> b;
    int ans = lcs_len(a, b);
    cout << ans << endl;
    return 0;
}