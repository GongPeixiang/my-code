#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> nums, sum;
vector<vector<int>> f_max, f_min;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    nums.resize(2 * n + 1);
    sum.resize(2 * n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        cin >> nums[i];
        nums[i + n] = nums[i];
    }
    for (int i = 1; i <= 2 * n; ++i) 
        sum[i] = sum[i - 1] + nums[i];

    f_max.resize(2 * n + 1, vector<int>(2 * n + 1, 0));
    f_min.resize(2 * n + 1, vector<int>(2 * n + 1, 1e5));
    for (int i = 1; i <= 2 * n; ++i) 
        f_min[i][i] = f_max[i][i] = 0;

    for (int len = 2; len <= n; ++len) {
        for (int i = 1; i + len - 1 <= 2 * n; ++i) {
            int j = i + len - 1;
            for (int k = i; k < j; ++k) {
                f_min[i][j] = min(f_min[i][j], 
                    f_min[i][k] + f_min[k + 1][j] + sum[j] - sum[i - 1]);
                f_max[i][j] = max(f_max[i][j], 
                    f_max[i][k] + f_max[k + 1][j] + sum[j] - sum[i - 1]);
            }
        }
    }

    int ans_min = 1e6, ans_max = -1e6;
    for (int i = 1; i <= n; ++i) {
        ans_min = min(ans_min, f_min[i][i + n - 1]);
        ans_max = max(ans_max, f_max[i][i + n - 1]);
    }

    cout << ans_min << '\n' << ans_max << '\n';
}