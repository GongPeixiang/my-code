#include <bits/stdc++.h>
using std::string;
using std::vector;
using std::set;

int p, k, s, max_sum = 0;
string str = "";
set<string> dict;

void preprocess(vector<vector<int>> &dp) {
    int n = str.size();
    dp.resize(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        if (dict.count(str.substr(i, 1))) 
            dp[i][i] = 1;
    }
    for (int len = 2; len <= n; ++len) {
        for (int i = 0; i + len - 1 < n; ++i) {
            int j = i + len - 1;
            dp[i][j] = dp[i + 1][j];
            for (int l = i; l <= j; ++l) {
                if (dict.count(str.substr(i, l - i + 1))) {
                    ++dp[i][j];
                    break;
                }
            }
        }
    }
}

int solve() {
    int n = str.size();
    vector<vector<int>> f, dp;
    f.resize(n + 1, vector<int>(k + 1, 0));
    preprocess(dp);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= k; ++j) {
            int _i = i - 1, _l;
            for (int l = j - 1; l < i; ++l) {
                _l = l - 1;
                f[i][j] = std::max(f[i][j], f[l][j - 1] + dp[_l + 1][_i]);
            }
        }
    }
    return f[n][k];
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cin >> p >> k;
    std::cin.ignore(2, '\n');
    // std::cin.ignore(cnt, '\n'); 忽略最多cnt个字符,直到读到'\n'
    string tmp;
    for (int i = 0; i < p; ++i) {
        getline(std::cin, tmp);
        // Linux格式下处理Windows文本的换行('\r''\n'),需手动移除'\r'!
        if (!tmp.empty() && tmp.back() == '\r') 
            tmp.pop_back();
        str += tmp;
    }
    std::cin >> s;
    std::cin.ignore(2, '\n');
    for (int i = 0; i < s; ++i) {
        getline(std::cin, tmp);
        if (!tmp.empty() && tmp.back() == '\r') 
            tmp.pop_back();
        dict.insert(tmp);
    }
    int ans = solve();
    std::cout << ans << '\n';
}