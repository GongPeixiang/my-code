#include <bits/stdc++.h>
using namespace std;

constexpr int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, -1, 0, 1};
constexpr int MAXN = 105;

int n;
bool vis[MAXN][MAXN];

int bfs(int sr, int sc, int dr, int dc) {
    if (dr == sr && dc == sc) 
        return 0;
    memset(vis, 0, sizeof(vis));
    vis[sr][sc] = true;
    queue<pair<int, int>> q;
    q.push(make_pair(sr, sc));
    int steps = 0;
    while (!q.empty()) {
        int len = q.size();
        ++steps;
        while (len--) {
            pair<int, int> cur = q.front();
            q.pop();
            for (int i = 0; i < 4; ++i) {
                int nr = cur.first + dx[i], nc = cur.second + dy[i];
                if (nr == dr && nc == dc)
                    return steps;
                if (nr >= 0 && nr < n && nc >= 0 && nc < n && !vis[nr][nc]) {
                    vis[nr][nc] = true;
                    q.push(make_pair(nr, nc));
                }
            }
        }
    }
    return -1;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    int sr, sc, cr, cc, dr, dc;
    int type;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> type;
            switch(type) {
                case 2 : sr = i; sc = j; break;
                case 3 : cr = i; cc = j; break;
                case 4 : dr = i; dc = j; break;
                default : break;
            }
        }
    }
    int ans = bfs(sr, sc, cr, cc) + bfs(cr, cc, dr, dc);
    cout << ans << '\n';
    return 0;
}