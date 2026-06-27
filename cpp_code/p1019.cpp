#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 50;

int n, maxlen = 0xcfcfcfcf;
string dict[MAXN];
bool vis[MAXN];

int check(const string& str, const string& a) {
    int len = str.size() > a.size()? a.size(): str.size();
    for (int i = 1; i < len; ++i) {
        if (str.substr(str.size() - i, i) == a.substr(0, i)) 
            return i;
    }
    return -1;
}

void dfs(string& str) {
    int len = str.size();
    if (len > maxlen) maxlen = len;
    for (int i = 0; i < 2 * n; ++i) {
        int k = check(str, dict[i]);
        if (vis[i] || k == -1) continue;
        vis[i] = true;
        str += dict[i].substr(k);
        dfs(str);
        str.erase(len);
        vis[i] = false; 
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    char src;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> dict[i];
        dict[i + n] = dict[i];
    }
    cin >> src;
    for (int i = 0; i < 2 * n; ++i) {
        memset(vis, 0, sizeof(vis));
        if (dict[i][0] != src) continue;
        string str = dict[i];
        vis[i] = true;
        dfs(str);
    }
    cout << maxlen << '\n';
    return 0;
}