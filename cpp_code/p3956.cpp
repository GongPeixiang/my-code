#include <bits/stdc++.h>
using namespace std;

constexpr int MAXM = 105;
constexpr int dx[4] = {-1, 0, 0, 1};
constexpr int dy[4] = {0, -1, 1, 0};

int m, board[MAXM][MAXM], best_g[MAXM][MAXM][2][2];

struct Node {
    int r, c;
    int cl; bool mag;
    int g;
    Node(int r, int c, int pc, bool m, int g): r(r), c(c), cl(pc), 
    mag(m), g(g) {}
    struct Cmp {
        bool operator()(const Node *a, const Node *b) const {
            return a->g > b->g;
        }
    };
};

int solve() {
    priority_queue<Node *, vector<Node *>, Node::Cmp> pq;
    vector<unique_ptr<Node>> all_nodes;
    
    auto init_node = make_unique<Node>(0, 0, board[0][0], false, 0);
    pq.push(init_node.get());
    all_nodes.push_back(move(init_node));

    while (!pq.empty()) {
        auto cur = pq.top();
        pq.pop();
        int r = cur->r, c = cur->c, cl = cur->cl, mag = cur->mag;
        int curg = cur->g;
        if (curg > best_g[r][c][cl][mag]) continue;
        if (r == m - 1 && c == m - 1) 
            return curg;
        for (int i = 0; i < 4; ++i) {
            int nr = r + dx[i], nc = c + dy[i];
            if (nr < 0 || nr >= m || nc < 0 || nc >= m) continue;
            int ng = 0, ncl = -1;
            bool nmag = false;
            if (board[nr][nc] != -1) {
                ng = curg + (board[nr][nc] == cl ? 0 : 1);
                ncl = board[nr][nc]; 
            } else {
                if (mag) continue;
                ng = curg + 2;
                ncl = cl;
                nmag = true;
            }
            if (ng < best_g[nr][nc][ncl][nmag]) {
                auto new_node = make_unique<Node>(nr, nc, ncl, nmag, ng);
                best_g[nr][nc][ncl][nmag] = ng;
                pq.push(new_node.get());
                all_nodes.push_back(move(new_node));
            }
        }
    }
    return -1;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    memset(board, 0xff, sizeof(board));
    memset(best_g, 0x3f, sizeof(best_g));
    int n, r, c, t;
    cin >> m >> n;
    while (n--) {
        cin >> r >> c >> t;
        --r, --c;
        board[r][c] = t;
    }
    int ans = solve();
    cout << ans << '\n';
}