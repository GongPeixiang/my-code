#include <bits/stdc++.h>
using namespace std;

vector<int> memo;

int dfs(int k) {
    if (memo[k - 1] != -1) return memo[k - 1];
    int result = 1; // 这个数本身
    for (int i = k / 2; i >= 1; i--) {
        result += dfs(i);
    }
    memo[k - 1] = result;
    return result;
}

int main() {
    int n = 0;
    cin >> n;
    memo.resize(n, -1);
    memo[0] = 1;   // 代表1只有1个，注意是 0-based 索引
    int ans = dfs(n);
    cout << ans << endl;
    return 0;
}
