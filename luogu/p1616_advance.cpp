#include <bits/stdc++.h>
using namespace std;

struct Item {
    int w;
    int v;
};

int n, w;
vector<Item> items;
vector<long long> dp;

int main() {
    cin >> w >> n;
    items.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> items[i].w >> items[i].v;
    }
    dp.resize(w + 1, 0);
    for (int i = 1; i <= n; i++) {
        for (int j = items[i].w; j <= w; j++) {
            dp[j] = max(dp[j], dp[j-items[i].w] + items[i].v);
        }
    }
    long long ans = dp[w];
    cout << ans << '\n';
}