#include <bits/stdc++.h>
using namespace std;

constexpr int INF = 3000;
int k, n, max_val;
vector<int> cur, dp;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> k >> n;
    cur.resize(n);
    for (int i = 0; i < n; ++i) 
        cin >> cur[i];
    sort(cur.begin(), cur.end());
    int max_possible = cur[n - 1] * k;
    dp.resize(max_possible + 1, INF);
    dp[0] = 0;
    for (int i = 1; i <= n; ++i) {
        int cur_i = cur[i - 1];
        for (int j = cur_i; j <= max_possible; ++j) {
            dp[j] = min(dp[j], dp[j - cur_i] + 1);
        }
    }
    max_val = max_possible;
    for (int val = 1; val <= max_possible; ++val) {
        if (dp[val] > k) {
            max_val = val - 1;
            break;
        }
    }
    cout << max_val << '\n';
}