#include <bits/stdc++.h>
using namespace std;

int l1, l2;
string seq1, seq2;
vector<int> a, b;

array<array<int, 5>, 5> table = {{  
    {5, -1, -2, -1, -3},
    {-1, 5, -3, -2, -4},
    {-2, -3, 5, -2, -2},
    {-1, -2, -2, 5, -1},
    {-3, -4, -2, -1, (int)1e8}
}};

void preprocess() {
    a.resize(l1);
    b.resize(l2);
    for (int i = 0; i < l1; ++i) {
        switch (seq1[i]) {
            case 'A': a[i] = 0; break;
            case 'C': a[i] = 1; break;
            case 'G': a[i] = 2; break;
            case 'T': a[i] = 3; break;
            default: a[i] = 4; break;
        }
    }
    for (int i = 0; i < l2; ++i) {
        switch (seq2[i]) {
            case 'A': b[i] = 0; break;
            case 'C': b[i] = 1; break;
            case 'G': b[i] = 2; break;
            case 'T': b[i] = 3; break;
            default: b[i] = 4; break;
        }
    }
}

int solve() {
    vector<vector<int>> dp(l1 + 1, vector<int>(l2 + 1, 0));
    for (int i = 1; i <= l1; ++i) 
        dp[i][0] = dp[i - 1][0] + table[a[i - 1]][4];
    for (int j = 1; j <= l2; ++j) 
        dp[0][j] = dp[0][j - 1] + table[4][b[j - 1]];
    for (int i = 1; i <= l1; ++i) {
        for (int j = 1; j <= l2; ++j) {
            int ai = a[i - 1], bj = b[j - 1];
            dp[i][j] = max(dp[i - 1][j - 1] + table[ai][bj], 
                max(dp[i - 1][j] + table[ai][4], dp[i][j - 1] + table[4][bj]));
        }
    }
    return dp[l1][l2];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> l1 >> seq1 >> l2 >> seq2;
    preprocess();
    int ans = solve();
    cout << ans << '\n';
}