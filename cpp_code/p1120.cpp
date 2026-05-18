#include <bits/stdc++.h>
using namespace std;

int n, sum = 0;
vector<int> frag_len;
vector<bool> vis;

bool dfs(int done, int cur_len, int cur_pos, const int div,
const int len) {
    if (done == div) 
        return true;
    if (cur_len == len) 
        return dfs(done + 1, 0, 0, div, len);
    int skip = 0;
    for (int i = cur_pos; i < n ; ++i) {
        if (vis[i] || frag_len[i] == skip) 
            continue;
        if (frag_len[i] + cur_len <= len) {
            vis[i] = true;
            if (dfs(done, cur_len + frag_len[i], i + 1, div, len)) 
                return true;
            skip = frag_len[i];
            vis[i] = false;
            if (cur_len == 0 || cur_len + frag_len[i] == len) 
                return false;
        }
    }
    return false;
}

int solve() {
    int start = max(sum / n , frag_len[0]);
    for (int len = start; len <= sum / 2; ++len) {
        if (sum % len != 0) 
            continue;
        int div = sum / len;
        vis.assign(n, false);
        if (dfs(0, 0, 0, div, len)) 
            return len;
    }
    return sum;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    frag_len.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> frag_len[i];
        sum += frag_len[i];
    }
    sort(frag_len.begin(), frag_len.end(), greater<int>());

    int ans = solve();
    cout << ans << '\n';
}