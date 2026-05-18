#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <memory>
#include <array>
#include <chrono>
#include <thread>
#include <cmath>
#include <string>
#include <iomanip>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

using namespace std;

const string RESET = "\033[0m";
const string BOLD = "\033[1m";
const string UNDERLINE = "\033[4m";
const string BLINK = "\033[5m";
const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string YELLOW = "\033[33m";
const string BLUE = "\033[34m";
const string MAGENTA = "\033[35m";
const string CYAN = "\033[36m";
const string WHITE = "\033[37m";

constexpr int BOARD_SIZE = 3;
constexpr array<pair<int, int>, 4> DIRECTIONS = {{
    {-1, 0}, {0, -1}, {1, 0}, {0, 1}
}};

using Board = array<array<int, BOARD_SIZE>, BOARD_SIZE>;
using ll = long long;

void sleep_ms(int ms) {
#ifdef _WIN32
    Sleep(ms);
#else
    this_thread::sleep_for(chrono::milliseconds(ms));
#endif
}

void clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

ll encode(const Board &board) {
    ll code = 0;
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            code = code * 9 + board[i][j];
        }
    }
    return code;
}

pair<int, int> decode(ll code, Board &board) {
    int zr = 0, zc = 0;
    for (int i = BOARD_SIZE - 1; i >= 0; --i) {
        for (int j = BOARD_SIZE - 1; j >= 0; --j) {
            board[i][j] = code % 9;
            if (board[i][j] == 0) {
                zr = i;
                zc = j;
            }
            code /= 9;
        }
    }
    return {zr, zc};
}

int heuristic(const Board &board) {
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

inline bool is_goal(const Board &board) {
    return board[0][0] == 8 && board[0][1] == 1 && board[0][2] == 7;
}

struct Node {
    ll code;
    int g, h, f;
    Node *prev;
    Node(ll c, int _g, int _h, Node *p) 
        : code(c), g(_g), h(_h), f(_h + _g), prev(p) {}
};

struct NodeCmp {
    bool operator()(const Node *a, const Node *b) const {
        if (a->f != b->f) 
            return a->f > b->f;
        return a->h > b->h;
    }
};

void print_border(const string &title) {
    cout << CYAN << "╔";
    for(int i = 0; i < 36; ++i) 
        cout << "═";
    cout << "╗\n";
    cout << "║" << BOLD << WHITE << " " << left << setw(34) 
              << title.substr(0, 34) << RESET << CYAN << "║\n";
    cout << "╠";
    for(int i = 0; i < 36; ++i) 
        cout << "═";
    cout << "╣\n" << RESET;
}

void print_board(const Board &board) {
    cout << "\n";
    for (int i = 0; i < BOARD_SIZE; ++i) {
        cout << "  ";
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (board[i][j] == 0) 
                cout << GREEN << "┌───┐" << RESET;
            else 
                cout << "┌───┐";
        }
        cout << "\n  ";
        
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (board[i][j] == 0) 
                cout << GREEN << "│   │" << RESET;
            else if (board[i][j] == 8 || board[i][j] == 1 || board[i][j] == 7) 
                cout << YELLOW << "│ " << board[i][j] << " │" << RESET;
            else 
                cout << "│ " << board[i][j] << " │";
        }
        cout << "\n  ";
        
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (board[i][j] == 0) 
                cout << GREEN << "└───┘" << RESET;
            else 
                cout << "└───┘";
        }
        cout << "\n";
    }
    cout << "\n";
}

bool validate_input(const Board &board) {
    array<int, 9> count = {0};
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            int num = board[i][j];
            if (num < 0 || num > 8) {
                cout << RED << "错误: 数字必须在 0-8 之间！\n" << RESET;
                return false;
            }
            count[num]++;
        }
    }
    
    for (int i = 0; i < 9; ++i) {
        if (count[i] != 1) {
            cout << RED << "错误: 数字 " << i << " 必须出现且仅出现一次！\n" << RESET;
            return false;
        }
    }
    return true;
}

vector<ll> solve_path(const Board &init_board) {
    if (is_goal(init_board)) 
        return {};

    vector<unique_ptr<Node>> all_nodes;
    priority_queue<Node *, vector<Node *>, NodeCmp> open_set;
    unordered_map<ll, int> best_g;
  
    ll init_code = encode(init_board);
    int init_h = heuristic(init_board); 
    auto init_node = make_unique<Node>(init_code, 0, init_h, nullptr);

    best_g[init_code] = 0;
    open_set.push(init_node.get());
    all_nodes.push_back(move(init_node));
        
    Board board;
        
    while (!open_set.empty()) {
        auto cur_ptr = open_set.top();
        open_set.pop();
            
        if (best_g[cur_ptr->code] < cur_ptr->g) 
            continue;
            
        auto [zr, zc] = decode(cur_ptr->code, board);
            
        if (is_goal(board)) {
            Node *track_ptr = cur_ptr;
            vector<ll> path;
            while (track_ptr != all_nodes[0].get()) {
                path.push_back(track_ptr->code);
                track_ptr = track_ptr->prev;
            }
            reverse(path.begin(), path.end());
            return path;
        }
            
        for (const auto &[dr, dc] : DIRECTIONS) {
            int nr = zr + dr, nc = zc + dc;
            if (nr < 0 || nr >= BOARD_SIZE || nc < 0 || nc >= BOARD_SIZE) 
                continue;
                
            swap(board[zr][zc], board[nr][nc]);
            ll new_code = encode(board);
            int new_g = cur_ptr->g + 1;
            int new_h = heuristic(board);
                
            auto it = best_g.find(new_code);
            if (it == best_g.end() || new_g < it->second) {
                auto new_node = make_unique<Node>(new_code, new_g, 
                    new_h, cur_ptr);
                best_g[new_code] = new_g;
                open_set.push(new_node.get());
                all_nodes.push_back(move(new_node));
            }
                
            swap(board[zr][zc], board[nr][nc]);
        }
    }

    return {};
}

// 游戏主逻辑
void game() {
    clear_screen();
    print_border("一个特别的八数码游戏");
    
    cout << YELLOW << "\n输入说明:\n" << RESET;
    cout << "  请按行输入 9 个数字 (0-8)，0 代表空格\n";
    cout << "  例如:\n";
    cout << "  2 1 3\n";
    cout << "  8 0 7\n";
    cout << "  4 5 6\n\n";
    cout << CYAN << "请输入您的初始棋盘:\n" << RESET;
    cout << "(输入 9 个数字，空格分隔，每行 3 个)\n\n";
    
    Board init_board;
    bool valid = false;
    while (!valid) {
        for (int i = 0; i < BOARD_SIZE; ++i) {
            cout << "第 " << i + 1 << " 行: ";
            for (int j = 0; j < BOARD_SIZE; ++j) {
                cin >> init_board[i][j];
            }
        }
        valid = validate_input(init_board);
        if (!valid) {
            cout << RED << "\n输入无效，请重新输入！\n\n" << RESET;
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }
    
    cin.clear();
    cin.ignore(10000, '\n');
    
    cout << GREEN << "\n✓ 输入成功！正在计算最优解...\n" << RESET;
    sleep_ms(500);
    
    const auto &path = solve_path(init_board);
        
    clear_screen();
    print_border("求解结果");
        
    cout << GREEN << BOLD << "\n✨ 找到解决方案！✨\n" << RESET;
    cout << CYAN << "总共需要 " << YELLOW << BOLD << path.size() << CYAN << " 步\n\n" << RESET;
    cout << UNDERLINE << "路径演示:\n\n" << RESET;
    sleep_ms(1000);
        
    Board board;
    for (size_t i = 0; i < path.size(); ++i) {
        cout << CYAN << "╔═════════════════════════════╗\n";
        cout << "║  " << BOLD << "第 " << setw(2) << i + 1 << " 步" << RESET << CYAN << "                   ║\n";
        cout << "╚═════════════════════════════╝\n" << RESET;
        decode(path[i], board);
        print_board(board);
        cout << "───────────────────────────────\n";
        sleep_ms(500);
    }
        
    cout << "\n";
    cout << BLINK;
    sleep_ms(200);
    cout << BOLD << RED << "\n★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★\n";
    cout << "★                                            ★\n";
    cout << "★  " << MAGENTA << "8  1  7" << RED << "  -  你的生日！        " << RED << "★\n";
    cout << "★  " << YELLOW << "第一行 8.17，祝你生日快乐！" << RED << "           ★\n";
    cout << "★                                            ★\n";
    cout << "★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★\n" << RESET;
    sleep_ms(500);
        
    cout << BOLD << GREEN << "\n✨ 恭喜你找到了隐藏的惊喜！✨\n\n" << RESET;
    cout << "\n" << CYAN << "按任意键返回主菜单..." << RESET;
    cin.get();
}

void show_help() {
    clear_screen();
    print_border("帮助文档");
    
    cout << CYAN << "\n【游戏介绍】\n" << RESET;
    cout << "  这是一个特殊的八数码游戏，目标是拼出特定的图案。\n\n";
    
    cout << CYAN << "【目标状态】\n" << RESET;
    Board target = {{{8, 1, 7}, {0, 0, 0}, {0, 0, 0}}};
    print_board(target);
    
    cout << CYAN << "【游戏规则】\n" << RESET;
    cout << "  • 通过移动数字块（与空格交换位置）来重组棋盘\n";
    cout << "  • 最终将棋盘变成目标状态\n";
    cout << "  • 程序会自动寻找最优解并演示移动步骤\n\n";
    
    cout << CYAN << "【操作说明】\n" << RESET;
    cout << "  • 输入初始棋盘时，每行输入3个数字（0-8）\n";
    cout << "  • 0 代表空格位置\n";
    cout << "  • 程序会验证输入是否有效\n\n";
    
    cout << YELLOW << "【特殊提示】\n" << RESET;
    cout << "  完成游戏后会有惊喜哦！🎁\n\n";
    
    cout << CYAN << "按任意键返回主菜单...\n" << RESET;
    cin.get();
}

void show_title() {
    clear_screen();
    cout << CYAN << "\n";
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
    
    cout << CYAN << "\n";
    cout << "╔══════════════════════════════════════════════════════════╗\n";
    cout << "║" << BOLD << WHITE << "                    八数码 · 生日密码                     " << CYAN << "║\n";
    cout << "║" << WHITE << "                 寻找隐藏在数字中的惊喜                   " << CYAN << "║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n" << RESET;
    
    cout << "\n\n";
    cout << "     " << GREEN << "●" << CYAN << " 按 " << BOLD << YELLOW << "P" << CYAN << " 开始游戏\n";
    cout << "     " << GREEN << "●" << CYAN << " 按 " << BOLD << YELLOW << "H" << CYAN << " 查看帮助\n";
    cout << "     " << GREEN << "●" << CYAN << " 按 " << BOLD << YELLOW << "Q" << CYAN << " 退出程序\n";
    cout << "\n";
    cout << "     " << CYAN << "──────────────────────────────────────────\n" << RESET;
}

int main() {
#ifdef _WIN32
    system("chcp 65001 > nul");
#endif
    
    char choice;
    while(true) {
        show_title();
        cout << "\n  " << BOLD << CYAN << "请选择操作: " << RESET;
        cin >> choice;
        cin.ignore();
        switch(tolower(choice)) {
            case 'P':
            case 'p':
                game();
                break;
            case 'H':
            case 'h':
                show_help();
                break; 
            case 'Q':
            case 'q':
                clear_screen();
                cout << GREEN << "\n";
                cout << "╔════════════════════════════════════════════╗\n";
                cout << "║                                            ║\n";
                cout << "║      " << BOLD << "感谢使用，再见！" << RESET << GREEN << "               ║\n";
                cout << "║                                            ║\n";
                cout << "╚════════════════════════════════════════════╝\n" << RESET;
                cout << "\n";
                system("pause");
                return 0;
            default:
                cout << RED << "\n无效输入，请按 P、H 或 Q！\n" << RESET;
                sleep_ms(1000);
                break;
        }
    }
}