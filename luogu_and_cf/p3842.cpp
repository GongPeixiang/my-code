#include <bits/stdc++.h>
using namespace std;

constexpr int N = 20005;

int n, dp[N][2], l[N], r[N]; // left 和 right 与标准库 (std::left, std::right) 冲突

// 0 - based
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> l[i] >> r[i];
        l[i]--;
        r[i]--;
    }
    dp[0][0] = r[0] + (r[0] - l[0]);
    dp[0][1] = r[0];
    for (int i = 1; i < n; i++) {
        dp[i][0] = r[i] - l[i] + 1 + min(abs(l[i-1] - r[i]) + dp[i-1][0], abs(r[i-1] - r[i]) + dp[i-1][1]);
        dp[i][1] = r[i] - l[i] + 1 + min(abs(l[i-1] - l[i]) + dp[i-1][0],abs(r[i-1] - l[i]) + dp[i-1][1]);
    }
    int ans = min(n - 1 - l[n-1] + dp[n-1][0], n - 1 - r[n-1] + dp[n-1][1]);
    cout << ans << '\n';
    return 0;
}