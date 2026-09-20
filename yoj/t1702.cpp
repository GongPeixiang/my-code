#include <bits/stdc++.h>
using namespace std;

constexpr int N = 100005;

int n, a[N], b[N];

struct Node {
    int i, j;
    int sum;
    bool operator<(const Node& other) const { return sum > other.sum; }
};

void solve() {
    vector<int> ans;
    priority_queue<Node, vector<Node>> pq;
    for (int i = 0; i < n; i++) {
        pq.push((Node){i, 0, a[i] + b[0]});
    }
    while (ans.size() < n) {
        Node cur = pq.top(); pq.pop();
        int i = cur.i, j = cur.j, sum = cur.sum;
        ans.push_back(sum);
        if (j + 1 < n) pq.push((Node){i, j+1, a[i] + b[j+1]});
    }
    for (int i = 0; i < n; i++) printf("%d ", ans[i]);
} 

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);
    for (int j = 0; j < n; j++) scanf("%d", &b[j]);
    solve();
    return 0;
}