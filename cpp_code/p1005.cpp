#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<vector<string>> matrix;
array<string, 81> pow2_table;

string add(const string &a, const string &b) {
    if (a == "0" || b == "0") 
        return a == "0" ? b : a;
    int len = max(a.size(), b.size());
    vector<int> res(len, 0);
    int carry = 0;
    int w = len - 1, i = a.size() - 1, j = b.size() - 1;
    while (w >= 0) {
        int x = i >= 0 ? a[i] - '0' : 0;
        int y = j >= 0 ? b[j] - '0' : 0;
        int tmp = x + y + carry;
        res[w] = tmp % 10;
        carry = tmp / 10;
        --w; 
        --i, --j;
    }
    if (carry) 
        res.insert(res.begin(), carry);
    string result = "";
    for (int num : res) 
        result += char(num + '0');
    return result;
}

string multiply(const string &a, const string &b) {
    if (a == "0" || b == "0") 
        return "0";
    int len = a.size() + b.size();
    vector<int> res(len, 0);
    for (int i = a.size() - 1; i >= 0; --i) {
        int carry = 0;
        for (int j = b.size() - 1; j >= 0; --j) {
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
    for (; i < len; ++i) 
        result += char(res[i] + '0');
    return result;
}

string get_max(const string &a, const string &b) {
    if (a.size() > b.size()) 
        return a;
    else if (a.size() < b.size()) 
        return b;
    return a > b ? a : b;
}

string pow2(int k) {
    string res = "1";
    for (int i = 0; i < k; ++i) 
        res = multiply(res, "2");
    return res;
}

void get_table(int m) {
    for (int i = 1; i <= m; ++i) 
        pow2_table[i] = pow2(i);
}

string solve() {
    get_table(m);
    string max_score = "0";
    vector<vector<string>> dp;
    for (int r = 0; r < n; ++r) {
        dp.assign(m, vector<string>(m, "0"));
        for (int i = 0; i < m; ++i) 
            dp[i][i] = multiply(matrix[r][i], pow2_table[m]);
        for (int len = 2; len <= m; ++len) {
            for (int i = 0; i + len - 1 < m; ++i) {
                int j = i + len - 1;
                string fac = pow2_table[m - len + 1];
                auto res1 = add(dp[i + 1][j], multiply(fac, matrix[r][i]));
                auto res2 = add(dp[i][j - 1], multiply(fac, matrix[r][j]));
                dp[i][j] = get_max(res1, res2);
            }
        }
        max_score = add(dp[0][m - 1], max_score);
    }
    return max_score;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    matrix.resize(n, vector<string>(m));
    int tmp;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> tmp;
            matrix[i][j] = to_string(tmp);
        }
    }
    string ans = solve();
    cout << ans << '\n';
}