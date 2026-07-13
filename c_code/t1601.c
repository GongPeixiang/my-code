/* morning after halloween */
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXN 150
#define MAXQ 4000000
const int dx[5] = {0, -1, 0, 1, 0}, dy[5] = {0, 0, 1, 0, -1};
// the direction array is only used in preprocess

int deg[MAXN], g[MAXN][5], src[3], dst[3];
int dist[MAXN][MAXN][MAXN];
struct Node {
    int a, b, c;
} q[MAXQ];

static inline int illegal(int x, int y, int nx, int ny) 
{ return (nx == ny)||(x == ny && y == nx); }

int solve() 
{
    memset(dist, 0xff, sizeof(dist));
    int head = 0, tail = 0;
    q[tail++] = (struct Node){src[0], src[1], src[2]};
    dist[src[0]][src[1]][src[2]] = 0;
    while (head != tail) {
        struct Node cur = q[head++];
        int a = cur.a, b = cur.b, c = cur.c;
        if (a == dst[0] && b == dst[1] && c == dst[2]) 
            return dist[a][b][c];
        for (int i = 0; i < deg[a]; ++i) {
            int na = g[a][i];
            for (int j = 0; j < deg[b]; ++j) {
                int nb = g[b][j];
                if (illegal(a, b, na, nb)) continue;
                for (int k = 0; k < deg[c]; ++k) {
                    int nc = g[c][k];
                    if (illegal(a, c, na, nc) || illegal(b, c, nb, nc)) continue;
                    if (~dist[na][nb][nc]) continue;
                    dist[na][nb][nc] = dist[a][b][c] + 1;
                    q[tail++] = (struct Node){na, nb, nc};
                }
            }
        }
    }
    return -1;
}

int main() 
{
    char maze[20][20];
    int w, h, sum;
    int cnt = 0, x[MAXN], y[MAXN], id[20][20], ch;
    while (scanf("%d%d%d", &w, &h, &sum)==3) {
        if (!w && !h && !sum) break;
        cnt = 0;
        memset(deg, 0, sizeof(deg));
        for (int i = 0; i < h; ++i) {
            while ((ch=getchar()) != '\n');
            for (int j = 0; j < w; ++j) {
                maze[i][j] = getchar();
                if (maze[i][j] != '#') {
                    x[cnt] = i, y[cnt] = j;
                    id[i][j] = cnt;
                    if (islower(maze[i][j])) src[maze[i][j]-'a'] = cnt;
                    if (isupper(maze[i][j])) dst[maze[i][j]-'A'] = cnt;
                    ++cnt;
                }
            }
        }
        for (int i = 0; i < cnt; ++i) {
            for (int k = 0; k < 5; ++k) {
                int xx = x[i] + dx[k], yy = y[i] + dy[k];
                if (xx < 0 || xx >= h || yy < 0 || yy >= w) continue;
                if (maze[xx][yy] != '#') g[i][deg[i]++] = id[xx][yy];
            }
        }
        if (sum <= 2) { src[2] = dst[2] = g[cnt][0] = cnt; deg[cnt++] = 1; }
        if (sum <= 1) { src[1] = dst[1] = g[cnt][0] = cnt; deg[cnt++] = 1; }
        int ans = solve();
        printf("%d\n", ans);
    }
    return 0;
}
