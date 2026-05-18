#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> a;
vector<vector<int>> dp;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    a.resize(n);
    for (int i = 0; i < n; ++i) 
        cin >> a[i];
    dp.resize(n, vector<int>(n, 0));
    for (int len = 2; len <= n; ++len) {
        for (int i = 0; i + len - 1 < n; ++i) {
            int j = i + len - 1;
            if (a[i] == a[j]) 
                dp[i][j] = dp[i + 1][j - 1];
            else 
                dp[i][j] = min(dp[i + 1][j - 1], 
                    min(dp[i][j - 1], dp[i + 1][j])) + 1;
        }
    }
    cout << dp[0][n - 1] << '\n';
}