#include <bits/stdc++.h>
using namespace std;

constexpr int MAXS = (1<<24), tgt[12] = {0,0,0,0,0,0,0,0,0,0,0,0};

int stat[12], cnnt[12][4], dist[MAXS+5];
struct Node {
    int code, op;
    int f, g;
    bool operator<(const Node& other) const { return f > other.f; }
} pre[MAXS+5];
vector<int> path;

int encode() {
    int ret = 0;
    for (int i = 0; i < 12; i++) ret = ret * 4 + stat[i];
    return ret;
}

void decode(int code) {
    for (int i = 11; i >= 0; i--) {
        stat[i] = code % 4;
        code /= 4;
    }
}

int h() {
    int ans = 0;
    for (int i = 0; i < 12; i++) 
        if (stat[i]) ans += (4 - stat[i]);
    return ans / 2;
}

bool solve() {
    memset(dist, 0x3f, sizeof(dist));
    int init = encode();
    dist[init] = 0;
    priority_queue<Node, vector<Node>> pq;
    pq.push((Node){init, -1, h(), 0});
    pre[init] = (Node){-1, -1, -1, -1};
    while (!pq.empty()) {
        Node cur = pq.top(); pq.pop();
        int code = cur.code, g = cur.g;
        if (g > dist[code]) continue;
        decode(code);
        if (memcmp(stat, tgt, sizeof(tgt)) == 0) {
            Node trk = cur;
            while (trk.code != init) {
                path.push_back(trk.op + 1);
                trk = pre[trk.code];
            }
            reverse(path.begin(), path.end());
            return true;
        }
        for (int i = 0; i < 12; i++) {
            int nxt = cnnt[i][stat[i]];
            stat[i] = (stat[i] + 1) % 4;
            stat[nxt] = (stat[nxt] + 1) % 4;
            int ncode = encode(), ng = g + 1;
            if (ng < dist[ncode]) {
                dist[ncode] = ng;
                pre[ncode] = cur;
                pq.push((Node){ncode, i, ng + h(), ng});
            }
            stat[i] = (stat[i] + 3) % 4;
            stat[nxt] = (stat[nxt] + 3) % 4;
        }
    }
    return false;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    for (int i = 0; i < 12; i++) {
        cin >> stat[i]; stat[i]--;
        for (int j = 0; j < 4; j++)  { 
            cin >> cnnt[i][j];
            cnnt[i][j]--;
        }
    }
    if (!solve()) cout << "-1\n";
    else {
        int sz = path.size();
        cout << sz << '\n';
        for (int i = 0; i < sz; i++) cout << path[i] << " \n"[i == sz-1];
    }
    return 0;
}