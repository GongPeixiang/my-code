#include <bits/stdc++.h>
using namespace std;

struct Item {
    int p, sig; // p代表价格， sig代表重要度
    int val;    // val = p * sig;
};

int n, m;
vector<Item> items;
vector<vector<int>> dp;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    items.resize(m + 1);
    for (int i = 1; i <= m; i++) {
        cin >> items[i].p >> items[i].sig;
        items[i].val = items[i].p * items[i].sig;
    }
    dp.resize(m + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (j < items[i].p) 
                dp[i][j] = dp[i-1][j];
            else 
                dp[i][j] = max(dp[i-1][j], 
                    dp[i-1][j-items[i].p] + items[i].val);
        }
    }
    int ans = dp[m][n];
    cout << ans << '\n';
    return 0;
}