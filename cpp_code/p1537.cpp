#include <bits/stdc++.h>
using namespace std;

array<int, 6> cnt, flg = {{0, 0, 0, 0, 0, 0}};

// 二进制分组优化多重背包
bool judge() {
    int sum = 0;
    vector<int> items;
    for (int i = 0; i < 6; ++i) {
        sum += cnt[i] * (i + 1);
        int c = 1, k = cnt[i];
        while (k > c) {
            k -= c;
            items.push_back(c * (i + 1));
            c *= 2;
        }
        items.push_back(k * (i + 1));
    }
    if (sum % 2 == 1)   
        return false;
    vector<bool> dp(sum + 1, false);
    dp[0] = true;
    for (int i = 0; i < items.size(); ++i) {
        int val = items[i];
        for (int v = sum; v >= val; --v) {
            dp[v] = dp[v - val] || dp[v];
        }
    }
    return dp[sum / 2];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int k = 1;
    while (1) {
        for (int i = 0; i < 6; ++i) 
            cin >> cnt[i];
        if (cnt == flg) 
            break;
        cout << "Collection #" << k << ':' << '\n';
        if (judge()) 
            cout << "Can be divided.\n";
        else 
            cout << "Can't be divided.\n";
        cout << '\n';
        ++k;
    }
}