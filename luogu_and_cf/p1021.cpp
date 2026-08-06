#include <bits/stdc++.h>
using namespace std;

constexpr int INF = 5000;
int n, k, MAX = 0;
vector<int> result, cur;

int cal_max(int dep) {
    int max_val = n * cur[dep - 1];
    vector<int> dp(max_val + 1, INF);
    // dp[j]表示凑出金额j所需的最少张数, unbounded pack
    dp[0] = 0;
    for (int i = 1; i <= dep; ++i) {
        int cur_i = cur[i - 1];
        for (int j = cur_i; j <= max_val; ++j) {
            dp[j] = min(dp[j], dp[j - cur_i] + 1);
        }
    }
    /*
        或正向递推(注: 01背包不行)
        for (int i = 1; i <= dep; ++i) {
            for (int j = 0; j <= max_val; ++j) {
                if (j + cur[i - 1] > max_val) 
                    continue;
                int nj = j + cur[i - 1];
                dp[nj] = min(dp[nj], dp[j] + 1);
            }
        }
    */
    for (int i = 1; i <= max_val; ++i) {
        if (dp[i] > n) 
            return i - 1;
    }
    return max_val;
}

// dep从1开始，方便dp
void dfs(int dep) {
    if (dep == k) {
        int max_tmp = cal_max(k);
        if (max_tmp > MAX) {
            MAX = max_tmp;
            result = cur;
        }
        return;
    }
    int max_tmp = cal_max(dep);
    for (int num = cur[dep - 1] + 1; num <= max_tmp + 1; ++num) {
        cur.push_back(num);
        dfs(dep + 1);
        cur.pop_back();
    }
}

int main() {
    cin >> n >> k;
    cur.push_back(1);
    dfs(1);
    for (auto num : result) 
        cout << num << ' ';
    cout << '\n' << "MAX=" << MAX << '\n';
}