#include <bits/stdc++.h>
using namespace std;

int m, n;
vector<int> timber, need_len, cpy;

bool dfs(const int div, int done, int cur) {
    if (done == div) 
        return true;
    if (n - cur + done < div) 
        return false;
    for (int i = 0; i < m; ++i) {
        if (cpy[i] >= need_len[cur]) {
            cpy[i] -= need_len[cur];
            if (dfs(div, done + 1, cur + 1)) 
                return true;
            cpy[i] += need_len[cur];
        }
    }
    return dfs(div, done, cur + 1);
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
    for (int i = 0; i < n; ++i) 
        cin >> need_len[i];

    sort(need_len.begin(), need_len.end(), greater<int>());
    sort(timber.begin(), timber.end(), greater<int>());
    
    // 把问题转化成给定个数下的可行性验证
    // 利用二分, 极大地减少搜索个数
    int ans = 0;
    int l = 0, r = n;
    while (l <= r) {
        int mid = (l + r) / 2;
        cpy = timber;
        if (dfs(mid, 0, 0)) {
            ans = mid;
            l = mid + 1;
        }
        else
            r = mid - 1;
    }

    cout << ans << '\n';
}