#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 205, MAXK = 50;

int P, K, s, dp[MAXN][MAXN], f[MAXN][MAXK];
string str = "";
set<string> dict;

void preprocess() {
    int n = str.size();
    for (int i = 0; i < n; ++i) {
        if (dict.count(str.substr(i, 1))) 
            dp[i][i] = 1;
    }
    for (int len = 2; len <= n; ++len) {
        for (int i = 0; i + len - 1 < n; ++i) {
            int j = i + len - 1;
            dp[i][j] = dp[i+1][j];
            for (int l = i; l <= j; ++l) {
                if (dict.count(str.substr(i, l - i + 1))) {
                    ++dp[i][j];
                    break;
                }
            }
        }
    }
}

int solve() {
    int N = str.size();
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= K; ++j) {
            for (int l = j - 1; l < i; ++l) {
                f[i][j] = max(f[i][j], f[l][j-1] + dp[l][i-1]);
            }
        }
    }
    return f[N][K];
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> P >> K;
    string tmp;
    for (int i = 0; i < P; ++i) {
        cin >> tmp;
        str += tmp;
    }
    cin >> s;
    for (int i = 0; i < s; ++i) {
        cin >> tmp;
        dict.insert(tmp);
    }
    memset(f, 0, sizeof(f));
    memset(dp, 0, sizeof(dp));
    preprocess();
    int ans = solve();
    cout << ans << '\n';
}