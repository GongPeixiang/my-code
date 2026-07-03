#include <bits/stdc++.h>
using namespace std;

constexpr int MAXR = 10, STAR = 100;
constexpr int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};

constexpr int east[6][6] = {
    {-1, 2, 4, 1, 3, -1},
    {3, -1, 0, 5, -1, 2},
    {1, 5, -1, -1, 0, 4},
    {4, 0, -1, -1, 5, 1},
    {2, -1, 5, 0, -1, 3},
    {-1, 3, 1, 4, 2, -1}
};

int R, C, maze[MAXR][MAXR], sr, sc, st, sf;
bool vis[MAXR][MAXR][6][6];
struct Node {
    int r, c, top, front;
} pre[MAXR][MAXR][6][6];
vector<Node> path;

inline void roll(int i, int t, int f, int &nt, int &nf) {
    int e = east[t][f];
    switch (i) {
        case 0: nt = f;     nf = 5 - t; break;    
        case 1: nt = 5 - e; nf = f;     break;  
        case 2: nt = 5 - f; nf = t;     break;    
        case 3: nt = e;     nf = f;     break;  
    }
}

void solve() {
    queue<Node> q;
    vis[sr][sc][st][sf] = true;
    pre[sr][sc][st][sf] = Node{-1, -1, -1, -1};
    q.push(Node{sr, sc, st, sf});
    int lyr = 0;
    while (!q.empty()) {
        int lyrsize = q.size();
        for (int k = 0; k < lyrsize; ++k) {
            Node cur = q.front(); q.pop();
            int r = cur.r, c = cur.c, t = cur.top, f = cur.front;
            if (r == sr && c == sc && lyr >= 1) {
                Node trk = cur;
                while (trk.r != -1) {
                    path.push_back(trk);
                    trk = pre[trk.r][trk.c][trk.top][trk.front];
                }
                reverse(path.begin(), path.end());
                return;
            }
            for (int i = 0; i < 4; ++i) {
                int nr = r + dx[i], nc = c + dy[i];
                if (nr < 0 || nr >= R || nc < 0 || nc >= C) continue;
                int nt, nf;
                roll(i, t, f, nt, nf);
                if (maze[nr][nc] == t || maze[nr][nc] == STAR) {
                    if ((nr == sr && nc == sc && lyr >= 2) || !vis[nr][nc][nt][nf]) {
                        q.push(Node{nr, nc, nt, nf});
                        vis[nr][nc][nt][nf] = true;
                        pre[nr][nc][nt][nf] = cur;
                    }
                }
            }
        }
        ++lyr;
    }
}

int main() {
    char name[50];
    while (1) {
        scanf("%s", name);
        if (strcmp(name, "END")==0) break;
        scanf("%d %d %d %d %d %d", &R, &C, &sr, &sc, &st, &sf);
        --sr, --sc; --st, --sf;
        for (int i = 0; i < R; ++i)
            for (int j = 0; j < C; ++j) {
                scanf("%d", &maze[i][j]);
                if (--maze[i][j] == -2) maze[i][j] = STAR;
            }
        memset(vis, 0, sizeof(vis));
        memset(pre, 0xff, sizeof(pre));
        path.clear();
        solve();
        printf("%s\n", name);
        int n = path.size();
        if (!n) printf("  No Solution Possible\n");
        else {
            for (int i = 0; i < n; ++i) {
                int k = i % 9;
                if (!k) printf("  ");
                printf("(%d,%d)", path[i].r + 1, path[i].c + 1);
                if (i != n - 1) putchar(',');
                if (k == 8 || i == n - 1) putchar('\n');
            }
        }
    }
    return 0;
}
