#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const array<int, 12> target = {{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }};
array<array<int, 4>, 12> connect;

struct Node {
    ll code;
    int op;
    int g, h, f;
    Node(ll code, int op, int g, int h): code(code), op(op), g(g), h(h) {
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

struct NodeHash {
    size_t operator()(const Node *a) const {
        return hash<ll> {}(a->code);
    }
};

struct HashEqual {
    bool operator()(const Node *a, const Node *b) const {
        return a->code == b->code;
    }
};

ll encode(const array<int, 12> &state) 
{
    ll ret = 0LL;
    for (int i = 0; i < 12; i++) 
        ret = ret * 4 + state[i];
    return ret;
}

void decode(ll code, array<int, 12> &state)
{
    for (int i = 11; i >= 0; i--) {
        state[i] = code % 4;
        code /= 4;
    }
}

int heuristic(array<int, 12> state)
{
    int h = 0;
    for (int i = 0; i < 12; i++) {
        if (state[i] != 0) 
            h += 4 - state[i];
    }
    return h / 2;   
}

vector<int> find_path(const array<int, 12> &init) 
{
    if (init == target) 
        return {};
    
    ll init_code = encode(init);
    auto init_node = make_unique<Node>(init_code, -1, 0, heuristic(init));

    priority_queue<Node *, vector<Node *>, NodeCmp> open_set;
    unordered_map<ll, int> best_g; // 记录最优解
    unordered_map<Node *, Node *, NodeHash, HashEqual> prev;
    vector<unique_ptr<Node>> all_nodes;

    open_set.push(init_node.get());
    prev[init_node.get()] = nullptr;
    all_nodes.push_back(move(init_node));
    best_g[init_code] = 0;

    while (!open_set.empty()) {
        Node *cur_ptr = open_set.top();
        open_set.pop();

        ll cur_code = cur_ptr->code;
        int cur_g = cur_ptr->g;

        if (cur_g > best_g[cur_code]) 
            continue;

        array<int, 12> cur_state;
        decode(cur_code, cur_state);

        if (cur_state == target) {
            vector<int> path;
            Node *track_ptr = cur_ptr;
            while (track_ptr != all_nodes[0].get()) {
                path.push_back(track_ptr->op);
                track_ptr = prev[track_ptr];
            }
            reverse(path.begin(), path.end());
            return path;
        }

        for (int i = 0; i < 12; i++) {
            array<int, 12> new_state = cur_state;
            int next = connect[i][new_state[i]];
            new_state[i] = (new_state[i] + 1) % 4;
            new_state[next] = (new_state[next] + 1) % 4;

            ll new_code = encode(new_state);
            int new_g = cur_g + 1;
            int new_h = heuristic(new_state);

            if (!best_g.count(new_code) || new_g < best_g[new_code]) {
                best_g[new_code] = new_g;
                auto new_node = make_unique<Node>(new_code, i, new_g, new_h);
                open_set.push(new_node.get());
                prev[new_node.get()] = cur_ptr;
                all_nodes.push_back(move(new_node));
            }
        }
    }
    return {};
}

int main()
{
    array<int, 12> init_state;
    for (int i = 0; i < 12; i++) {
        cin >> init_state[i];
        init_state[i]--;
        for (int j = 0; j < 4; j++) {
            cin >> connect[i][j];
            connect[i][j]--;  // 0-based 索引
        }
    }

    vector<int> path = find_path(init_state);
    cout << path.size() << '\n';
    for (int op : path) 
        cout << op + 1 << ' ';
}