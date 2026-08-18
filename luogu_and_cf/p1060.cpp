 #include <bits/stdc++.h>
using namespace std;

constexpr int M = 30, N = 30005;

struct Item {
    int p, sig; // p代表价格， sig代表重要度
    int val;    // val = p * sig;
} item[M];
int n, m, dp[M][N];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> item[i].p >> item[i].sig;
        item[i].val = item[i].p * item[i].sig;
    }
    for (int i = 1; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (j < item[i].p) dp[i][j] = dp[i-1][j];
            else dp[i][j] = max(dp[i-1][j], dp[i-1][j-item[i].p] + item[i].val);
        }
    }
    cout << dp[m][n] << '\n';
    return 0;
}