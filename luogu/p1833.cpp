#include <bits/stdc++.h>
using namespace std;

struct Tree {
    int t;
    int c;
    int p;
};

int T, n;
vector<Tree> trees;
vector<int> dp;

int get_time(string &a, string &b) {
    int t;
    if (a.size() < 5) a = '0' + a;
    if (b.size() < 5) b = '0' + b;
    int tmp1 = stoi(a.substr(3, 2)), tmp2 = stoi(b.substr(3, 2));
    int tmp3 = stoi(a.substr(0, 2)), tmp4 = stoi(b.substr(0, 2));
    if (tmp2 >= tmp1) 
        t = (tmp4 - tmp3) * 60 + tmp2 - tmp1;
    else 
        t = (tmp4 - tmp3 - 1) * 60 + 60 + tmp2 - tmp1;
    return t;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string a, b;
    cin >> a >> b >> n;
    T = get_time(a, b);
    trees.resize(n + 1);
    for (int i = 1; i <= n; i++) 
        cin >> trees[i].t >> trees[i].c >> trees[i].p;
    dp.resize(T + 1, 0);
    for (int i = 1; i <= n; i++) {
        if (trees[i].p == 0) {
            // 完全背包
            for (int j = trees[i].t; j <= T; j++) 
                dp[j] = max(dp[j], dp[j-trees[i].t] + trees[i].c);
        }
        else {
            // 多重背包 or 01背包
            for (int j = T; j >= trees[i].t; j--) {
                for (int k = 1; k * trees[i].t <= j && k <= trees[i].p; k++) {
                    dp[j] = max(dp[j], dp[j-k*trees[i].t] + k * trees[i].c);
                }
            }
        }
    }
    int ans = dp[T];
    cout << ans << '\n';
    return 0;
}