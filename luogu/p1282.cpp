// 76pts
#include <bits/stdc++.h>
using namespace std;

constexpr int INF = 10000;
int n, sum1 = 0, sum2 = 0;
vector<int> dif;

// 无后效性
int solve() {
    vector<vector<int>> dp(n + 1);
    for (int i = 0; i <= n; ++i) {
        dp[i].resize(i + 1, INF);
        dp[i][0] = sum2 - sum1;
    }        
    for (int i = 1; i <= n; ++i) {
        int chg = dif[i - 1] * 2;
        dp[i][i] = dp[i - 1][i - 1] + chg;
        for (int j = 1; j < i; ++j) {
            if (abs(dp[i - 1][j]) < abs(dp[i][j])) 
                dp[i][j] = dp[i - 1][j];
            if (abs(dp[i - 1][j - 1] - chg) < abs(dp[i][j])) 
                dp[i][j] = dp[i - 1][j - 1] - chg;
        }
    }
    int cnt = 0;
    for (int i = 1; i <= n; ++i) {
        if (abs(dp[n][i]) < abs(dp[n][cnt])) 
            cnt = i;
    }
    return cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    vector<array<int, 2>> cards(n);
    dif.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> cards[i][0] >> cards[i][1];
        sum1 += cards[i][0];
        sum2 += cards[i][1];
        dif[i] = cards[i][1] - cards[i][0];
    }
    int ans = solve();
    cout << ans << '\n';
}