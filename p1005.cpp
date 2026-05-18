#include <bits/stdc++.h>
using std::string;

constexpr int MAXN = 80;
constexpr int MAXM = 80;

int n, m;
string dp[MAXM + 5][MAXM + 5], matrix[MAXN + 5][MAXM + 5];
string pow2_tab[MAXM + 5];

string add(const string &a, const string &b) {
    int len = std::max(a.size(), b.size());
    std::vector<int> res(len, 0);
    int carry = 0;
    int k = len - 1, i = a.size() - 1, j = b.size() - 1;
    while (k >= 0) {
        int x = i >= 0 ? a[i] - '0' : 0;
        int y = j >= 0 ? b[j] - '0' : 0;
        int tmp = x + y + carry;
        res[k] = tmp % 10;
        carry = tmp / 10;
        --k, --i, --j;
    }
    string ans = "";
    if (carry) ans += '1';
    for (int i = 0; i < len; ++i) 
        ans += (char)(res[i] + '0');
    return ans;
}

string multiply(const string &a, const string &b) {
    if (a == "0" || b == "0") 
        return "0";
    int la = a.size(), lb = b.size();
    int len = la + lb;
    std::vector<int> res(len, 0);
    for (int i = la - 1; i >= 0; --i) {
        int carry = 0;
        for (int j = lb - 1; j >= 0; --j) {
            int x = a[i] - '0', y = b[j] - '0';
            int tmp = x * y + carry + res[i+j+1];
            res[i+j+1] = tmp % 10;
            carry = tmp / 10;
        }
        if (carry) res[i] += carry;
    }
    int i = 0;
    while (res[i] == 0) ++i;
    string ans = "";
    for (; i < len; ++i) 
        ans += (char)(res[i] + '0');
    return ans;
}

string get_max(string &a, string &b) {
    if (a.size() != b.size()) 
        return a.size() > b.size() ? a : b;
    return a > b ? a : b;
}

void preprocess() {
    pow2_tab[0] = "1";
    for (int i = 1; i <= m; ++i) {
        pow2_tab[i] = multiply(pow2_tab[i - 1], "2");
    }
}

string solve() {
    preprocess();
    string score = "0";
    for (int r = 0; r < n; ++r) {
        for (int i = 0; i <= m; ++i) {
            for (int j = 0; j <= m; ++j) {
                dp[i][j] = "0";
            }
        }
        for (int i = 0; i < m; ++i) 
            dp[i][i] = multiply(matrix[r][i], pow2_tab[m]);
        for (int len = 2; len <= m; ++len) {
            for (int i = 0; i + len - 1 < m; ++i) {
                int j = i + len - 1;
                string fac = pow2_tab[m - len + 1];
                auto res1 = add(dp[i + 1][j], multiply(fac, matrix[r][i]));
                auto res2 = add(dp[i][j - 1], multiply(fac, matrix[r][j]));
                dp[i][j] = get_max(res1, res2);
            }
        }
        score = add(dp[0][m - 1], score);
    }
    return score;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cin >> n >> m;
    int tmp;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            std::cin >> tmp;
            matrix[i][j] = std::to_string(tmp);
        }
    }
    string ans = solve();
    std::cout << ans << '\n';
    return 0;
}