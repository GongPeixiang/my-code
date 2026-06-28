#include <bits/stdc++.h>
using namespace std;

struct Item {
    int w;
    int v;
};

int n, w;
vector<Item> items;
vector<vector<long long>> dp;

int main()
{
    cin >> w >> n;
    items.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> items[i].w >> items[i].v;
    }
    dp.resize(n + 1, vector<long long>(w + 1, 0));
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= w; j++) {
            if (j < items[i].w) 
                dp[i][j] = dp[i-1][j];
            else 
                dp[i][j] = max(dp[i-1][j], dp[i][j-items[i].w] + items[i].v);
        }
    }
    long long ans = dp[n][w];
    cout << ans << '\n';
    return 0;
}