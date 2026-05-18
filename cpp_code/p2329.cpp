#include <bits/stdc++.h>
using namespace std;

int m, n;
vector<int> timber, need_len;
int max_done = 0;
vector<bool> vis;

void dfs(int done) {
    int cur_timber = timber[0];
    vector<int> tmp = timber;
    for (int i = 0; i < n; ++i) {
        if (!vis[i] && need_len[i] <= cur_timber) {
            int remain = cur_timber - need_len[i];
            vis[i] = true;
            timber.erase(timber.begin());
            timber.push_back(remain);
            sort(timber.begin(), timber.end(), greater<int>());
            dfs(done + 1);
            timber = tmp;
            vis[i] = false;
        }
    }
    max_done = max(max_done, done);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> m;
    timber.resize(m);
    for (int i = 0; i < m; ++i) 
        cin >> timber[i];
    cin >> n;
    need_len.resize(n);
    vis.resize(n, false);
    for (int i = 0; i < n; ++i) 
        cin >> need_len[i];

    sort(timber.begin(), timber.end(), greater<int>());
    sort(need_len.begin(), need_len.end(), greater<int>());

    dfs(0);

    cout << max_done << '\n';
}