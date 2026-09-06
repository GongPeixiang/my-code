#include <bits/stdc++.h>
using namespace std;

const int K = 20;

int n, k, val[K], ans[K], maxsum = 0, dp[10000];

int calc(int dep) {
    memset(dp, 0x3f, sizeof(dp));
    dp[0] = 0;
    for (int i = 0; i <= dep; i++) {
        for (int j = val[i]; j <= n * val[dep]; j++) {
            dp[j] = min(dp[j], dp[j-val[i]] + 1);
        }
    }
    for (int i = 1; i <= n * val[dep]; i++) 
        if (dp[i] > n && dp[i-1] <= n) return i - 1;
    return n * val[dep];
}

void solve(int dep) {
    int tmp = calc(dep - 1); // tmp bound
    if (dep == k) {
        if (tmp > maxsum)  {
            maxsum = tmp;
            memcpy(ans, val, sizeof(ans));
        }
        return;
    }
    for (int v = val[dep-1] + 1; v <= tmp + 1; v++) {
        val[dep] = v;
        solve(dep + 1);
    }
}

int main() {
    scanf("%d%d", &n, &k);
    val[0] = ans[0] = 1;
    solve(1);
    for (int i = 0; i < k; i++) printf("%d%c", ans[i], " \n"[i==k-1]);
    printf("MAX=%d\n", maxsum);
    return 0;
}