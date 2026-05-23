#include <bits/stdc++.h>
using namespace std;

constexpr int MAXM = 105;
constexpr int dir[4][2] = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};

int m, board[MAXM][MAXM];

struct State {
    int r, c;
    int last_color;  
    bool magic; // 当前格子是否是魔法变出来的
    bool operator==(const State &other) const {
        return r == other.r && c == other.c && last_color == other.last_color && magic == other.magic;
    }
};

struct StateHash {
    size_t operator()(const State &s) const {
        size_t h1 = hash<int>{}(s.r);
        size_t h2 = hash<int>{}(s.c);
        size_t h3 = hash<int>{}(s.last_color);
        size_t h4 = hash<bool>{}(s.magic);
        return ((h1 ^ (h2 << 1)) ^ (h3 << 2)) ^ (h4 << 3);
    }
};

struct Node {
    State state;
    int g;
    Node(State s, int g): state(s), g(g) {}
};

struct NodeCmp {
    bool operator()(const Node *a, const Node *b) const {
        return a->g > b->g;
    }
};

int solve() {
    priority_queue<Node *, vector<Node *>, NodeCmp> open_set;
    unordered_map<State, int, StateHash> best_g;
    vector<unique_ptr<Node>> all_nodes;
    
    State start = {1, 1, board[1][1], false};
    auto start_node = make_unique<Node>(start, 0);
    open_set.push(start_node.get());
    best_g[start] = 0;
    all_nodes.push_back(move(start_node));

    while (!open_set.empty()) {
        auto cur = open_set.top();
        open_set.pop();
        
        int r = cur->state.r, c = cur->state.c;
        int last_color = cur->state.last_color;
        bool magic = cur->state.magic;
        int cur_g = cur->g;
        
        if (cur_g > best_g[cur->state]) 
            continue;

        if (r == m && c == m) 
            return cur_g;
        
        for (int i = 0; i < 4; ++i) {
            int nr = r + dir[i][0], nc = c + dir[i][1];
            if (nr < 0 || nr > m || nc < 0 || nc > m) 
                continue;

            int new_g;
            State next_state;
            if (board[nr][nc] != -1) { 
                if (magic) 
                    new_g = cur_g + (board[nr][nc] == last_color ? 0 : 1);
                else 
                    new_g = cur_g + (board[nr][nc] == board[r][c] ? 0 : 1);
                next_state = {nr, nc, board[nr][nc], false};
            } else { 
                if (magic) continue;
                new_g = cur_g + 2;
                next_state = {nr, nc, board[r][c], true};
            }

            if (!best_g.count(next_state) || new_g < best_g[next_state]) {
                auto new_node = make_unique<Node>(next_state, new_g);
                best_g[next_state] = new_g;
                open_set.push(new_node.get());
                all_nodes.push_back(move(new_node));
            }
        }
    }
    return -1;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    memset(board, 0xff, sizeof(board));
    int n, r, c, t;
    cin >> m >> n;
    while (n--) {
        cin >> r >> c >> t;
        board[r][c] = t;
    }
    int ans = solve();
    cout << ans << '\n';
}