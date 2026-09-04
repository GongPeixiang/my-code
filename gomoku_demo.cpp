/* 很简陋的五子棋对抗程序 */
#include <bits/stdc++.h>
using namespace std;

typedef uint64_t ull;

// -1 for empty, 0 for black, 1 for white
const int INF = 0X3f3f3f3f, MAXDEP = 5;
const int dx[4] = {1, 1, 1, 0}, dy[4] = {-1, 0, 1, 1};

int board[15][15], none[15][15], mycolor, usrcolor, maxdep;
ull seed=0, cur_hash = 0, zob[15][15][2];
clock_t start;
int nodecnt = 0;

inline ull random_ull() { // xorsft
    ull x = seed;
    x ^= x << 13;
    x ^= x >> 7;
    x ^= x << 17;
    return seed = x;
}

void init_zob() {
    seed = (ull)time(NULL) ^ (ull)clock() ^ (ull)&seed;
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            for (int k = 0; k < 2; k++) zob[i][j][k] = random_ull();
            if (~board[i][j]) {
                int c = board[i][j];
                cur_hash ^= zob[i][j][c];
            }
        }
    }
}

struct TT {
    static const int TABSIZE = 1 << 20;

    int gen;
    struct Entry {
        ull hash;
        int dep;
        int score, flg; // 0:precise, 1:lower-limit, 2:upper-limit
        int age;
    } tab[TABSIZE];

    inline void init() { 
        gen = 0; 
        memset(tab, 0, sizeof(tab));
    }
    inline void newGen() { gen++; }

    inline void save(ull hash, int dep, int score, int flg) {
        int id = (int)(hash & (TABSIZE - 1));
        tab[id] = (Entry){hash, dep, score, flg, gen};
    }

    bool lookup(ull hash, int dep, int alpha, int beta, int& score) {
        int id = (int)(hash & (TABSIZE - 1));
        Entry& entry = tab[id];
        if (entry.hash!=hash || entry.dep<dep || entry.age!=gen) return false;
        bool ok = false;
        if (entry.flg == 0) ok = true;
        else if (entry.flg == 1 && entry.score >= beta) ok = true;
        else if (entry.flg == 2 && entry.score <= alpha) ok = true;
        if (ok) {
            score = entry.score;
            return true;
        }
        return false;
    }
} tt;

bool is_full() {
    int epcnt = 0;
    for (int i = 0; i < 15; i++) 
        for (int j = 0; j < 15; j++) 
            if (board[i][j]==-1) epcnt++;
    return epcnt == 0;
}

inline bool time_exceed() {
    if (++nodecnt & 0x3FF) return false;
    clock_t now = clock();
    double pass = (double)(now-start)/CLOCKS_PER_SEC;
    return pass >= 0.95;
}

// TODO: at least reach amateur level
int eval() {
    int score = 0;
    for (int x = 0; x < 15; x++) {
        for (int y = 0; y < 15; y++) {
            if (board[x][y] == -1) continue;
            int color = board[x][y];
            int sign = (color == mycolor) ? 1 : -1;
            for (int d = 0; d < 4; d++) {
                int cnt = 1, empty = 0, blocked = 0;
                for (int i = 1; i < 5; i++) { // 正方向
                    int nx = x + dx[d]*i, ny = y + dy[d]*i;
                    if (nx < 0 || nx >= 15 || ny < 0 || ny >= 15) { blocked++; break; }
                    if (board[nx][ny] == color) cnt++;
                    else if (board[nx][ny] == -1) { empty++; break; }
                    else { blocked++; break; }
                }
                for (int i = 1; i < 5; i++) { // 负方向
                    int nx = x - dx[d]*i, ny = y - dy[d]*i;
                    if (nx < 0 || nx >= 15 || ny < 0 || ny >= 15) { blocked++; break; }
                    if (board[nx][ny] == color) cnt++;
                    else if (board[nx][ny] == -1) { empty++; break; }
                    else { blocked++; break; }
                }
                if (cnt >= 5) return sign * INF;
                // 根据连子数和开放情况打分
                if (cnt == 4 && empty > 0) score += sign * (empty >= 2 ? 50000 : 3000);
                else if (cnt == 3 && empty > 0) score += sign * (empty >= 2 ? 3000 : 500);
                else if (cnt == 2 && empty > 0) score += sign * (empty >= 2 ? 300 : 50);
                else if (cnt == 1 && empty > 0) score += sign * 10;
            }
        }
    }
    return score;
}

vector<int> get_moves(int color) {
    vector<int> movs;
    int has_stone = memcmp(board, none, sizeof(none));
    if (has_stone) {
        for (int x = 0; x < 15; x++) 
            for (int y = 0; y < 15; y++) {
                if (!(~board[x][y])) continue;
                for (int d = 0; d < 4; d++) {
                    for (int s = -2; s <= 2; s++) {
                        int nx = x + dx[d] * s, ny = y + dy[d] * s;
                        if (nx < 0 || nx >= 15 || ny < 0 || ny >= 15) continue;
                        if (~board[nx][ny]) continue;
                        movs.push_back(nx * 15 + ny);
                    }
                }
            }
        sort(movs.begin(), movs.end());
        movs.erase(unique(movs.begin(), movs.end()), movs.end());
        vector<pair<int,int>> scored_moves;
        for (int mov : movs) {
            int x = mov / 15, y = mov % 15;
            board[x][y] = color;
            int score = eval();
            board[x][y] = -1;
            scored_moves.push_back({score, mov});
        }
        if (color == mycolor) {
            sort(scored_moves.begin(), scored_moves.end(),
                 [](const pair<int,int>& a, const pair<int,int>& b) {
                     return a.first > b.first;
                 });
        } else {
            sort(scored_moves.begin(), scored_moves.end(),
                 [](const pair<int,int>& a, const pair<int,int>& b) {
                     return a.first < b.first;
                 });
        }
        movs.clear();
        int limit = min((int)scored_moves.size(), 30);
        for (int i = 0; i < limit; i++) 
            movs.push_back(scored_moves[i].second);
    } else movs.push_back(7 * 15 + 7);
    return move(movs);
}

int minimax(int dep, int alpha, int beta, bool is_max) {
    nodecnt++;
    if (time_exceed()) return eval();
    int tt_score;
    if (tt.lookup(cur_hash, dep, alpha, beta, tt_score)) return tt_score;
    if (dep == maxdep) {
        int score = eval();
        tt.save(cur_hash, dep, score, 0);
        return score;
    }
    int color = is_max ? mycolor : usrcolor;
    int maxs = -INF, mins = INF;
    vector<int> movs = get_moves(color);
    if (movs.empty()) return eval();
    for (int mov: movs) {
        int x = mov / 15, y = mov % 15;
        board[x][y] = color;
        cur_hash ^= zob[x][y][color];
        int score = minimax(dep + 1, alpha, beta, !is_max);
        cur_hash ^= zob[x][y][color];
        board[x][y] = -1;
        if (is_max) {
            maxs = max(score, maxs);
            alpha = max(maxs, alpha);
            if (alpha >= beta) {
                tt.save(cur_hash, dep, alpha, 2);
                return alpha;
            }
        } else {
            mins = min(score, mins);
            beta = min(mins, beta);
            if (beta <= alpha) {
                tt.save(cur_hash, dep, beta, 1);
                return beta;
            }
        }
    }
    if (is_max) {
        tt.save(cur_hash, dep, maxs, 0);
        return maxs;
    } else {
        tt.save(cur_hash, dep, mins, 0);
        return mins;
    }
    return -1;
}

inline void gotoxy(int x, int y) {   
    printf("\033[%d;%dH", x + 1, y + 1);  // ANSI escape    
}

inline char sft(int c) {
    switch (c) {
        case -1: return ' ';
        case 0: return 'B';
        case 1: return 'W';
    }
    return ' ';
}

void display_board() {
    printf("\033[2J\033[H"); // clear the screen
    printf("    0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  \n");
    printf("  +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+\n");
    for (int i = 0; i < 15; i++) {
        printf("%2d|", i);
        for (int j = 0; j < 15; j++) printf(" %c |", sft(board[i][j]));
        printf("\n");
        printf("  +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+\n");
    }
}

void my_turn() {
    start = clock();
    nodecnt = 0;
    tt.newGen();
    vector<int> movs = get_moves(mycolor);
    int maxs = -INF, bestmov = -1;
    for (int mov: movs) {
        int x = mov / 15 , y = mov % 15;
        board[x][y] = mycolor;
        cur_hash ^= zob[x][y][mycolor];
        int score = minimax(0, -INF, INF, false);
        if (score > maxs) {
            maxs = score;
            bestmov = mov;
        }
        cur_hash ^= zob[x][y][mycolor];
        board[x][y] = -1;
    }
    int x = bestmov / 15, y = bestmov % 15;
    board[x][y] = mycolor;
    cur_hash ^= zob[x][y][mycolor];
    printf("AI moves at (%d, %d)", x, y);
    display_board();
}

void usr_turn() {
    printf("Now is your turn (enter row col): ");
    int r, c;
    scanf("%d%d", &r, &c);
    while (r < 0 || r >= 15 || c < 0 || c >= 15 || board[r][c] != -1) {
        gotoxy(0, 21);
        printf("Invalid move! Try again (row col): ");
        scanf("%d%d", &r, &c);
    }
    board[r][c] = usrcolor;
    cur_hash ^= zob[r][c][usrcolor];
    display_board();
}

bool check_end(bool *win, bool *loss, bool *full) {
    int score = eval();
    if (score == INF) { *win = true; *loss = false; return true; }
    if (score == -INF) { *win = false; *loss = true; return true; }
    if (is_full()) { *win = false; *loss = false; *full = true; return true; }
    return false;
}

int main() {
    memset(board, -1, sizeof(board));
    memset(none, -1, sizeof(none));
    init_zob();
    tt.init();
    printf("Select your color: (0 for 'B', 1 for 'W'): ");
    scanf("%d", &usrcolor);
    mycolor = 1 - usrcolor;
    printf("\nBoard display: W = %d, B = %d\n", 0, 1);
    printf("Rows and columns are 0-indexed (0-14).\n");
    printf("You are %c, AI is %c\n\n", sft(usrcolor), sft(mycolor));
    display_board();
    bool win = false, loss = false, full = false;
    while (!check_end(&win, &loss, &full)) {
        if (usrcolor == 0) {
            usr_turn();
            if (check_end(&win, &loss, &full)) break;
            my_turn();
        } else {
            my_turn();
            if (check_end(&win, &loss, &full)) break;
            usr_turn();
        }
    }
    putchar('\n');
    if (win)       printf("========== YOU LOSS ==========\n");
    else if (loss) printf("========== YOU WIN! ==========\n");
    else if (full) printf("============ DRAW ============\n");
    else printf("=== GAME DOESN'T END NORMALLY ===\n");
    system("pause");
    return 0;
}