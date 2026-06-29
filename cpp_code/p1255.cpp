#include <bits/stdc++.h>
using namespace std;

int n;
vector<string> dp;

string add(string &a, string &b) {
    string res;
    int len = max(a.size(), b.size());
    res.resize(len);
    while (a.size() < len) 
        a = '0' + a;
    while (b.size() < len) 
        b = '0' + b;
    int carry = 0;
    for (int i = a.size() - 1; i >= 0; --i) {
        int x = a[i] - '0', y = b[i] - '0';
        int tmp = x + y + carry;
        carry = tmp / 10;
        res[i] = (tmp % 10) + '0';
    }
    if (carry) 
        res = '1' + res;
    return res;
}

int main() {
    cin >> n;
    dp.resize(n + 1);
    dp[0] = "1", dp[1] = "1";
    for (int i = 2; i <= n; ++i) {
        dp[i] = add(dp[i - 1], dp[i - 2]);
    }
    cout << dp[n] << '\n';
}