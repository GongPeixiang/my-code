#include <bits/stdc++.h>
using namespace std;

int N, K;
string line;
vector<vector<string>> dp;

string multiply(const string &a, const string &b) {
    if (a == "0" || b == "0")
        return "0";
    int len1 = a.size(), len2 = b.size();
    vector<int> res(len1 + len2, 0);
    for (int i = len1 - 1; i >= 0; --i) {
        int carry = 0;
        for (int j = len2 - 1; j >= 0; --j) {
            int x = a[i] - '0', y = b[j] - '0';
            int tmp = x * y + carry + res[i + j + 1];
            // 注意是 i + j + 1,有个加1!
            res[i + j + 1] = tmp % 10;
            carry = tmp / 10;
        }
        if (carry) 
            res[i] += carry;
    }
    string result = "";
    int i = 0;
    while (res[i] == 0) 
        ++i;
    for (; i < res.size(); ++i) 
        result += res[i] + '0';
    return result;
}

string get_max(const string &a, const string &b) {
    if (a.size() > b.size()) 
        return a;
    else if (a.size() < b.size()) 
        return b;
    return a > b ? a : b;
}

int main() {
    cin >> N >> K >> line;
    dp.resize(N + 1);
    for (int i = 1; i <= N; ++i) {
        dp[i].resize(i, "0"); // i个数最多添 i-1 个乘号
        dp[i][0] = line.substr(0, i);
    }
    for (int i = 2; i <= N; ++i) {
        for (int j = 1; j <= i - 1; ++j) {
            for (int l = j; l <= i - 1; ++l) {
                auto tmp = line.substr(l, i - l);
                dp[i][j] = get_max(dp[i][j], multiply(dp[l][j - 1], tmp));
            }
        }
    }
    cout << dp[N][K] << '\n';
}