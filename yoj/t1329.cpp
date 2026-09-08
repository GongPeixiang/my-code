#include <bits/stdc++.h>
using namespace std;

constexpr int N = 105, MAXS = 20005;

int n, nums[N], sum = 0;
bool dp[MAXS];

bool solve() {
    if (sum % 2) return false;
    dp[0] = true;
    for (int i = 0; i < n; i++) {
        int num = nums[i];
        for (int j = sum / 2; j >= num; j--) dp[j] |= dp[j-num];
    }
    return dp[sum/2];
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for (int i = 0; i < n; i++) { 
        cin >> nums[i];
        sum += nums[i];
    }
    cout << solve() << '\n';
    return 0;
}