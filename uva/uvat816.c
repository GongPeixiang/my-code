#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXN 10
#define MAXQ 15000

const int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};
const char dirs[] = "NESW", turns[] = "LFR";

int sr, sc, dr, dc, sdir;
int vis[MAXN][MAXN][4],ok[MAXN][MAXN][4][3]; // (i+3)%4, i%4, (i+1)%4

struct Node {
    int r, c, dir;
} q[MAXQ], pre[MAXN][MAXN][4], path[MAXN*MAXN*4+5];
int path_len, head = 0, tail = 0;

static inline int get_dir(char d) { return strchr(dirs, d) - dirs; }

static inline int get_turn(char d) { return strchr(turns, d) - turns; }

void solve() 
{
    memset(vis, 0, sizeof(vis));
    memset(pre, 0xff, sizeof(pre));
    path_len = 0;
    int nr = sr + dx[sdir], nc = sc + dy[sdir];
    vis[nr][nc][sdir] = 1;
    pre[nr][nc][sdir] = (struct Node){sr, sc, sdir};
    q[tail++] = (struct Node){nr, nc, sdir};
    while (head != tail) {
        struct Node cur = q[head++];
        int r = cur.r, c = cur.c, dir = cur.dir;
        if (r == dr && c == dc) {
            struct Node trk = cur;
            while (1) {
                if (trk.r == -1) break;
                path[path_len++] = trk;
                trk = pre[trk.r][trk.c][trk.dir];
            }
            for (int i = 0; i < path_len / 2; i++) {
                struct Node tmp = path[i];
                path[i] = path[path_len-1-i];
                path[path_len-1-i] = tmp;
            }
            return;
        }
        for (int i = 0; i < 3; ++i) {
            if (!ok[r][c][dir][i]) continue;
            int ndir = (dir - 1 + i + 4) % 4;
            int nr = r + dx[ndir], nc = c + dy[ndir];
            if (nr < 1 || nr > 9 || nc < 1 || nc > 9) continue;
            if (!vis[nr][nc][ndir]) {
                vis[nr][nc][ndir] = 1;
                pre[nr][nc][ndir] = cur;
                q[tail++] = (struct Node){nr, nc, ndir};
            }
        }
    }
}

int main() 
{
    char name[100];
    while (scanf("%s", name) == 1 && strcmp(name, "END") != 0) {
        char ds;
        scanf("%d %d %c %d %d", &sr, &sc, &ds, &dr, &dc);
        sdir = get_dir(ds);
        memset(ok, 0, sizeof(ok));
        while (getchar() != '\n');
        int r, c;
        char line[256];
        while (1) {
            if (!fgets(line, sizeof(line), stdin)) continue;;
            char *tok = strtok(line, " "); 
            if (!tok) continue;
            r = atoi(tok); if (!r) break;
            tok = strtok(NULL, " ");
            if (!tok) continue;
            c = atoi(tok);
            while (tok=strtok(NULL, " ")) {
                if (tok[0] == '*') break;
                int di = get_dir(tok[0]);
                for (int j = 1; tok[j] != '\0'; ++j) {
                    int t = get_turn(tok[j]);
                    ok[r][c][di][t] = 1;
                }
            }
        }
        solve();
        printf("%s\n", name);
        if (path_len == 0) 
            printf("  No Solution Possible\n");
        else {
            for (int i = 0; i < path_len; ++i) {
                if (i % 10 == 0) printf(" ");
                printf(" (%d,%d)", path[i].r, path[i].c);
                if ((i + 1) % 10 == 0 || i == path_len - 1)
                    printf("\n");
            }
        }
    }
    return 0;
}