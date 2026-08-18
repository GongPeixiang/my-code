#include <bits/stdc++.h>
using namespace std;

constexpr int MAXW = 1005;

int maxw, w[7] = {-1, 1, 2, 3, 5, 10, 20}, cnt[7];
int dp[MAXW]; // dp[i]代表能凑出重量i的方案数

int main() {
    for (int i = 1; i <= 6; i++) {
        cin >> cnt[i];
        maxw += cnt[i] * w[i];
    }
    dp[0] = 1;
    for (int i = 1; i <= 6; i++) {
        for (int j = maxw; j >= w[i]; j--) {
            for (int k = 1; k * w[i] <= j && k <= cnt[i]; k++) {
                dp[j] += dp[j - k*w[i]];
            }
        }
    }
    int ans = 0;
    for (int i = 1; i <= maxw; i++) 
        if (dp[i]) ans++;
    cout << "Total=" << ans << '\n';
}