#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1005;

int n, dp[N];
bool ok[N][N];
struct Rec {
    int wid, len;
} rec[N];

int f(int x) {
    if (~dp[x]) return dp[x];
    dp[x] = 1;
    for (int i = 0; i < n; i++) {
        if (ok[i][x]) dp[x] = max(dp[x], f(i) + 1);
    }
    return dp[x];
}

void print_ans(int i) {
    cout << i << ' ';
    for (int j = 0; j < n; j++) {
        if (ok[i][j] && dp[i] == dp[j] + 1) {
            print_ans(j);
            break;
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 0; i < n; i++) cin >> rec[i].len >> rec[i].wid;
        memset(ok, 0, sizeof(ok));
        memset(dp, -1, sizeof(dp));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if ((rec[i].len < rec[j].len && rec[i].wid < rec[j].wid)
                || (rec[i].len < rec[j].wid && rec[i].wid < rec[j].len)) 
                    ok[i][j] = true;
            }
        }
        int ans = 1, pos = -1;
        for (int i = 0; i < n; i++) { 
            if (f(i) > ans) {
                ans = dp[i];
                pos = i;
            }
        }
        cout << ans << '\n';
        print_ans(pos);
    }
    return 0;
}