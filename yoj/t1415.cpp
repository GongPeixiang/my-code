#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int M = 1000005;
const ll MOD = 998244353;

// ccf, cspark
int n, m, goa[4][26], gob[7][26];
bool fix[M];
ll dp[4][7][2][2][2], ndp[4][7][2][2][2]; // 0,1,2,3

void init() {
    goa[0]['c'-'a'] = 1;
    goa[1]['c'-'a'] = 2;
    goa[2]['f'-'a'] = 3; goa[2]['c'-'a'] = 2;
    goa[3]['c'-'a'] = 1;

    gob[0]['c'-'a'] = 1;
    gob[1]['s'-'a'] = 2; gob[1]['c'-'a'] = 1;
    gob[2]['p'-'a'] = 3;
    gob[3]['a'-'a'] = 4;
    gob[4]['r'-'a'] = 5;
    gob[5]['k'-'a'] = 6;
    gob[6]['c'-'a'] = 1;
}

int main() {
    init();
    scanf("%d%d", &n, &m);
    int a;
    for (int i = 0; i < m; i++) { 
        scanf("%d", &a);
        fix[--a] = true;
    }
    memset(dp, 0, sizeof(dp));
    // memset(ndp, 0, sizeof(ndp));
    dp[0][0][0][0][0] = 1;
    for (int pos = 0; pos < n; pos++) {
        memset(ndp, 0, sizeof(ndp));
        if (fix[pos]) {
            for (int i = 0; i < 4; i++) 
                for (int j = 0; j < 7; j++) 
                    for (int fi = 0; fi < 2; fi++) 
                        for (int fj = 0; fj < 2; fj++) 
                            for (int o = 0; o < 2; o++) {
                                int ni = 0, nj = 0;
                                ndp[ni][ni][fi][fj][o] = (ndp[ni][ni][fi][fj][o] + dp[i][j][fi][fj][o]) % MOD;
                            }
        } else {
            for (int i = 0; i < 4; i++) 
                for (int j = 0; j < 7; j++) 
                    for (int fi = 0; fi < 2; fi++) 
                        for (int fj = 0; fj < 2; fj++) 
                            for (int o = 0; o < 2; o++) 
                                for (int c = 0; c < 26; c++) {
                                    int ni = goa[i][c], nj = gob[j][c];
                                    bool nfi = fi || (ni == 3), nfj = fj || (nj == 6);
                                    bool no = o;
                                    if (fi && !fj && nfj) no = 1;
                                    ndp[ni][nj][nfi][nfj][no] = (ndp[ni][nj][nfi][nfj][no] + dp[i][j][fi][fj][o]) % MOD;
                                }
        }
        memcpy(dp, ndp, sizeof(dp));
    }
    ll ans = 0;
    for (int i = 0; i < 4; i++) 
        for (int j = 0; j < 7; j++) 
            ans = (ans + dp[i][j][1][1][1]) % MOD;
    printf("%lld\n", ans);
    return 0;
}