#include <bits/stdc++.h>
using namespace std;

constexpr int N = 105;

int n, t[N], dp[N];

int solve() {
    int ans = 0x3f3f3f3f;
    for (int i = 0; i < n; ++i) {
        fill(dp, dp + i + 1, 1);
        int remain = 0;
        for (int j = 0; j <= i; ++j) {
            for (int k = 0; k < j; ++k) {
                if (t[k] < t[j]) dp[j] = max(dp[k] + 1, dp[j]);
            }
        }
        remain += dp[i];
        fill(dp + i, dp + n, 1);
        for (int j = n - 1; j >= i; --j) {
            for (int k = n - 1; k > j; --k) {
                if (t[k] < t[j]) dp[j] = max(dp[k] + 1, dp[j]);
            }
        }
        remain += dp[i];
        ans = min(ans, n - remain + 1);
    }
    return ans;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) scanf("%d", t + i);
    int ans = solve();
    printf("%d\n", ans);
    return 0;
}