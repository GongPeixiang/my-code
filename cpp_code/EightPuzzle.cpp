// A*算法模板题
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const array<pair<int, int>, 4> dir = {{ {-1, 0}, {0, -1}, {0, 1}, {1, 0} }};

struct Node {
    ll code;
    int last_mov;
    int g, h, f;
    Node *prev;
    Node(ll c, int l, int g, int h, Node *p):
        code(c), last_mov(l), g(g), h(h), prev(p) {
            f = g + h;
        }
};

// 优先队列返回true表示前者排在后者的后面
struct NodeCmp {
    bool operator()(const Node *a, const Node *b) const {
        if (a->f != b->f) 
            return a->f > b->f;
        return a->h > b->h;
    }
};

void pre_process(const array<array<int, 3>, 3> &target, 
    array<array<int, 2>, 9> &target_pos) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            int num = target[i][j];
            target_pos[num][0] = i;
            target_pos[num][1] = j;
        }
    }
}

ll encode(const array<array<int, 3>, 3> &board) {
    ll ret = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            ret = ret * 9 + board[i][j];
        }
    }
    return ret;
}

pair<int, int> decode(ll code, array<array<int, 3>, 3> &board) {
    pair<int, int> zero_pos;
    for (int i = 2; i >= 0; i--) {
        for (int j = 2; j >= 0; j--) {
            board[i][j] = code % 9;
            if (!board[i][j]) {
                zero_pos.first = i;
                zero_pos.second = j;
            }
            code /= 9;
        }
    }
    return zero_pos;
}

int heuristic(const array<array<int, 3>, 3> &board,
    const array<array<int, 2>, 9> &t_pos) {
    int cnt = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (!board[i][j]) 
                continue;
            int num = board[i][j];
            cnt += abs(i - t_pos[num][0]) + abs(j - t_pos[num][1]);
        }
    }
    return cnt;
}

vector<ll> solve(const array<array<int, 3>, 3> &init_board,
    const array<array<int, 3>, 3> &target) {
    if (init_board == target) 
        return {};

    array<array<int, 2>, 9> t_pos;
    pre_process(target, t_pos);

    int init_h = heuristic(init_board, t_pos);
    ll init_code = encode(init_board);
    auto init_node = make_unique<Node>(init_code, -1, 0, init_h, nullptr);

    priority_queue<Node *, vector<Node *>, NodeCmp> open_set;
    unordered_map<ll, int> best_g;
    vector<unique_ptr<Node>> all_nodes;

    open_set.push(init_node.get());
    best_g[init_code] = 0;
    all_nodes.push_back(move(init_node));
    // 由于使用了std::move(), init_node已无效, 需使用all_nodes[0]

    while (!open_set.empty()) {
        Node *cur_ptr = open_set.top();
        open_set.pop();

        ll cur_code = cur_ptr->code;
        int cur_g = cur_ptr->g;
        int last_mov = cur_ptr->last_mov;

        if (cur_g > best_g[cur_code]) 
            continue;

        array<array<int, 3>, 3> cur_board;
        pair<int, int> z_pos = decode(cur_code, cur_board);

        if (cur_board == target) {
            Node *trace_ptr = cur_ptr;
            vector<ll> path;
            while (trace_ptr != all_nodes[0].get()) {
                path.push_back(trace_ptr->code);
                trace_ptr = trace_ptr->prev;
            }
            reverse(path.begin(), path.end());
            return path;
        }

        int zr = z_pos.first, zc = z_pos.second;
        for (int i = 0; i < 4; i++) {
            if (i == 3 - last_mov) 
                continue;
            
            int nr = zr + dir[i].first, nc = zc + dir[i].second;
            if (nr < 0 || nr >= 3 || nc < 0 || nc >= 3) 
                continue;

            swap(cur_board[zr][zc], cur_board[nr][nc]);
            int new_h = heuristic(cur_board, t_pos);
            int new_g = cur_g + 1;
            ll new_code = encode(cur_board);
            if (best_g.find(new_code) == best_g.end() 
                || new_g < best_g[new_code]) {
                    best_g[new_code] = new_g;
                    auto new_node = make_unique<Node>(new_code, i, new_g, new_h, cur_ptr);
                    open_set.push(new_node.get());
                    all_nodes.push_back(move(new_node));
                }

            swap(cur_board[zr][zc], cur_board[nr][nc]);
        }
    }
    return {};
}

int main() {
    array<array<int, 3>, 3> init_board, target;
    cout << "Please enter your initial board:" << '\n';
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cin >> init_board[i][j];
        }
    }
    cout << "Please enter you target board:" << '\n';
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cin >> target[i][j];
        }
    }

    vector<ll> path = solve(init_board, target);

    cout << path.size() << '\n';
    array<array<int, 3>, 3> board;
    int steps = 1;
    for (ll code : path) {
        cout << "[steps " << steps++ << ']' << '\n';
        decode(code, board);
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) 
                cout << board[i][j] << ' ';
            cout << '\n';
        }
        cout << "---------" << '\n';
    }
}