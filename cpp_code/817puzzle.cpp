#include <bits/stdc++.h>
using namespace std;
using ll = long long;

constexpr array<pair<int, int>, 4> directions = {{ {-1, 0}, {0, -1}, 
    {1, 0}, {0, 1} 
}};

struct Node {
    ll code;
    int g, h, f;
    Node *prev;
    Node(ll c, int g, int h, Node *p): code(c), g(g), 
    h(h), prev(p) {
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

ll encode(const array<array<int, 3>, 3> &board) {
    ll code = 0;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            code = code * 9 + board[i][j];
        }
    }
    return code;
}

pair<int, int> decode(ll code, array<array<int, 3>, 3> &board) {
    pair<int, int> zero_pos;
    for (int i = 2; i >= 0; --i) {
        for (int j = 2; j >= 0; --j) {
            board[i][j] = code % 9;
            if (!board[i][j]) 
                zero_pos = make_pair(i, j);
            code /= 9;
        }
    }
    return zero_pos;
}

int heuristic(const array<array<int, 3>, 3> &board) {
    int cnt = 0;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            switch(board[i][j]){
                case 8: cnt += abs(i) + abs(j); break;
                case 1: cnt += abs(i) + abs(j - 1); break;
                case 7: cnt += abs(i) + abs(j - 2); break;
                default: break;
            }
        }
    }
    return cnt;
}

inline bool judge(const array<array<int, 3>, 3> &board) {
    return board[0][0] == 8 && board[0][1] == 1 && board[0][2] == 7;
}

vector<ll> a_star(const array<array<int, 3>, 3> &init_board) {
    if (judge(init_board)) 
        return {};

    ll init_code = encode(init_board);
    int init_h = heuristic(init_board);
    auto init_node = make_unique<Node>(init_code, 0, init_h, nullptr);

    priority_queue<Node *, vector<Node *>, NodeCmp> open_set;
    unordered_map<ll, int> best_g;
    vector<unique_ptr<Node>> all_nodes;

    open_set.push(init_node.get());
    best_g[init_code] = 0;
    all_nodes.push_back(move(init_node));

    while (!open_set.empty()) {
        Node *cur_ptr = open_set.top();
        open_set.pop();
        ll cur_code = cur_ptr->code;
        if (best_g[cur_code] < cur_ptr->g) 
            continue;

        array<array<int, 3>, 3> cur_board;
        pair<int, int> zero_pos = decode(cur_code, cur_board);
        
        if (judge(cur_board)) {
            Node *trace_ptr = cur_ptr;
            vector<ll> path;
            while (trace_ptr != all_nodes[0].get()) {
                path.push_back(trace_ptr->code);
                trace_ptr = trace_ptr->prev;
            }
            reverse(path.begin(), path.end());
            return path;
        }

        int zr = zero_pos.first, zc = zero_pos.second;
        for (auto dir : directions) {
            int nr = zr + dir.first, nc = zc + dir.second;
            if (nr < 0 || nr >= 3 || nc < 0 || nc >= 3) 
                continue;

            swap(cur_board[zr][zc], cur_board[nr][nc]);
            int new_h = heuristic(cur_board);
            int new_g = cur_ptr->g + 1;
            ll new_code = encode(cur_board);

            if (!best_g.count(new_code) || new_g < best_g[new_code]) {
                best_g[new_code] = new_g;
                auto new_node = make_unique<Node>(new_code, new_g, 
                    new_h, cur_ptr);
                open_set.push(new_node.get());
                all_nodes.push_back(move(new_node));
            }

            swap(cur_board[zr][zc], cur_board[nr][nc]);
        }
    }
    return {};
}

int main() {
    array<array<int, 3>, 3> init_board;
    cout << "Please enter your initial board:" << '\n';
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            cin >> init_board[i][j];
        }
    }

    vector<ll> path = a_star(init_board);

    cout << path.size() << " steps" << '\n';
    array<array<int, 3>, 3> cur_board;
    for (int k = 0; k < path.size(); ++k) {
        cout << "steps " << k + 1 << '\n';
        decode(path[k], cur_board);
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) 
                cout << cur_board[i][j] << ' ';
            cout << '\n';
        }
        cout << "---------" << '\n';
    }
}