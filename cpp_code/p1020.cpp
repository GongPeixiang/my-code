#include <bits/stdc++.h>
using namespace std;

vector<int> height;
vector<int> dp1, dp2; // dp[i]表示长度为i + 1的上升子序列的最小末尾元素

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tmp;
    while (cin >> tmp) 
        height.push_back(tmp);
    for (int h : height) {
        auto it = upper_bound(dp1.begin(), dp1.end(), h, greater<int>());
        if (it == dp1.end()) 
            dp1.push_back(h);
        else 
            *it = h;
    }
    int max_cnt = dp1.size();
    for (int h : height) {
        auto it = lower_bound(dp2.begin(), dp2.end(), h);
        if (it == dp2.end()) 
            dp2.push_back(h);
        else 
            *it = h;
    }
    int need = dp2.size();
    cout << max_cnt << '\n' << need << '\n';
}