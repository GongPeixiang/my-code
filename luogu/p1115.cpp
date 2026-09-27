#include <bits/stdc++.h>
using namespace std;

constexpr int N = 200005;

int n; // long long sum[N];
long long a[N], dp[N], ans = LLONG_MIN;

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%lld", a + i);
        if (!i) dp[i] = a[i];
        else dp[i] = max(dp[i-1] + a[i], a[i]);
        ans = max(ans, dp[i]);
    }
    printf("%lld\n", ans);
    return 0;
}