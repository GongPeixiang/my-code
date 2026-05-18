#include <bits/stdc++.h>
using namespace std;

struct Item {
    int w, v;
    Item(int a, int b) : w(a), v(b) {}
};

int n, m;
vector<vector<Item>> items;
vector<int> dp;

int main() {
    cin >> m >> n;
    items.resize(n + 1);
    int a, b, c;
    int K = 1;
    for (int i = 0; i < n; i++) {
        cin >> a >> b >> c;
        K = max(K, c);
        items[c].push_back(Item(a, b));
    }
    dp.resize(m + 1, 0);
    for (int k = 1; k <= K; k++) {
        int cnt = items[k].size();
        for (int i = m; i >= 0; i--) {
            for (int j = 0; j < cnt; j++) {
                if (i >= items[k][j].w) {
                    dp[i] = max(dp[i], dp[i - items[k][j].w] + items[k][j].v);
                }
            }
        }
    }
    int ans = dp[m];
    cout << ans << '\n';
}