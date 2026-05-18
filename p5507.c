#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef long long ll;
#define MAXNODE 5000000
#define MAXSTEP 50
#define MAXCODE (1ll << 26)

#define swap(T, a, b) do { \
    T tmp = a; \
    a = b; \
    b = tmp; \
} while (0)

int init_sta[12], link[12][4];

ll encode(int sta[12]) 
{
    ll ret = 0;
    for (int i = 0; i < 12; ++i) 
        ret = ret * 4 + sta[i];
    return ret;
}

void decode(ll code, int sta[12]) 
{
    for (int i = 11; i >= 0; --i) {
        sta[i] = code % 4;
        code /= 4;
    }
}

typedef struct node {
    ll code;
    int op;
    int f, g, h;
    int prev_idx;
} Node;

Node *node_pool[MAXNODE];
int pool_tp = 0;

int create_node(ll c, int op, int f, int g, int h, int p) 
{
    Node *node = (Node *)malloc(sizeof(Node));
    if (!node) exit(1);
    node->code = c;
    node->op = op;
    node->f = f, node->g = g, node->h = h;
    node->prev_idx = p;
    node_pool[pool_tp] = node;
    return pool_tp++;
}

void cleanup() 
{
    for (int i = 0; i < pool_tp; ++i) 
        free(node_pool[i]);
}

typedef struct heap {
    int idx_arr[MAXNODE];
    int heap_tp;
} MinHeap;

static inline void init_heap(MinHeap *pq) { pq->heap_tp = 0; }

void push(MinHeap *pq, int node_idx) 
{
    int cur = pq->heap_tp;
    pq->idx_arr[pq->heap_tp++] = node_idx;
    while (cur > 0 && node_pool[pq->idx_arr[cur]]->f 
    < node_pool[pq->idx_arr[(cur - 1) / 2]]->f) {
        swap(int, pq->idx_arr[cur], pq->idx_arr[(cur - 1) / 2]);
        cur = (cur - 1) / 2;
    }
}

int pop(MinHeap *pq) 
{
    int ret_idx = pq->idx_arr[0];
    pq->idx_arr[0] = pq->idx_arr[--pq->heap_tp];
    int cur = 0;
    while (1) {
        int small = cur;
        int l = cur * 2 + 1, r = cur * 2 + 2;
        if (l < pq->heap_tp && node_pool[pq->idx_arr[l]]->f < node_pool[pq->idx_arr[small]]->f) 
            small = l;
        if (r < pq->heap_tp && node_pool[pq->idx_arr[r]]->f < node_pool[pq->idx_arr[small]]->f) 
            small = r;
        if (small == cur) 
            break;
        swap(int, pq->idx_arr[cur], pq->idx_arr[small]);
        cur = small;
    }
    return ret_idx;
}

static inline bool is_empty(MinHeap *pq) { return pq->heap_tp == 0; }

int best_g[MAXCODE + 10];
MinHeap open_set;

int heuristic(int sta[12]) 
{
    int cnt = 0;
    for (int i = 0; i < 12; ++i) {
        if (sta[i]) 
            cnt += (4 - sta[i]);
    }
    return cnt / 2;
}

bool check(int sta[12]) 
{
    for (int i = 0; i < 12; ++i) 
        if (sta[i] != 0) return false;
    return true;
} 

int path[MAXSTEP], path_tp = 0;

int solve() 
{
    memset(best_g, 0x3f, sizeof(best_g));
    init_heap(&open_set);
    ll init_code = encode(init_sta);
    int h = heuristic(init_sta);
    int init_id = create_node(init_code, -1, h, 0, h, -1);
    best_g[init_code] = 0;
    push(&open_set, init_id);
    
    while (!is_empty(&open_set)) {
        int cur_id = pop(&open_set);
        Node *cur_node = node_pool[cur_id];
        ll cur_code = cur_node->code;
        int cur_g = cur_node->g;

        if (cur_g > best_g[cur_code]) 
            continue;

        int cur_sta[12], cpy[12];
        decode(cur_code, cur_sta);
        
        if (check(cur_sta)) {
            int track = cur_id;
            while (track != init_id) {
                path[path_tp++] = node_pool[track]->op;
                track = node_pool[track]->prev_idx;
            }
            for (int i = 0; i < path_tp / 2; ++i) 
                swap(int, path[i], path[path_tp - 1 - i]);
            cleanup();
            return cur_g;
        }

        memcpy(cpy, cur_sta, sizeof(cur_sta));
        for (int i = 0; i < 12; ++i) {
            int nxt = link[i][cur_sta[i]];
            cur_sta[i] = (cur_sta[i] + 1) % 4;
            cur_sta[nxt] = (cur_sta[nxt] + 1) % 4;
            ll new_code = encode(cur_sta);
            int new_g = cur_g + 1;
            int new_h = heuristic(cur_sta);
            if (new_g < best_g[new_code]) {
                int new_id = create_node(new_code, i, new_g + new_h, new_g, new_h, cur_id);
                push(&open_set, new_id);
                best_g[new_code] = new_g;
            }
            memcpy(cur_sta, cpy, sizeof(cpy));
        }
    }
    cleanup();
    return -1;
}

int main() 
{
    for (int i = 0; i < 12; ++i) {
        scanf(" %d", &init_sta[i]);
        --init_sta[i];
        for (int j = 0; j < 4; ++j) {
            scanf(" %d", &link[i][j]);
            --link[i][j];
        }
    }

    int ans = solve();
    printf("%d\n", ans);
    for (int i = 0; i < path_tp; ++i) 
        printf("%d ", path[i] + 1);
    printf("\n");

    return 0;
}