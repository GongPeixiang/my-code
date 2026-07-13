#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef long long ll;
#define MAXC (1ll<<24)
#define MAXP 50

const int tgt[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

int board[12], cnnct[12][4];
struct Node {
    ll code; int op;
    int g, f;
} pq[MAXC], pre[MAXC];
int pq_cnt = 0, dist[MAXC], path[MAXP], path_cnt = 0;

#define swap(T, a, b) do { T tmp = a; a = b; b = tmp; } while(0)

inline static bool check() { return memcmp(board, tgt, sizeof(tgt)) == 0; }

ll encode() 
{
    ll res = 0;
    for (int i = 0; i < 12; ++i) res = res * 4 + board[i];
    return res;
}

void decode(ll code) 
{ for (int i = 11; i >= 0; --i) { board[i] = code % 4; code /= 4; } }

int h() 
{
    int cnt = 0;
    for (int i = 0; i < 12; ++i) 
        if (board[i]) cnt += 4 - board[i];
    return cnt / 2;
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
        int l = 2 * cur + 1, r = cur * 2 + 2;
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
    memset(pre, 0xff, sizeof(pre));
    ll init_code = encode();
    struct Node init = (struct Node){init_code, -1, 0, h()};
    pq_push(init);
    dist[init_code] = 0;
    pre[init_code] = (struct Node){-1, -1, -1, -1};
    while (pq_cnt != 0) {
        struct Node cur = pq_pop();
        ll code = cur.code; int g = cur.g;
        if (dist[code] < g) continue;
        decode(code);
        if (check()) {
            struct Node trk = cur;
            while (trk.code != init_code) {
                path[path_cnt++] = trk.op;
                trk = pre[trk.code];
            }
            for (int i = 0; i < path_cnt/2; ++i) 
                swap(int, path[i], path[path_cnt-1-i]);
            return true;
        }
        for (int i = 0; i < 12; ++i) {
            int nxt = cnnct[i][board[i]];
            board[i] = (board[i] + 1) % 4;
            board[nxt] = (board[nxt] + 1) % 4;
            ll ncode = encode();
            int ng = g + 1;
            if (dist[ncode] == -1 || ng < dist[ncode]) {
                dist[ncode] = ng;
                pre[ncode] = cur;
                struct Node nnode = (struct Node){ncode, i, ng, ng + h()};
                pq_push(nnode);
            }
            board[i] = (board[i] + 3) % 4;
            board[nxt] = (board[nxt] + 3) % 4;
        }
    }
    return false;
}

int main() 
{
    for (int i = 0; i < 12; ++i) {
        scanf("%d", &board[i]); --board[i];
        for (int j = 0; j < 4; ++j) 
        { scanf("%d", &cnnct[i][j]); --cnnct[i][j]; }
    }
    bool flg = solve();
    if (!flg) { printf("-1\n"); return 0; }
    printf("%d\n", path_cnt);
    for (int i = 0; i < path_cnt; ++i) 
        printf("%d%c", path[i]+1, " \n"[i == path_cnt-1]);
    return 0;
}