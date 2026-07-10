#include <bits/stdc++.h>
using namespace std;

#ifdef _WIN32
    #include <windows.h>
    #define SLEEP_MS(ms) Sleep(ms)
#else
    #include <unistd.h>
    #define SLEEP_MS(ms) usleep((ms) * 1000)
#endif

// it can be proved that an answer always exists
// the heuristic function does not guarantee consistency

constexpr char RESET[10] = "\033[0m", BOLD[10] = "\033[1m", UNDERLINE[10] = "\033[4m", BLINK[10] = "\033[5m";
constexpr char RED[10] = "\033[31m", GREEN[10] = "\033[32m", YELLOW[10] = "\033[33m"; 
constexpr char MAGENTA[10] = "\033[35m", CYAN[10] = "\033[36m", WHITE[10] = "\033[37m";

constexpr int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, -1, 0, 1};
constexpr int fact[9] = {1,1,2,6,24,120,720,5040,40320}; 
constexpr int MAXS = 362880;

struct Node {
    int code;
    int g, f;
    bool operator<(const Node& other) const { return f > other.f; }
} pre[MAXS];
int best_g[MAXS];

int encode(int board[3][3]) { // cantor
    int code = 0, cnt = 0;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            int rk = 0;
            for (int r = i; r < 3; ++r) {
                for (int c = (r==i ? j+1:0); c < 3; ++c) 
                    if (board[r][c] < board[i][j]) ++rk;
            }
            code += rk * fact[8-cnt];
            ++cnt;
        }
    }
    return code;
}

pair<int, int> decode(int board[3][3], int code) {
    vector<int> nums;
    for (int i = 0; i < 9; ++i) nums.push_back(i);
    int zr, zc;
    for (int i = 0; i < 9; ++i) {
        int rk = code / fact[8 - i], val = nums[rk];
        code %= fact[8 - i];
        board[i/3][i%3] = val;
        if (val == 0) { zr = i / 3; zc = i % 3; }
        nums.erase(nums.begin() + rk);
    }
    return make_pair(zr, zc);
}

int h(int board[3][3]) {
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

inline bool judge(int board[3][3]) { 
    return board[0][0] == 8 && board[0][1] == 1 && board[0][2] == 7; 
}

void clr_screen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void print_border(const string& title) {
    cout << CYAN << "╔";
    for(int i = 0; i < 50; ++i) cout << "═";
    cout << "╗\n";
    cout << "║" << BOLD << GREEN << left << setw(45) << title << RESET << CYAN << "║\n╠";
    for(int i = 0; i < 50; ++i) cout << "═";
    cout << "╣\n" << RESET;
}

void print_board(int board[3][3]) {
    cout << '\n';
    for (int i = 0; i < 3; ++i) {
        cout << "  ";
        for (int j = 0; j < 3; ++j) {
            if (!board[i][j]) cout << GREEN << "╔═══╗" << RESET;
            else cout << "╔═══╗";
        }
        cout << "\n  ";
        for (int j = 0; j < 3; ++j) {
            if (!board[i][j]) cout << GREEN << "║   ║" << RESET;
            else if (board[i][j] == 8 || board[i][j] == 1 || board[i][j] == 7) 
                cout << YELLOW << "║ " << board[i][j] << " ║" << RESET;
            else cout << "║ " << board[i][j] << " ║";
        }
        cout << "\n  ";
        for (int j = 0; j < 3; ++j) {
            if (!board[i][j]) cout << GREEN << "╚═══╝" << RESET; 
            else cout << "╚═══╝";
        }
        cout << '\n';
    }
    cout << '\n';
}

void prompt() {
    cout << YELLOW << "\n输入说明:\n" << RESET; 
    cout << "  请按行输入 9 个数字 (0-8), 0 代表空格\n";
    cout << "  例如:\n";
    cout << "  2 1 3\n" << "  8 0 7\n" << "  4 5 6\n\n";
}

bool valid_input(int board[3][3]) {
    int cnt[9] = {0};
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            int num = board[i][j];
            if (num < 0 || num > 8) {
                cout << RED <<  "错误: 数字必须在 0-8 之间! \n" << RESET;
                return false;
            }
            ++cnt[num];
        }
    }
    for (int i = 0; i < 9; ++i) {
        if (cnt[i] != 1) {
            cout << RED <<  "错误: 数字 " << (i + 1) << " 必须出现且仅出现一次! \n" << RESET;
            return false;
        }
    }
    return true;
}

void game() {
    int board[3][3];
    clr_screen();
    print_border("一个特别的八数码游戏");
    prompt();
    cout << CYAN <<  "请输入您的初始棋盘:\n" << RESET;
    cout << "(输入 9 个数字，空格分隔，每行 3 个)\n\n";
    bool vld = false;
    while (!vld) {
        for (int i = 0; i < 3; ++i) {
            cout << "第 " << (i + 1) << " 行: ";
            for (int j = 0; j < 3; ++j) 
                cin >> board[i][j];
        }
        vld = valid_input(board);
        if (!vld) cout << RED <<  "\n输入无效, 请重新输入! \n\n" << RESET;
    }
    cout << GREEN << "\n√ 输入成功！正在计算最优解...\n" << RESET;
    SLEEP_MS(500);

    priority_queue<Node, vector<Node>> pq;
    memset(best_g, 0xff, sizeof(best_g));
    vector<int> path;

    int init_code = encode(board), init_h = h(board);
    pq.push(Node{init_code, 0, init_h});
    best_g[init_code] = 0; pre[init_code] = Node{-1, -1, -1};

    while (!pq.empty()) {
        Node cur = pq.top(); pq.pop();
        if (best_g[cur.code] < cur.g) continue;
        pair<int, int> zpos = decode(board, cur.code);
        int zr = zpos.first, zc = zpos.second;
        if (judge(board)) {
            Node trk = cur;
            while (trk.code != init_code) {
                path.push_back(trk.code);
                trk = pre[trk.code]; 
            }
            reverse(path.begin(), path.end());
            break;
        }
        for (int i = 0; i < 4; ++i) {
            int nr = zr + dx[i], nc = zc + dy[i];
            if (nr < 0 || nr >= 3 || nc < 0 || nc >= 3) continue;
            swap(board[zr][zc], board[nr][nc]);
            int ncode = encode(board), ng = cur.g + 1, nh = h(board);
            if (best_g[ncode] == -1 || ng < best_g[ncode]) {
                best_g[ncode] = ng;
                pre[ncode] = cur;
                pq.push(Node{ncode, ng, ng + nh});
            }
            swap(board[zr][zc], board[nr][nc]);
        }
    }

    clr_screen();
    print_border("求解结果");
    cout << GREEN << BOLD << "\n✨ 找到解决方案! ✨\n" << RESET;
    cout << CYAN << "总共需要 " << YELLOW << BOLD << path.size() << CYAN << " 步\n\n" << RESET;
    cout << UNDERLINE << "路径演示:\n\n" << RESET;
    SLEEP_MS(1000);
    for (size_t i = 0; i < path.size(); ++i) {
        cout << CYAN << "╔══════════════════════════════════════════════════════════╗\n";
        cout << "║  " << BOLD << "第 " << setw(3) << (i + 1) << " 步" << RESET << CYAN << "                              ║\n";
        cout << "╚══════════════════════════════════════════════════════════╝\n" << RESET;
        decode(board, path[i]);
        print_board(board);
        cout << "────────────────────────────────────────────────────────────\n";
        SLEEP_MS(1000);
    }
    cout << '\n';
    cout << BLINK;
    SLEEP_MS(200);
    cout << BOLD << RED << "\n★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★\n";
    cout << "★                                            ★\n";
    cout << "★  " << MAGENTA << "8  1  7" << RED << "  -  你的生日!        " << RED << "★\n";
    cout << "★  " << YELLOW << "第一行 8.17, 祝你生日快乐!" << RED << "           ★\n";
    cout << "★                                            ★\n";
    cout << "★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★\n" << RESET;
    SLEEP_MS(500);
    cout << BOLD << GREEN << "\n✨ 恭喜你找到了隐藏的惊喜! ✨\n\n" << RESET;
    cin.get();
    cout << "\n" << CYAN << "按任意键返回主菜单..." << RESET;
    cin.get();
}

void help() {
    clr_screen();
    print_border("帮助文档");
    cout << CYAN << "\n【游戏介绍】\n" << RESET;
    cout << "  这是一个特殊的八数码游戏, 目标是拼出特定的图案\n\n";
    cout << CYAN << "【目标状态】\n" << RESET;
    int target[3][3] = {{8, 1, 7}, {0, 0, 0}, {0, 0, 0}};
    print_board(target);
    cout << CYAN << "【游戏规则】\n" << RESET;
    cout << "  • 通过移动数字块(与空格交换位置)来重组棋盘\n";
    cout << "  • 最终将棋盘变成目标状态\n";
    cout << "  • 程序会自动寻找最优解并演示移动步骤\n\n";
    cout << CYAN << "【操作说明】\n" << RESET;
    cout << "  • 输入初始棋盘时, 每行输入3个数字 (0-8) \n";
    cout << "  • 0 代表空格位置\n";
    cout << "  • 程序会验证输入是否有效\n\n";
    cout << YELLOW << "【特殊提示】\n" << RESET;
    cout << "  完成游戏后会有惊喜哦! 🎁\n\n";
    cout << CYAN << "按任意键返回主菜单...\n" << RESET;
    cin.get();
}

void show_title() 
{
    clr_screen();
    cout << CYAN << '\n';
    cout << "╔══════════════════════════════════════════════════════════╗\n";
    cout << "║" << BOLD << MAGENTA << "                                                          " << CYAN << "║\n";
    cout << "║" << BOLD << MAGENTA << "       █████╗     ██████╗  ██╗ ███████╗ ████████╗         " << CYAN << "║\n";
    cout << "║" << BOLD << MAGENTA << "      ██╔══██╗   ██╔════╝  ██║ ██╔════╝ ╚══██╔══╝         " << CYAN << "║\n";
    cout << "║" << BOLD << MAGENTA << "      ███████║   ██║  ███╗ ██║ █████╗      ██║            " << CYAN << "║\n";
    cout << "║" << BOLD << MAGENTA << "      ██╔══██║   ██║   ██║ ██║ ██╔══╝      ██║            " << CYAN << "║\n";
    cout << "║" << BOLD << MAGENTA << "      ██║  ██║   ╚██████╔╝ ██║ ██║         ██║            " << CYAN << "║\n";
    cout << "║" << BOLD << MAGENTA << "      ╚═╝  ╚═╝    ╚═════╝  ╚═╝ ╚═╝         ╚═╝            " << CYAN << "║\n";
    cout << "║" << BOLD << MAGENTA << "                                                          " << CYAN << "║\n";
    cout << "║" << BOLD << YELLOW << "                                                          " << CYAN << "║\n";
    cout << "║" << BOLD << YELLOW << "       ███████╗ ██████╗ ██████╗                           " << CYAN << "║\n";
    cout << "║" << BOLD << YELLOW << "       ██╔════╝██╔═══██╗██╔══██╗                          " << CYAN << "║\n";
    cout << "║" << BOLD << YELLOW << "       █████╗  ██║   ██║██████╔╝                          " << CYAN << "║\n";
    cout << "║" << BOLD << YELLOW << "       ██╔══╝  ██║   ██║██╔══██╗                          " << CYAN << "║\n";
    cout << "║" << BOLD << YELLOW << "       ██║     ╚██████╔╝██║  ██║                          " << CYAN << "║\n";
    cout << "║" << BOLD << YELLOW << "       ╚═╝      ╚═════╝ ╚═╝  ╚═╝                          " << CYAN << "║\n";
    cout << "║" << BOLD << YELLOW << "                                                          " << CYAN << "║\n";
    cout << "║" << BOLD << YELLOW << "       ██╗   ██╗ ██████╗ ██╗   ██╗                        " << CYAN << "║\n";
    cout << "║" << BOLD << YELLOW << "       ╚██╗ ██╔╝██╔═══██╗██║   ██║                        " << CYAN << "║\n";
    cout << "║" << BOLD << YELLOW << "        ╚████╔╝ ██║   ██║██║   ██║                        " << CYAN << "║\n";
    cout << "║" << BOLD << YELLOW << "         ╚██╔╝  ██║   ██║██║   ██║                        " << CYAN << "║\n";
    cout << "║" << BOLD << YELLOW << "          ██║   ╚██████╔╝╚██████╔╝                        " << CYAN << "║\n";
    cout << "║" << BOLD << YELLOW << "          ╚═╝    ╚═════╝  ╚═════╝                         " << CYAN << "║\n";
    cout << "║" << BOLD << YELLOW << "                                                          " << CYAN << "║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n" << RESET;
    
    cout << CYAN << '\n';
    cout << "╔══════════════════════════════════════════════════════════╗\n";
    cout << "║" << BOLD << WHITE << "                    八数码 · 生日密码                     " << CYAN << "║\n";
    cout << "║" << WHITE << "                 寻找隐藏在数字中的惊喜                   " << CYAN << "║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n" << RESET;
    
    cout << "\n\n";
    cout << "     " << GREEN << "●" << CYAN << " 按 " << BOLD << YELLOW << "P" << CYAN << " 开始游戏\n";
    cout << "     " << GREEN << "●" << CYAN << " 按 " << BOLD << YELLOW << "H" << CYAN << " 查看帮助\n";
    cout << "     " << GREEN << "●" << CYAN << " 按 " << BOLD << YELLOW << "Q" << CYAN << " 退出程序\n";
    cout << '\n';
    cout << "     " << CYAN << "──────────────────────────────────────────\n" << RESET;
}

int main() {
    char c;
#ifdef _WIN32
    system("chcp 65001 > nul");
#endif
    while(1) {
        show_title();
        cout << "\n  " << BOLD << CYAN << "请选择操作: " << RESET;
        c = cin.get();
        cin.get();
        switch(c) {
            case 'p':
            case 'P':
                game();
                break;
            case 'h':
            case 'H':
                help();
                break;
            case 'q':
            case 'Q':
                clr_screen();
                cout << GREEN << '\n';
                cout << "╔══════════════════════════════════════════════════╗\n";
                cout << "║                                            ║\n";
                cout << "║      " << BOLD << "感谢使用, 再见!" << RESET << GREEN << "               ║\n";
                cout << "║                                            ║\n";
                cout << "╚══════════════════════════════════════════════════╝\n" << RESET;
                cout << '\n';
#ifdef _WIN32
                system("pause");
#endif
                return 0;
           default:
                cout << RED << "\n无效输入, 请按 P, H或 Q! \n" << RESET;
                SLEEP_MS(1000);
                break;
        }
    }
    return 0;
}