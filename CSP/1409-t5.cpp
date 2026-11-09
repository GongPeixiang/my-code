#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int M = 8, MOD = 1000000007;

int n, m;
ll dp[0][1<<M];

ll solve() {
    dp[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        int cur = i & 1, p = (i-1) & 1;
        for (int mask = 0; mask < (1<<m); mask++) {
            if (!dp[p][mask]) continue;
            for (int j = 0; j < m; j++) {
                int flg = mask>>(m-1-i);
                if (!flg) {
                    
                }
            }
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    ll ans = solve();
    printf("%lld\n", ans);
    return 0;
}