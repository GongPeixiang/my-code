#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// multi-platform
#ifdef _WIN32
    #include <windows.h>
    #define SLEEP_MS(ms) Sleep(ms)
#else
    #include <unistd.h>
    #define SLEEP_MS(ms) usleep((ms) * 1000)
#endif

// it can be proved that an answer always exists
// the heuristic function does not guarantee consistency

#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define UNDERLINE "\033[4m"
#define BLINK   "\033[5m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

#define PATH_SIZE 55
#define MAX_NODES 100000
#define HEAP_SIZE 150000
#define HASH_TAB_SIZE 8191 // 2 ^ 13 - 1
#define HASH_NUM 0x9e3779b9ull

typedef unsigned long long ull;

const int directions[4][2] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

#define swap(T, a, b) do { \
    T tmp = a; \
    a = b; \
    b = tmp; \
} while (0)

/*-------------------------------------------------------------------*/
// board related
typedef struct point {
    int r, c;
} Point;

ull encode(int board[3][3])
{
    ull code = 0;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            code = code * 9 + board[i][j];
        }
    }
    return code;
}

Point decode(ull code, int board[3][3])
{
    int zr, zc;
    for (int i = 2; i >= 0; --i) {
        for (int j = 2; j >= 0; --j) {
            board[i][j] = (int)(code % 9);
            if (!board[i][j]) {
                zr = i;
                zc = j;
            }
            code /= 9;
        }
    }
    Point zero_pos = {zr, zc};
    return zero_pos;
}

int heuristic(int board[3][3])
{
    int cnt = 0;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
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

static inline bool judge(int board[3][3])
{
    return board[0][0] == 8 && board[0][1] == 1 && board[0][2] == 7;
}

/*-------------------------------------------------------------------*/
// node and pool
typedef struct node {
    ull code;
    int g, h, f;
    int prev_idx;
} Node;

typedef struct node_pool {
    Node *nodes[MAX_NODES];
    int node_cnt;
} NodePool;

void init_node_pool(NodePool *pool)
{
    for (int i = 0; i < MAX_NODES; ++i)
        pool->nodes[i] = NULL;
    pool->node_cnt = 0;
}

Node *get_node(NodePool *pool, int node_idx)
{
    if (node_idx >= pool->node_cnt) {
        printf("this node does not exist\n");
        return NULL;
    }
    return pool->nodes[node_idx];
}

int create_node(NodePool *pool, ull code, int g, int h, int prev_idx)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
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

void clear_nodes(NodePool *pool)
{
    for (int i = 0; i < pool->node_cnt; ++i) {
        free(pool->nodes[i]);
    }
    pool->node_cnt = 0;
}

/*-------------------------------------------------------------------*/
// heap and prority queue
typedef struct minheap {
    int node_id[HEAP_SIZE];
    int idx;
} MinHeap;

static inline void init_heap(MinHeap *pq) { pq->idx = 0; }

void heap_push(MinHeap *pq, NodePool *pool, int node_idx)
{
    int cur = pq->idx;
    pq->node_id[pq->idx++] = node_idx;
    while (cur > 0 && pool->nodes[pq->node_id[cur]]->f
        < pool->nodes[pq->node_id[(cur - 1) / 2]]->f) {
        swap(int, pq->node_id[cur], pq->node_id[(cur - 1) / 2]);
        cur = (cur - 1) / 2;
    }
}

int heap_pop(MinHeap *pq, NodePool *pool)
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
        swap(int, pq->node_id[cur], pq->node_id[smallest]);
        cur = smallest;
    }
    return ret;
}

static inline bool heap_empty(MinHeap *pq) { return pq->idx == 0; }

/*-------------------------------------------------------------------*/
// hash table
typedef struct hashnode {
    ull code;
    int g;
    struct hashnode *next;
} HashNode;

void init_hash_tab(HashNode *hash_tab[])
{
    for (int i = 0; i < HASH_TAB_SIZE; ++i)
        hash_tab[i] = NULL;
}

static inline int hash(ull key) { return (key * HASH_NUM) % HASH_TAB_SIZE; }

bool hash_tab_contains(HashNode *hash_tab[], ull code)
{
    int hash_val = hash(code);
    for (HashNode *hn = hash_tab[hash_val]; hn != NULL; hn = hn->next) {
        if (hn->code == code)
            return true;
    }
    return false;
}

bool hash_tab_insert(HashNode *hash_tab[], ull code, int g)
{
    int hash_val = hash(code);
    HashNode *hn = (HashNode *)malloc(sizeof(HashNode));
    if (!hn)
        return false;
    hn->code = code;
    hn->g = g;
    hn->next = hash_tab[hash_val];
    hash_tab[hash_val] = hn;
    return true;
}

int hash_tab_get(HashNode *hash_tab[], ull code)
{
    int hash_val = hash(code);
    for (HashNode *hn = hash_tab[hash_val]; hn != NULL; hn = hn->next) {
        if (hn->code == code)
            return hn->g;
    }
    return 1e7;
}

void hash_tab_replace(HashNode *hash_tab[], ull code, int g)
{
    int hash_val = hash(code);
    for (HashNode *hn = hash_tab[hash_val]; hn != NULL; hn = hn->next) {
        if (hn->code == code) {
            hn->g = g;
            return;
        }
    }
}

void clear_hash_tab(HashNode *hash_tab[])
{
    for (int i = 0; i < HASH_TAB_SIZE; ++i) {
        HashNode *hn = hash_tab[i];
        while (hn != NULL) {
            HashNode *tmp = hn;
            hn = hn->next;
            free(tmp);
        }
        hash_tab[i] = NULL;
    }
}

/*-------------------------------------------------------------------*/
// path process
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
        swap(ull, p->path[i], p->path[cnt - 1 - i]);
    }
}

/*-------------------------------------------------------------------*/
// helper functions
void clear_screen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void print_border(const char *title)
{
    printf(CYAN "╔");
    for(int i = 0; i < 58; ++i)
        printf("═");
    printf("╗\n");
    printf("║" BOLD WHITE " %-56s " RESET CYAN "║\n", title);
    printf("╠");
    for(int i = 0; i < 58; ++i)
        printf("═");
    printf("╣\n" RESET);
}

void print_board(int board[3][3])
{
    printf("\n");
    for (int i = 0; i < 3; ++i) {
        printf("  ");
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == 0)
                printf(GREEN "┌───┐" RESET);
            else
                printf("┌───┐");
        }
        printf("\n  ");

        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == 0)
                printf(GREEN "│   │" RESET);
            else if (board[i][j] == 8 || board[i][j] == 1 || board[i][j] == 7)
                printf(YELLOW "│ %d │" RESET, board[i][j]);
            else
                printf("│ %d │", board[i][j]);
        }
        printf("\n  ");

        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == 0)
                printf(GREEN "└───┘" RESET);
            else
                printf("└───┘");
        }
        printf("\n");
    }
    printf("\n");
}

void print_input_prompt()
{
    printf(YELLOW "\n输入说明:\n" RESET);
    printf("  请按行输入 9 个数字 (0-8), 0 代表空格\n");
    printf("  例如:\n");
    printf("  2 1 3\n");
    printf("  8 0 7\n");
    printf("  4 5 6\n\n");
}

bool validate_input(int board[3][3])
{
    int count[9] = {0};
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            int num = board[i][j];
            if (num < 0 || num > 8) {
                printf(RED "错误: 数字必须在 0-8 之间！\n" RESET);
                return false;
            }
            count[num]++;
        }
    }

    for (int i = 0; i < 9; ++i) {
        if (count[i] != 1) {
            printf(RED "错误: 数字 %d 必须出现且仅出现一次！\n" RESET, i);
            return false;
        }
    }
    return true;
}

/*-------------------------------------------------------------------*/
// game main loop
void game()
{
    clear_screen();
    print_border("一个特别的八数码游戏");

    int init_board[3][3];

    print_input_prompt();
    printf(CYAN "请输入您的初始棋盘:\n" RESET);
    printf("(输入 9 个数字，空格分隔，每行 3 个)\n\n");

    bool valid = false;
    while (!valid) {
        for (int i = 0; i < 3; ++i) {
            printf("第 %d 行: ", i + 1);
            for (int j = 0; j < 3; ++j) {
                scanf("%d", &init_board[i][j]);
            }
        }
        valid = validate_input(init_board);
        if (!valid) {
            printf(RED "\n输入无效, 请重新输入! \n\n" RESET);
        }
    }

    printf(GREEN "\n✓ 输入成功！正在计算最优解...\n" RESET);
    SLEEP_MS(500);

    NodePool all_nodes;
    MinHeap open_set;
    HashNode *best_g[HASH_TAB_SIZE];
    path_t final_path = { .path_cnt = 0 };

    init_node_pool(&all_nodes);
    init_heap(&open_set);
    init_hash_tab(best_g);

    ull init_code = encode(init_board);
    int init_h = heuristic(init_board);
    int init_id = create_node(&all_nodes, init_code, 0, init_h, -1);
    heap_push(&open_set, &all_nodes, init_id);

    int board[3][3];

    while (!heap_empty(&open_set)) {
        int cur_id = heap_pop(&open_set, &all_nodes);
        Node *cur_node = get_node(&all_nodes, cur_id);
        ull cur_code = cur_node->code;
        int cur_g = cur_node->g;

        if (hash_tab_get(best_g, cur_code) < cur_g)
            continue;

        Point z_pos = decode(cur_code, board);
        int zr = z_pos.r, zc = z_pos.c;

        if (judge(board)) {
            int track_id = cur_id;
            Node *tmp;
            while (track_id != init_id) {
                tmp = get_node(&all_nodes, track_id);
                path_push(&final_path, tmp->code);
                track_id = tmp->prev_idx;
            }
            path_reverse(&final_path);
            break;
        }

        for (int i = 0; i < 4; ++i) {
            int nr = zr + directions[i][0], nc = zc + directions[i][1];
            if (nr < 0 || nr >= 3 || nc < 0 || nc >= 3)
                continue;

            swap(int, board[zr][zc], board[nr][nc]);
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
            swap(int, board[zr][zc], board[nr][nc]);
        }
    }

    clear_screen();
    print_border("求解结果");

    printf(GREEN BOLD "\n✨ 找到解决方案！✨\n" RESET);
    printf(CYAN "总共需要 " YELLOW BOLD "%d" CYAN " 步\n\n" RESET, final_path.path_cnt);

    printf(UNDERLINE "路径演示:\n\n" RESET);
    SLEEP_MS(1000);

    for (int i = 0; i < final_path.path_cnt; ++i) {
        printf(CYAN "╔══════════════════════════════════════════════════════════╗\n");
        printf("║  " BOLD "第 %3d 步" RESET CYAN "                              ║\n", i + 1);
        printf("╚══════════════════════════════════════════════════════════╝\n" RESET);
        decode(final_path.path[i], board);
        print_board(board);
        printf("────────────────────────────────────────────────────────────\n");
        SLEEP_MS(500);
    }

    printf("\n");
    printf(BLINK);
    SLEEP_MS(200);
    printf(BOLD RED "\n★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★\n");
    printf("★                                            ★\n");
    printf("★  " MAGENTA "8  1  7" RED "  -  你的生日！        " RED "★\n");
    printf("★  " YELLOW "第一行 8.17, 祝你生日快乐！" RED "           ★\n");
    printf("★                                            ★\n");
    printf("★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★\n" RESET);
    SLEEP_MS(500);

    printf(BOLD GREEN "\n✨ 恭喜你找到了隐藏的惊喜！✨\n\n" RESET);
    getchar();

    clear_nodes(&all_nodes);
    clear_hash_tab(best_g);

    printf("\n" CYAN "按任意键返回主菜单..." RESET);
    getchar();
}

/*-------------------------------------------------------------------*/
// helping docs
void show_help()
{
    clear_screen();
    print_border("帮助文档");

    printf(CYAN "\n【游戏介绍】\n" RESET);
    printf("  这是一个特殊的八数码游戏，目标是拼出特定的图案。\n\n");

    printf(CYAN "【目标状态】\n" RESET);
    int target[3][3] = {{8, 1, 7}, {0, 0, 0}, {0, 0, 0}};
    print_board(target);

    printf(CYAN "【游戏规则】\n" RESET);
    printf("  • 通过移动数字块（与空格交换位置）来重组棋盘\n");
    printf("  • 最终将棋盘变成目标状态\n");
    printf("  • 程序会自动寻找最优解并演示移动步骤\n\n");

    printf(CYAN "【操作说明】\n" RESET);
    printf("  • 输入初始棋盘时, 每行输入3个数字 (0-8) \n");
    printf("  • 0 代表空格位置\n");
    printf("  • 程序会验证输入是否有效\n\n");

    printf(YELLOW "【特殊提示】\n" RESET);
    printf("  完成游戏后会有惊喜哦！🎁\n\n");

    printf(CYAN "按任意键返回主菜单...\n" RESET);
    getchar();
}

/*-------------------------------------------------------------------*/
// title
void show_title() 
{
    clear_screen();
    printf(CYAN "\n");
    printf("╔══════════════════════════════════════════════════════════╗\n");
    printf("║" BOLD MAGENTA "                                                          " CYAN "║\n");
    printf("║" BOLD MAGENTA "       █████╗     ██████╗  ██╗ ███████╗ ████████╗         " CYAN "║\n");
    printf("║" BOLD MAGENTA "      ██╔══██╗   ██╔════╝  ██║ ██╔════╝ ╚══██╔══╝         " CYAN "║\n");
    printf("║" BOLD MAGENTA "      ███████║   ██║  ███╗ ██║ █████╗      ██║            " CYAN "║\n");
    printf("║" BOLD MAGENTA "      ██╔══██║   ██║   ██║ ██║ ██╔══╝      ██║            " CYAN "║\n");
    printf("║" BOLD MAGENTA "      ██║  ██║   ╚██████╔╝ ██║ ██║         ██║            " CYAN "║\n");
    printf("║" BOLD MAGENTA "      ╚═╝  ╚═╝    ╚═════╝  ╚═╝ ╚═╝         ╚═╝            " CYAN "║\n");
    printf("║" BOLD MAGENTA "                                                          " CYAN "║\n");
    printf("║" BOLD YELLOW "                                                          " CYAN "║\n");
    printf("║" BOLD YELLOW "       ███████╗ ██████╗ ██████╗                           " CYAN "║\n");
    printf("║" BOLD YELLOW "       ██╔════╝██╔═══██╗██╔══██╗                          " CYAN "║\n");
    printf("║" BOLD YELLOW "       █████╗  ██║   ██║██████╔╝                          " CYAN "║\n");
    printf("║" BOLD YELLOW "       ██╔══╝  ██║   ██║██╔══██╗                          " CYAN "║\n");
    printf("║" BOLD YELLOW "       ██║     ╚██████╔╝██║  ██║                          " CYAN "║\n");
    printf("║" BOLD YELLOW "       ╚═╝      ╚═════╝ ╚═╝  ╚═╝                          " CYAN "║\n");
    printf("║" BOLD YELLOW "                                                          " CYAN "║\n");
    printf("║" BOLD YELLOW "       ██╗   ██╗ ██████╗ ██╗   ██╗                        " CYAN "║\n");
    printf("║" BOLD YELLOW "       ╚██╗ ██╔╝██╔═══██╗██║   ██║                        " CYAN "║\n");
    printf("║" BOLD YELLOW "        ╚████╔╝ ██║   ██║██║   ██║                        " CYAN "║\n");
    printf("║" BOLD YELLOW "         ╚██╔╝  ██║   ██║██║   ██║                        " CYAN "║\n");
    printf("║" BOLD YELLOW "          ██║   ╚██████╔╝╚██████╔╝                        " CYAN "║\n");
    printf("║" BOLD YELLOW "          ╚═╝    ╚═════╝  ╚═════╝                         " CYAN "║\n");
    printf("║" BOLD YELLOW "                                                          " CYAN "║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n" RESET);
    
    printf(CYAN "\n");
    printf("╔══════════════════════════════════════════════════════════╗\n");
    printf("║" BOLD WHITE "                    八数码 · 生日密码                     " CYAN "║\n");
    printf("║" WHITE "                 寻找隐藏在数字中的惊喜                   " CYAN "║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n" RESET);
    
    printf("\n\n");
    printf("     " GREEN "●" CYAN " 按 " BOLD YELLOW "P" CYAN " 开始游戏\n");
    printf("     " GREEN "●" CYAN " 按 " BOLD YELLOW "H" CYAN " 查看帮助\n");
    printf("     " GREEN "●" CYAN " 按 " BOLD YELLOW "Q" CYAN " 退出程序\n");
    printf("\n");
    printf("     " CYAN "──────────────────────────────────────────\n" RESET);
}

/*-------------------------------------------------------------------*/
/* main function */
int main()
{
    char c;

#ifdef _WIN32
    system("chcp 65001 > nul");
#endif

    while(1) {
        show_title();
        printf("\n  " BOLD CYAN "请选择操作: " RESET);
        c = getchar();
        getchar();
        switch(c) {
            case 'p':
            case 'P':
                game();
                break;
            case 'h':
            case 'H':
                show_help();
                break;
            case 'q':
            case 'Q':
                clear_screen();
                printf(GREEN "\n");
                printf("╔════════════════════════════════════════════╗\n");
                printf("║                                            ║\n");
                printf("║      " BOLD "感谢使用，再见！" RESET GREEN "               ║\n");
                printf("║                                            ║\n");
                printf("╚════════════════════════════════════════════╝\n" RESET);
                printf("\n");
#ifdef _WIN32
                system("pause");
#endif
                return 0;

           default:
                printf(RED "\n无效输入, 请按 P、H 或 Q! \n" RESET);
                SLEEP_MS(1000);
                break;
        }
    }

    return 0;
}
