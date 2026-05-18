#include <bits/stdc++.h>
using namespace std;

struct Item {
    int r, v, t;
};

int n, m;
vector<int> cls_time;
vector<Item> items;

int solve() {
    int max_time = cls_time[0];
    vector<vector<int>> dp(m + 1, vector<int>(max_time + 1, 0));
    // dp[i][j]从前i个物品在时间j内选择能获得的最大价值
    Item item_i;
    for (int i = 1; i <= m; ++i) {
        item_i = items[i - 1];
        int r = item_i.r, t = item_i.t, v = item_i.v;
        for (int j = 0; j <= max_time; ++j) {
            if (j < t) 
                dp[i][j] = dp[i - 1][j];
            else if (j >= t && j < cls_time[r]) 
                dp[i][j] = max(dp[i - 1][j], dp[i][j - t] + v);
            else 
                dp[i][j] = dp[i][cls_time[r] - 1];
        }
    }
    return dp[m][max_time];  
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    cls_time.resize(n);
    items.resize(m);
    for (int i = 0; i < n; ++i) {
        cin >> cls_time[i];
        if (i == 0) 
            continue;
        cls_time[i] = min(cls_time[i], cls_time[i - 1]);
    }
    for (int i = 0; i < m; ++i) 
        cin >> items[i].r >> items[i].v >> items[i].t;
    sort(items.begin(), items.end(), [](const Item &a, const Item &b) {
        if (a.r != b.r) 
            return a.r > b.r;
        return a.t < b.t;
    });
    int max_val = solve();
    cout << max_val << '\n';
}