#include <bits/stdc++.h>
using namespace std;

int n, sum = 0;
vector<int> len;
// vector<bool>部分情况会有奇怪的问题,用vector<char>代替
vector<vector<char>> dp;

inline bool check(int a, int b, int c) {
    return a + b > c && a + c > b && b + c > a;
}

inline double get_area(double a, double b, double c) {
    double p = (a + b + c) / 2;
    return sqrt(p * (p - a) * (p - b) * (p - c));
}

int solve() {
    double max_area = -1;
    // 这个dp的定义是关键!
    // 只存储用前k个木板能否拼出有2边为i和j的三边,先不考虑三角形是否成立,后面判断
    // 本质是用状态压缩代替顺序搜索
    dp.resize(sum / 2 + 1, vector<bool>(sum / 2 + 1, false));
    dp[0][0] = true;
    for (int k = 1; k <= n; ++k) {
        int lk = len[ k - 1];
        for (int i = sum / 2; i >= 0; --i) {
            for (int j = sum / 2; j >= 0; --j) {
                if (i >= lk && dp[i - lk][j] || j >= lk && dp[i][j - lk])
                    dp[i][j] = true; 
            }
        }
    }
    for (int i = sum / 2; i >= 0; --i) {
        for (int j = sum / 2; j >= 0; --j) {
            if (dp[i][j] && check(i, j, sum - i - j)) {
                double area = get_area(i, j, sum - i - j);
                max_area = max(max_area, area);
            }
        }
    }
    if (max_area != -1) 
        return (int)(max_area * 100);
    return -1;
}

int main() {
    cin >> n;
    len.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> len[i];
        sum += len[i];
    }
    int ans = solve();
    cout << ans << '\n';
}