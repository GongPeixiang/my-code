#include <bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr ll MAXCODE = 1ll << 24;
constexpr int tgt[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

int stat[12], cnnct[12][4], best_g[MAXCODE+5];
vector<int> path;

struct Node {
    ll code; 
    int op;
    int g, f;
    bool operator<(const Node& other) const { return f > other.f; }
} pre[MAXCODE+5];

ll encode() {
    ll ret = 0;
    for (int i = 0; i < 12; ++i) 
        ret = ret * 4 + stat[i];
    return ret;
}

void decode(ll code) {
    for (int i = 11; i >= 0; --i) {
        stat[i] = code % 4;
        code /= 4;
    }
}

int hrstic() {
    int h = 0;
    for (int i = 0; i < 12; ++i) 
        if (stat[i]) h += (4 - stat[i]);
    return h / 2;
}

void solve() {
    memset(best_g, 0x3f, sizeof(best_g));
    memset(pre, 0xff, sizeof(pre));
    priority_queue<Node, vector<Node>> pq;

    ll init_code = encode();
    Node init_node = Node{init_code, -1, 0, hrstic()};
    pq.push(init_node);
    best_g[init_code] = 0, pre[init_code] = Node{-1, -1, -1, -1};

    while (!pq.empty()) {
        auto cur = pq.top();
        pq.pop();

        ll cur_code = cur.code;
        int cf = cur.f, cg = cur.g;
        if (cg > best_g[cur_code]) continue;
        decode(cur_code);
        if (memcmp(stat, tgt, sizeof(tgt)) == 0) {
            Node trk = cur;
            while (1) {
                if (trk.code == init_code) break;
                path.push_back(trk.op);
                trk = pre[trk.code];
            }
            reverse(path.begin(), path.end());
            return;
        }

        for (int i = 0; i < 12; ++i) {
            int nxt = cnnct[i][stat[i]];
            stat[i] = (stat[i] + 1) % 4;
            stat[nxt] = (stat[nxt] + 1) % 4;

            ll new_code = encode();
            int ng = cg + 1, nf = ng + hrstic();
            if (ng < best_g[new_code]) {
                best_g[new_code] = ng;
                pre[new_code] = cur;
                auto new_node = Node{new_code, i, ng, nf};
                pq.push(new_node);
            }

            stat[i] = (stat[i] + 3) % 4;
            stat[nxt] = (stat[nxt] + 3) % 4;
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    for (int i = 0; i < 12; ++i) {
        cin >> stat[i];
        --stat[i];
        for (int j = 0; j < 4; ++j) {
            cin >> cnnct[i][j];
            --cnnct[i][j];
        }
    }
    solve();
    cout << path.size() << '\n';
    for (int op: path) cout << op + 1 << ' ';
    return 0;
}