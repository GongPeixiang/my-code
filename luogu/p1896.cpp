#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 9, K = 90;

int n, k;
ll dp[N+1][K][1<<N];
vector<int> s; // contains 0

ll solve() {
    dp[0][0][0] = 1; // 1-based
    for (int r = 0; r < n; r++) {
        for (int stat: s) {
            for (int nstat: s) {
                if ((nstat|(nstat>>1)|(nstat<<1)) & stat) continue;
                int cnt = __builtin_popcount(nstat);
                for (int i = 0; i <= k - cnt; i++) 
                    dp[r+1][i+cnt][nstat] += dp[r][i][stat];
            }
        }
    }
    ll ans = 0;
    for (int stat: s) ans += dp[n][k][stat];
    return ans;  
}

int main() {
    scanf("%d%d", &n, &k);
    for (int stat = 0; stat < (1<<n); stat++) 
        if ((((stat<<1)|(stat>>1))&stat) == 0) s.push_back(stat);
    ll ans = solve();
    printf("%lld\n", ans);
    return 0;
}