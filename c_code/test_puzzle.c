#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* it can be proved that an answer always exists */
/* the heuristic function does not guarantee consistency */

#define BOARD_SIZE 3
#define PATH_SIZE 55
#define MAX_NODES 100000
#define HEAP_SIZE 150000
#define HASH_TAB_SIZE 8191 /* 2 ^ 13 - 1 */
#define HASH_NUM 0x9e3779b9ull

typedef unsigned long long ull;

const int DIRECTIONS[4][2] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

#define SWAP(T, a, b) do { \
    T tmp = a; \
    a = b; \
    b = tmp; \
} while (0)

typedef struct point {
    int r, c;
} point_t;

ull encode(int board[][BOARD_SIZE]) 
{
    ull code = 0;
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            code = code * 9 + board[i][j];
        }
    }
    return code;
}

point_t decode(ull code, int board[][BOARD_SIZE]) 
{
    int zr, zc;
    for (int i = BOARD_SIZE - 1; i >= 0; --i) {
        for (int j = BOARD_SIZE - 1; j >= 0; --j) {
            board[i][j] = (int)(code % 9);
            if (!board[i][j]) {
                zr = i;
                zc = j;
            }
            code /= 9;
        }
    }
    point_t zero_pos = {zr, zc};
    return zero_pos;
}

int heuristic(int board[][BOARD_SIZE]) 
{
    int cnt = 0;
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            switch (board[i][j]) {
                case 8: cnt += abs(i) + abs(j); break;
                case 1: cnt += abs(i) + abs(j - 1); break;
                case 7: cnt += abs(i) + abs(j - 2); break;
                default: break;
            }
        }
    }
    return cnt;
}

static inline bool judge(int board[][BOARD_SIZE]) 
{
    return board[0][0] == 8 && board[0][1] == 1 && board[0][2] == 7;
}


typedef struct node {
    ull code;
    int g, h, f;
    int prev_idx;
} node_t;

typedef struct node_pool {
    node_t *nodes[MAX_NODES];
    int node_cnt;
} node_pool_t;

void init_node_pool(node_pool_t *pool) 
{
    for (int i = 0; i < MAX_NODES; ++i) 
        pool->nodes[i] = NULL;
    pool->node_cnt = 0;
}

node_t *get_node(node_pool_t *pool, int node_idx) 
{
    if (node_idx >= pool->node_cnt) {
        printf("this node does not exist\n");
        return NULL;
    }
    return pool->nodes[node_idx];
}

int create_node(node_pool_t *pool, ull code, int g, int h, int prev_idx) 
{
    node_t *new_node = malloc(sizeof(node_t));
    if (!new_node) {
        printf("memory allocation failure.\n");
        return -1;
    }
    new_node->code = code;
    new_node->g = g;
    new_node->h = h;
    new_node->f = g + h;
    new_node->prev_idx = prev_idx;
    pool->nodes[pool->node_cnt] = new_node;
    return pool->node_cnt++;
}

void clear_nodes(node_pool_t *pool) 
{
    for (int i = 0; i < pool->node_cnt; ++i) {
        free(pool->nodes[i]);
    }
    pool->node_cnt = 0;
}


typedef struct minheap {
    int node_id[HEAP_SIZE];
    int idx;
} minheap_t;

minheap_t open_set;

void init_heap(minheap_t *pq) 
{
    pq->idx = 0;
}

void heap_push(minheap_t *pq, node_pool_t *pool, int node_idx) 
{
    int cur = pq->idx;
    pq->node_id[pq->idx++] = node_idx;
    while (cur > 0 && pool->nodes[pq->node_id[cur]]->f 
        < pool->nodes[pq->node_id[(cur - 1) / 2]]->f) {
        SWAP(int, pq->node_id[cur], pq->node_id[(cur - 1) / 2]);
        cur = (cur - 1) / 2;
    }
}

int heap_pop(minheap_t *pq, node_pool_t *pool) 
{
    int ret = pq->node_id[0];
    pq->node_id[0] = pq->node_id[--pq->idx];
    int cur = 0;
    while (1) {
        int left = cur * 2 + 1;
        int right = cur * 2 + 2;
        int smallest = cur;
        if (left < pq->idx && pool->nodes[pq->node_id[left]]->f 
            < pool->nodes[pq->node_id[smallest]]->f)
            smallest = left;
        if (right < pq->idx && pool->nodes[pq->node_id[right]]->f 
            < pool->nodes[pq->node_id[smallest]]->f)
            smallest = right;
        if (smallest == cur) break;
        SWAP(int, pq->node_id[cur], pq->node_id[smallest]);
        cur = smallest;
    }
    return ret;
}

static inline bool heap_empty(minheap_t *pq) 
{ 
    return pq->idx == 0; 
}


typedef struct hashnode {
    ull code;
    int g;
    struct hashnode *next;
} hashnode_t;

void init_hash_tab(hashnode_t *hash_tab[]) 
{
    for (int i = 0; i < HASH_TAB_SIZE; ++i)
        hash_tab[i] = NULL;
}

static inline int hash(ull key) 
{
    return (key * HASH_NUM) % HASH_TAB_SIZE;
}

bool hash_tab_contains(hashnode_t *hash_tab[], ull code) 
{
    int hash_val = hash(code);
    for (hashnode_t *hn = hash_tab[hash_val]; hn != NULL; hn = hn->next) {
        if (hn->code == code) 
            return true;
    }
    return false;
}

int hash_tab_insert(hashnode_t *hash_tab[], ull code, int g) 
{
    int hash_val = hash(code);
    hashnode_t *hn = malloc(sizeof(hashnode_t));
    if (!hn) 
        return false;
    hn->code = code;
    hn->g = g;
    hn->next = hash_tab[hash_val];
    hash_tab[hash_val] = hn;
    return true;
}

int hash_tab_get(hashnode_t *hash_tab[], ull code) 
{
    int hash_val = hash(code);
    for (hashnode_t *hn = hash_tab[hash_val]; hn != NULL; hn = hn->next) {
        if (hn->code == code) 
            return hn->g;
    }
    return 1e7;
}

void hash_tab_replace(hashnode_t *hash_tab[], ull code, int g) 
{
    int hash_val = hash(code);
    for (hashnode_t *hn = hash_tab[hash_val]; hn != NULL; hn = hn->next) {
        if (hn->code == code) {
            hn->g = g;
            return;
        }
    }
}

void clear_hash_tab(hashnode_t *hash_tab[]) 
{
    for (int i = 0; i < HASH_TAB_SIZE; ++i) {
        hashnode_t *hn = hash_tab[i];
        while (hn != NULL) {
            hashnode_t *tmp = hn;
            hn = hn->next;
            free(tmp);
        }
        hash_tab[i] = NULL;
    }
}


typedef struct path {
    ull path[PATH_SIZE];
    int path_cnt;
} path_t;

static inline void path_push(path_t *p, ull code) 
{
    p->path[p->path_cnt++] = code;
}

void path_reverse(path_t *p) 
{
    int cnt = p->path_cnt;
    for (int i = 0; i < cnt / 2; ++i) {
        SWAP(ull, p->path[i], p->path[cnt - 1 - i]);
    }
}

node_pool_t all_nodes;
hashnode_t *best_g[HASH_TAB_SIZE];
path_t final_path;

int main() 
{
    int init_board[BOARD_SIZE][BOARD_SIZE];

    printf("Please enter your initial board:\n");
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            scanf(" %d", &init_board[i][j]);
        }
    }

    init_node_pool(&all_nodes);
    init_heap(&open_set);
    init_hash_tab(best_g);

    ull init_code = encode(init_board);
    int init_h = heuristic(init_board);
    int init_id = create_node(&all_nodes, init_code, 0, init_h, -1);
    heap_push(&open_set, &all_nodes, init_id);

    int board[BOARD_SIZE][BOARD_SIZE];

    while (!heap_empty(&open_set)) {
        int cur_id = heap_pop(&open_set, &all_nodes);
        node_t *cur_node = get_node(&all_nodes, cur_id);
        ull cur_code = cur_node->code;
        int cur_g = cur_node->g;

        if (hash_tab_get(best_g, cur_code) < cur_g) 
            continue;

        point_t z_pos = decode(cur_code, board);
        int zr = z_pos.r, zc = z_pos.c;

        if (judge(board)) {
            int track_id = cur_id;
            node_t *tmp;
            while (track_id != init_id) {
                tmp = get_node(&all_nodes, track_id);
                path_push(&final_path, tmp->code);
                track_id = tmp->prev_idx;
            }
            path_reverse(&final_path);
            break;
        }

        for (int i = 0; i < 4; ++i) {
            int nr = zr + DIRECTIONS[i][0], nc = zc + DIRECTIONS[i][1];
            if (nr < 0 || nr >= BOARD_SIZE || nc < 0 || nc >= BOARD_SIZE)
                continue;

            SWAP(int, board[zr][zc], board[nr][nc]);
            ull new_code = encode(board);
            int new_g = cur_g + 1;
            int new_h = heuristic(board);

            if (!hash_tab_contains(best_g, new_code) 
                || new_g < hash_tab_get(best_g, new_code)) {
                int new_id = create_node(&all_nodes, new_code, new_g, 
                    new_h, cur_id);
                heap_push(&open_set, &all_nodes, new_id);
                if (!hash_tab_contains(best_g, new_code))
                    hash_tab_insert(best_g, new_code, new_g);
                else
                    hash_tab_replace(best_g, new_code, new_g);
            }
            SWAP(int, board[zr][zc], board[nr][nc]);
        }
    }

    int steps = final_path.path_cnt;
    printf("%d steps, and here are the path:\n", steps);
    for (int i = 0; i < steps; ++i) {
        decode(final_path.path[i], board);
        printf("[step %d]\n", i + 1);
        for (int j = 0; j < BOARD_SIZE; ++j) {
            for (int k = 0; k < BOARD_SIZE; ++k)
                printf("%d ", board[j][k]);
            printf("\n");
        }
        printf("---------\n");
    }

    clear_nodes(&all_nodes);
    clear_hash_tab(best_g);

    return 0;
}
