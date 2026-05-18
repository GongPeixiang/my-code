#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> nums;
vector<char> ops;

inline int get_min(int a, int b, int c) {
    return min(a, min(b, c));
}

inline int get_max(int a, int b, int c) {
    return max(a, max(b, c));
}

pair<int, vector<int>> solve() {
    vector<vector<int>> f, g;
    f.resize(2 * n, vector<int>(2 * n, -1e9));
    g.resize(2 * n, vector<int>(2 * n, 1e9));
    for (int i = 0; i < 2 * n; ++i) {
        f[i][i] = nums[i];
        g[i][i] = nums[i];
    }
    for (int len = 2; len <= n; ++len) {
        for (int i = 0; i + len - 1 < 2 * n; ++i) {
            int j = i + len - 1;
            for (int k = i; k < j; ++k) {
                if (ops[k + 1] == '*') {
                    f[i][j] = get_max(f[i][j], f[i][k] * f[k + 1][j],  
                        g[i][k] * g[k + 1][j]);
                    g[i][j] = get_min(g[i][j], g[i][k] * g[k + 1][j], 
                        f[i][k] * g[k + 1][j]);
                }
                else if (ops[k + 1] == '+') {
                    f[i][j] = max(f[i][j], f[i][k] + f[k + 1][j]);
                    g[i][j] = min(g[i][j], g[i][k] + g[k + 1][j]);
                }
            }
        }
    }
    int ans = -1e9;
    for (int i = 0; i < n; ++i) 
        ans = max(ans, f[i][i + n - 1]);
    vector<int> res;
    for (int i = 0; i < n; ++i) {
        if (f[i][i + n - 1] == ans) 
            res.push_back(i + 1);
    }
    return make_pair(ans, res);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    nums.resize(2 * n);
    ops.resize(2 * n);
    char tmp;
    for (int i = 0; i < n; ++i) {
        cin >> tmp >> nums[i];
        nums[i + n] = nums[i];
        if (tmp == 't') 
            ops[i + n] = ops[i] = '+';
        else 
            ops[i + n] = ops[i] = '*';
    }
    auto [ans, res] = solve();
    cout << ans << '\n';
    for (int k : res) 
        cout << k << ' ';
    cout << '\n';
}