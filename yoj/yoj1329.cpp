#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> nums;

bool judge() {
    int sum = 0;
    for (int i = 0; i < n; ++i) 
        sum += nums[i];
    if (sum % 2) 
        return false;
    vector<int> dp(sum + 1, false);
    dp[0] = true;
    for (int i = 0; i < n; ++i) {
        int num = nums[i];
        for (int s = sum; s >= num; --s) {
            dp[s] = dp[s - num] || dp[s];
        }
    }
    return dp[sum / 2];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    nums.resize(n);
    for (int i = 0; i < n; ++i) 
        cin >> nums[i];
    bool ans = judge();
    cout << ans << '\n';
}