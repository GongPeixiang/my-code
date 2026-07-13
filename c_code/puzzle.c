/* eight puzzle C99 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXS 362880 // factorial(9)
#define MAXP 100

const int dx[4] = {0, 1, 0, -1}, dy[4] = {-1, 0, 1, 0};
const int fact[9] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320};

int board[3][3], tgt[3][3], pos[9][2];
struct Node {
    int state;
    int g, f;
} pq[MAXS], pre[MAXS];
int pq_cnt = 0, dist[MAXS], path[MAXP], path_cnt = 0;

#define swap(T, a, b) do {  T tmp = a; a = b; b = tmp;  } while(0)

inline static bool check() { return memcmp(board, tgt, sizeof(tgt)) == 0; }

int encode() // cantor
{
    int res = 0, cnt = 0;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            int a = board[i][j], rk = 0;
            for (int ii = i; ii < 3; ++ii) {
                for (int jj = (ii == i ? j+1: 0); jj < 3; ++jj) {
                    if (board[ii][jj] < a) ++rk;
                }
            }
            res += rk * fact[8-cnt]; ++cnt;
        }
    }
    return res;
}

void decode(int code, int *zr, int *zc) 
{
    int cnt = 8, num[9] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    for (int i = 0; i < 9; ++i) {
        int rk = code / fact[8-i], val = num[rk];
        code %= fact[8-i];
        board[i/3][i%3] = val;
        if (board[i/3][i%3] == 0) { *zr = i/3; *zc = i%3; }
        if (rk < 8) memmove(num + rk, num + rk + 1, sizeof(int) * (8-rk));
    }
}

int h() 
{
    int cnt = 0;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            int val = board[i][j];
            cnt += abs(i - pos[val][0]) + abs(j - pos[val][1]);
        }
    }
    return cnt;
}

void pq_push(struct Node node) 
{
    int cur = pq_cnt;
    pq[pq_cnt++] = node;
    while (cur > 0 && pq[cur].f < pq[(cur-1)/2].f) {
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
        if (l < pq_cnt && pq[l].f < pq[small].f) small = l;
        if (r < pq_cnt && pq[r].f < pq[small].f) small = r;
        if (small == cur) break;
        swap(struct Node, pq[cur], pq[small]);
        cur = small;
    }
    return ret;
}

bool solve() 
{
    memset(dist, 0xff, sizeof(dist));
    int init_stat = encode();
    struct Node init = (struct Node){init_stat, 0, h()};
    pre[init_stat] = (struct Node){-1, -1, -1};
    dist[init_stat] = 0;
    pq_push(init);
    while (pq_cnt != 0) {
        struct Node cur = pq_pop();
        int state = cur.state, g = cur.g;
        if (g > dist[state]) continue;
        int zr, zc;
        decode(state, &zr, &zc);
        if (check()) {
            struct Node trk = cur;
            while (trk.state != init_stat) {
                path[path_cnt++] = trk.state;
                trk = pre[trk.state];
            }
            for (int i = 0; i < path_cnt / 2; ++i) 
                swap(int, path[i], path[path_cnt-1-i]);
            return true;
        }
        for (int i = 0; i < 4; ++i) {
            int nr = zr + dx[i], nc = zc + dy[i];
            if (nr < 0 || nr >= 3 || nc < 0 || nc >= 3) continue;
            swap(int, board[zr][zc], board[nr][nc]);
            int nstate = encode(), ng = g + 1;
            if (dist[nstate] == -1 || ng < dist[nstate]) {
                dist[nstate] = ng;
                pre[nstate] = cur;
                struct Node nnode = (struct Node){nstate, ng, ng + h()};
                pq_push(nnode);
            }
            swap(int, board[zr][zc], board[nr][nc]);
        }
    }
    return false;
}

int main() 
{
    printf("please enter your initial board:\n");
    for (int i = 0; i < 3; ++i) 
        for (int j = 0; j < 3; ++j) 
            scanf("%d", &board[i][j]);
    printf("please enter your target board:\n");
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            scanf("%d", &tgt[i][j]);
            int val = tgt[i][j];
            pos[val][0] = i; pos[val][1] = j;
        }
    }
    bool flg = solve();
    if (!flg) { printf("No Solution!\n"); return 0; }
    int zr, zc; // gather the required param... for decode() func
    for (int k = 0; k < path_cnt; ++k) {
        decode(path[k], &zr, &zc);
        printf("[step %d]\n", k+1);
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) 
                printf("%d ", board[i][j]);
            putchar('\n');
        }
        printf("---------\n");
    }
    return 0;
}