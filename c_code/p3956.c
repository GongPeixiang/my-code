#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define M 105
#define Q 50005

const int dx[4] = {0, -1, 0, 1}, dy[4] = {-1, 0, 1, 0};

int m, n, maze[M][M];
struct Node {
    int x, y;
    int g;
    int c;  bool mag;
} pq[Q];
int pq_cnt = 0, dist[M][M][3][2];

#define swap(T, a, b) do { T tmp = a; a = b; b = tmp; } while(0)

void pq_push(struct Node node) 
{
    int cur = pq_cnt;
    pq[pq_cnt++] = node;
    while (cur > 0 && pq[cur].g < pq[(cur-1)/2].g) {
        swap(struct Node, pq[cur], pq[(cur-1)/2]);
        cur = (cur - 1) / 2;
    }
}

struct Node pq_pop() 
{
    struct Node ret = pq[0];
    pq[0] = pq[--pq_cnt];
    int cur = 0;
    while (1) {
        int l = 2 * cur + 1, r = 2 * cur + 2;
        int small = cur;
        if (l < pq_cnt && pq[l].g < pq[small].g) small = l;
        if (r < pq_cnt && pq[r].g < pq[small].g) small = r;
        if (small == cur) break;
        swap(struct Node, pq[cur], pq[small]);
        cur = small;
    }
    return ret;
}

int solve() 
{
    memset(dist, 0x3f, sizeof(dist));
    struct Node init = (struct Node){0, 0, 0, maze[0][0], false};
    dist[0][0][maze[0][0]][0] = 0;
    pq_push(init);
    while (pq_cnt != 0) {
        struct Node cur = pq_pop();
        int x = cur.x, y = cur.y, c = cur.c, g = cur.g;
        bool mag = cur.mag;
        if (g > dist[x][y][c][mag==true]) continue;
        if (x == m - 1 && y == m - 1) 
            return g;
        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i], ny = y + dy[i];
            if (nx < 0 || nx >= m || ny < 0 || ny >= m) continue;
            int ng, nc; 
            bool nmag = false;
            if (~maze[nx][ny]) {// maze[nx][ny] != -1
                ng = g + (maze[nx][ny] != c);
                nc = maze[nx][ny];
            } else {
                if (mag) continue;
                ng = g + 2; nc = c;
                nmag = true;
            }
            if (ng < dist[nx][ny][nc][nmag==true]) {
                dist[nx][ny][nc][nmag==true] = ng;
                struct Node nnode = (struct Node){nx, ny, ng, nc, nmag};
                pq_push(nnode);
            }
        }
    }
    return -1;
}

int main() 
{
    memset(maze, 0xff, sizeof(maze));
    scanf("%d %d", &m, &n);
    int x, y, c;
    for (int i = 0; i < n; ++i) {
        scanf("%d %d %d", &x, &y, &c);
        maze[--x][--y] = c;
    }
    int ans = solve();
    printf("%d\n", ans);
    return 0;
}