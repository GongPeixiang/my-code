#include <bits/stdc++.h>
using namespace std;

const array<array<int, 2>, 4> dir = {{ {-1, 0}, {0, -1}, {0, 1}, {1, 0} }};
vector<vector<int>> board;
int m, n;

struct State {
    int r, c;
    int last_color;  
    bool used_magic; // 当前格子是否是魔法变出来的
    bool operator==(const State &other) const {
        return r == other.r && c == other.c && last_color == other.last_color 
            && used_magic == other.used_magic;
    }
};

struct StateHash {
    size_t operator()(const State &s) const {
        size_t h1 = hash<int>{}(s.r);
        size_t h2 = hash<int>{}(s.c);
        size_t h3 = hash<int>{}(s.last_color);
        size_t h4 = hash<bool>{}(s.used_magic);
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
    
    State start = {0, 0, board[0][0], false};
    auto start_node = make_unique<Node>(start, 0);
    
    open_set.push(start_node.get());
    best_g[start] = 0;
    all_nodes.push_back(move(start_node));

    while (!open_set.empty()) {
        auto cur = open_set.top();
        open_set.pop();
        
        int r = cur->state.r, c = cur->state.c;
        int last_color = cur->state.last_color;
        bool used_magic = cur->state.used_magic;
        int cur_g = cur->g;
        
        if (cur_g > best_g[cur->state]) 
            continue;
        
        if (r == m - 1 && c == m - 1) 
            return cur_g;
        
        for (int i = 0; i < 4; ++i) {
            int nr = r + dir[i][0], nc = c + dir[i][1];
            if (nr < 0 || nr >= m || nc < 0 || nc >= m) 
                continue;
            
            int next_color = board[nr][nc];
            int new_g;
            State next_state;
            
            if (next_color != -1) {
                if (used_magic) 
                    new_g = cur_g + (next_color == last_color ? 0 : 1);
                else 
                    new_g = cur_g + (next_color == board[r][c] ? 0 : 1);
                next_state = {nr, nc, next_color, false};
            } 
            else {
                if (used_magic) 
                    continue;
                new_g = cur_g + 2;
                next_state = {nr, nc, used_magic ? last_color : board[r][c], true};
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
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> m >> n;
    board.resize(m, vector<int>(m, -1));
    for (int i = 0; i < n; ++i) {
        int r, c, t;
        cin >> r >> c >> t;
        r--; c--;
        board[r][c] = t;
    }
    int ans = solve();
    cout << ans << '\n';
}