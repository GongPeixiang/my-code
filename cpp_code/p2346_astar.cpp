#include <bits/stdc++.h>
using namespace std;

const array<array<int, 2>, 4> dir = {{ {-1, 0}, {0, -1}, {1, 0}, {0, 1} }};

struct Node {
    int code;
    char prev_color;
    int g, h, f;
    Node(int c, char co, int g, int h):
        code(c), prev_color(co), g(g), h(h) {
            f = g + h;
        }
};

struct NodeCmp {
    bool operator()(const Node *a, const Node *b) const {
        if (a->f != b->f) 
            return a->f > b->f;
        return a->h > b->h;
    } 
};

int encode(const array<array<char, 4>, 4> &board) {
    int ret = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            switch(board[i][j]) {
                case 'O': ret = ret * 3 + 2; break;
                case 'W': ret = ret * 3 + 1; break;
                case 'B': ret = ret * 3; break;
                default: break;
            }
        }
    }
    return ret;
}

void decode(int code, array<array<char, 4>, 4> &board,
    vector<pair<int, int>> &space_pos) {
    int tmp;
    for (int i = 3; i >= 0; i--) {
        for (int j = 3; j >= 0; j--) {
            tmp = code % 3;
            switch(tmp) {
                case 2: board[i][j] = 'O';
                        space_pos.push_back(make_pair(i, j));
                        break;
                case 1: board[i][j] = 'W'; break;
                case 0: board[i][j] = 'B'; break;
                default: break;
            }
            code /= 3;
        }
    }
}

void pre_process(const array<array<char, 4>, 4> &board,
    array<array<int, 4>, 2> &row_cnt,  array<array<int, 4>, 2> &col_cnt, 
    array<int, 2> &left_cnt, array<int, 2> &right_cnt) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (board[i][j] == 'W') {
                row_cnt[0][i]++;
                col_cnt[0][j]++;
                if (i == j) 
                    left_cnt[0]++;
                if (i == 3 - j) 
                    right_cnt[0]++;
            } else if (board[i][j] == 'B') {
                row_cnt[1][i]++;
                col_cnt[1][j]++;
                if (i == j) 
                    left_cnt[1]++;
                if (i == 3 - j) 
                    right_cnt[1]++;
            }
        }
    }
}

int heuristic(const array<array<char, 4>, 4> &board) {
    array<array<int, 4>, 2> row_cnt = {0}, col_cnt = {0};
    array<int, 2> left_cnt = {0}, right_cnt = {0};
    pre_process(board, row_cnt, col_cnt, left_cnt, right_cnt);
    int max_cnt = 0;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 4; j++) {
            int tmp = max(row_cnt[i][j], col_cnt[i][j]);
            max_cnt = max(max_cnt, tmp);
        }
    }
    for (int i = 0; i < 2; i++) {
        int tmp = max(left_cnt[i], right_cnt[i]);
        max_cnt = max(max_cnt, tmp);
    }
    return (4 - max_cnt);
}

bool judge(const array<array<char, 4>, 4> &board) {
    array<array<int, 4>, 2> row_cnt = {0}, col_cnt = {0};
    array<int, 2> left_cnt = {0}, right_cnt = {0};
    pre_process(board, row_cnt, col_cnt, left_cnt, right_cnt);
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 4; j++) {
            if (row_cnt[i][j] == 4 || col_cnt[i][j] == 4) 
                return true;
        }
    }
    return (left_cnt[0] == 4 || left_cnt[1] == 4 || right_cnt[0] == 4 ||
        right_cnt[1] == 4);
}

int solve(const array<array<char, 4>, 4> &init_board) {
    int init_code = encode(init_board);
    if (judge(init_board)) 
        return 0;

    int init_h = heuristic(init_board);
    auto init_node_w = make_unique<Node>(init_code, 'W', 0, init_h);
    auto init_node_b = make_unique<Node>(init_code, 'B', 0, init_h);

    priority_queue<Node *, vector<Node *>, NodeCmp> open_set;
    unordered_map<int, int> best_g;
    vector<unique_ptr<Node>> all_nodes;

    open_set.push(init_node_w.get());
    open_set.push(init_node_b.get());
    best_g[init_code] = 0;
    all_nodes.push_back(move(init_node_w));
    all_nodes.push_back(move(init_node_b));

    while (!open_set.empty()) {
        Node *cur_ptr = open_set.top();
        open_set.pop();

        int cur_code = cur_ptr->code;
        int cur_g = cur_ptr->g;
        char prev_color = cur_ptr->prev_color;

        if (best_g[cur_code] < cur_g) 
            continue;
        
        array<array<char, 4>, 4> cur_board;
        vector<pair<int, int>> space_pos;
        decode(cur_code, cur_board, space_pos);

        if (judge(cur_board)) 
            return cur_g;

        for (auto sp : space_pos) {
            int sr = sp.first, sc = sp.second;
            for (int i = 0; i < 4; i++) {
                int nr = sr + dir[i][0], nc = sc + dir[i][1];
                if (nr < 0 || nr >= 4 || nc < 0 || nc >= 4) 
                    continue;
                if (cur_board[nr][nc] == 'O') 
                    continue;
                
                char cur_color = cur_board[nr][nc];
                if (cur_color == prev_color) 
                    continue;                

                swap(cur_board[sr][sc], cur_board[nr][nc]);
                int new_code = encode(cur_board);
                int new_g = cur_g + 1;
                int new_h = heuristic(cur_board);

                if (!best_g.count(new_code)|| new_g < best_g[new_code]) {
                    auto new_node = make_unique<Node>(new_code, cur_color, new_g, new_h);
                    open_set.push(new_node.get());
                    best_g[new_code] = new_g;
                    all_nodes.push_back(move(new_node));
                }

                swap(cur_board[sr][sc], cur_board[nr][nc]);
            }
        }
    }
    return -1;
}

int main() {
    array<array<char, 4>, 4> init_board;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cin >> init_board[i][j];
        }
    }

    int steps = solve(init_board);
    cout << steps << '\n';
}