#include <bits/stdc++.h>
using namespace std;

const array<array<int, 2>, 4> dir = {{ {-1, 0}, {0, -1}, {1, 0}, {0, 1} }};
int n, sr, sc, card_r, card_c, dr, dc;
vector<vector<int>> grid;

int bfs(int sr, int sc, int dr, int dc) {
    if (dr == sr && dc == sc)
        return 0;
    vector<vector<bool>> visited(n, vector<bool>(n, false));
    visited[sr][sc] = true;
    queue<pair<int, int>> q;
    q.push(make_pair(sr, sc));
    int steps = 0;
    while (!q.empty()) {
        int len = q.size();
        steps++;
        while (len--) {
            pair<int, int> cur = q.front();
            q.pop();
            for (int i = 0; i < 4; i++) {
                int nr = cur.first + dir[i][0], nc = cur.second + dir[i][1];
                if (nr == dr && nc == dc)
                    return steps;
                if (nr >= 0 && nr < n && nc >= 0 && nc < n && 
                    !visited[nr][nc]) {
                    visited[nr][nc] = true;
                    q.push(make_pair(nr, nc));
                }
            }
        }
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    grid.resize(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
            switch(grid[i][j]) {
                case 2 : sr = i; sc = j; break;
                case 3 : card_r = i; card_c = j; break;
                case 4 : dr = i; dc = j; break;
                default : break;
            }
        }
    }
    int s1 = bfs(sr, sc, card_r, card_c);
    int s2 = bfs(card_r, card_c, dr, dc);
    int s = s1 + s2;
    cout << s << '\n';
    return 0;
}