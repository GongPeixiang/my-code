#include <bits/stdc++.h>
using namespace std;

constexpr int N = 100005;

int n, D;
struct Node { 
    int x, y; 
    bool operator<(const Node& other) const { return x < other.x; }
} node[N];

int solve() {
    int ans = 0x3f3f3f3f;
    deque<int> mxq, mnq;
    int l = 0;
    for (int r = 0; r < n; ++r) {
        while (!mxq.empty() && node[mxq.back()].y <= node[r].y) mxq.pop_back();
        mxq.push_back(r);
        while (!mnq.empty() && node[mnq.back()].y >= node[r].y) mnq.pop_back();
        mnq.push_back(r);
        while (l <= r && node[mxq.front()].y - node[mnq.front()].y >= D) {
            ans = min(ans, node[r].x - node[l].x);
            ++l;
            while (!mxq.empty() && mxq.front() < l) mxq.pop_front();
            while (!mnq.empty() && mnq.front() < l) mnq.pop_front();
        }
    }
    return ans;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> D;
    for (int i = 0; i < n; ++i) cin >> node[i].x >> node[i].y;
    sort(node, node + n);
    int ans = solve();
    if (ans < 0x3f3f3f3f) cout << ans << '\n';
    else cout << "-1\n";
    return 0;
}