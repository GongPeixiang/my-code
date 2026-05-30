#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 350, MAXC = 45;

int N, val[MAXN], cnt[5];
int dp[MAXC][MAXC][MAXC][MAXC];

int solve() {
    dp[0][0][0][0] = val[0];
    for (int a = 0; a <= cnt[1]; ++a) {
        for (int b = 0; b <= cnt[2]; ++b) {
            for (int c = 0; c <= cnt[3]; ++c) {
                for (int d = 0; d <= cnt[4]; ++d) {
                    int r = a + b * 2 + c * 3 + d * 4;
                    if (a >= 1) 
                        dp[a][b][c][d] = max(dp[a][b][c][d], dp[a-1][b][c][d] + val[r]);
                    if (b >= 1) 
                        dp[a][b][c][d] = max(dp[a][b][c][d], dp[a][b-1][c][d] + val[r]);
                    if (c >= 1) 
                        dp[a][b][c][d] = max(dp[a][b][c][d], dp[a][b][c-1][d] + val[r]);
                    if (d >= 1) 
                        dp[a][b][c][d] = max(dp[a][b][c][d], dp[a][b][c][d-1] + val[r]);
                }
            }
        }
    }
    return dp[cnt[1]][cnt[2]][cnt[3]][cnt[4]];
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int M, tmp;
    cin >> N >> M;
    for (int i = 0; i < N; ++i) 
        cin >> val[i];
    for (int i = 0; i < M; ++i) {
        cin >> tmp;
        ++cnt[tmp];
    }
    int ans = solve();
    cout << ans << '\n';
    return 0;
}
