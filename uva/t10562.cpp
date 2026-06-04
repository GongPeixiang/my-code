#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 205;

int n;
string buf[MAXN];

void dfs(int dep, int c) {
    cout << buf[dep][c] << '(';
    if (dep + 3 < n && buf[dep+1][c] == '|') {
        int i = c;
        while (i - 1 >= 0 && buf[dep+2][i-1] == '-') --i;
        while (i < buf[dep+2].size() && buf[dep+2][i] == '-' && i < buf[dep+3].size()) {
            if (buf[dep+3][i] != ' ') 
                dfs(dep + 3, i);
            ++i;
        } 
    }
    cout << ')';
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int T;
    cin >> T;
    cin.ignore(1000, '\n');
    while (T--) {
        n = 0;
        for (auto &str: buf) str.clear();
        while (1) {
            getline(cin, buf[n]);
            if (buf[n][0] == '#') break;
            else ++n;
        }
        cout << '(';
        if (n) {
            for (int i = 0; i < buf[0].size(); ++i) {
                if (buf[0][i] != ' ') {
                    dfs(0, i);
                    break;
                }
            }
        }
        cout << ')' << '\n';
    }
    return 0;
}