#include <bits/stdc++.h>
using namespace std;

constexpr int LEN = 32;

int vis[LEN][LEN], cnt = 0;
string str;

void dfs(int &dep, int le, int ri, int up, int lo) {
    char ch = str[dep++];
    if (ch == 'f') {
        for (int i = le; i < ri; ++i) {
            for (int j = up; j < lo; ++j) {
                if (!vis[i][j]) {
                    vis[i][j] = 1;
                    ++cnt;
                }
            }
        }
    } else if (ch == 'p') {
        int mid1 = le + (ri - le) / 2 , mid2 = up + (lo - up) / 2;
        dfs(dep, mid1, ri, up, mid2);
        dfs(dep, le, mid1, up, mid2);
        dfs(dep, le, mid1, mid2, lo);
        dfs(dep, mid1, ri, mid2, lo);
    }
    return;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int N;
    cin >> N;
    while (N--) {
        memset(vis, 0, sizeof(vis));
        cnt = 0;
        for (int i = 0; i < 2; ++i) {
            cin >> str;
            int dep = 0;
            dfs(dep, 0, LEN, 0, LEN);
        }
        cout << "There are " << cnt << " black pixels.\n";
    }
    return 0;
}