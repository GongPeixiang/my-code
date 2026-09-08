#include <bits/stdc++.h>
using namespace std;

constexpr int D = 8, S = 8; // 7 days, 7 sessions each day, 1-based

int n, k, cnt[D][S];
struct Node {
    float time;
    int cnt;
    bool operator<(const Node& other) const {
        if (cnt != other.cnt) return cnt < other.cnt;
        return time < other.time;
    }
} node[D*S];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k;
    int p, id;  
    char time[5];
    for (int i = 0; i < n; i++) {
        cin >> id >> p;
        for (int j = 0; j < p; j++) {
            cin >> time;
            int d = time[0] - '0'; // keep in 1-based
            int s = time[2] - '0';
            cnt[d][s]++;
        }
    }
    int ncnt = 0;
    for (int d = 1; d < D; d++) {
        for (int s = 1; s < S; s++) {
            float time = d + (s / 10.0f);
            node[ncnt++] = (Node){time, cnt[d][s]};
        }
    }
    sort(node, node + ncnt);
    for (int i = 0; i < k; i++) 
        cout << node[i].time << ' ' << node[i].cnt << '\n';
    return 0;
}