#include <bits/stdc++.h>
using namespace std;

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
            res[i + j + 1] = tmp % 10;
            carry = tmp / 10;
        }
        if (carry) 
            res[i] += carry;
    }
    int i = 0;
    while (res[i] == 0) 
        ++i;
    string result = "";
    for (; i < res.size(); ++i) 
        result += res[i] + '0';
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string a, b;
    cin >> a >> b;
    string ans = multiply(a, b);
    cout << ans << '\n';
}