#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 105;
constexpr int MAXM = 15;

int n, m, a[MAXN], sum[MAXN];
int f[MAXN][MAXN][MAXM], g[MAXN][MAXN][MAXM];
int min_val = 0x3f3f3f3f, max_val = 0xcfcfcfcf;

// 数据包含负数, 不过加一次10就行
inline int mod(int x) { return (x % 10 + 10) % 10; }

void solve() {
    memset(f, 0xcf, sizeof(f));
    memset(g, 0x3f, sizeof(g));
    for (int i = 0; i < 2 * n; ++i) {
        for (int j = i; j < 2 * n; ++j) {
            g[i][j][1] = f[i][j][1] = mod(sum[j] - (i > 0 ? sum[i-1] : 0));
        }
    }
    for (int len = 2; len <= n; ++len) {
        for (int i = 0; i + len - 1 < 2 * n; ++i) {
            int j = i + len - 1;
            for (int c = 1; c <= len && c <= m; ++c) {
                for (int k = i; k < j; ++k) {
                    int ll = k - i + 1;
                    for (int cl = 1; cl < c && cl <= ll; ++cl) {
                        int cr = c - cl;
                        if (cr > j - k) continue;  // 右边不够分
                        f[i][j][c] = max(f[i][j][c], f[i][k][cl] * f[k+1][j][cr]);
                        g[i][j][c] = min(g[i][j][c], g[i][k][cl] * g[k+1][j][cr]);
                    }
                }
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        min_val = min(g[i][i+n-1][m], min_val);
        max_val = max(f[i][i+n-1][m], max_val);
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        a[i+n] = a[i];
    }
    sum[0] = a[0];
    for (int i = 1; i < 2 * n; ++i) 
        sum[i] = sum[i-1] + a[i];
    solve();
    cout << min_val << max_val << '\n';
    return 0;
}