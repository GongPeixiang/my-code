#include <bits/stdc++.h>
using namespace std;

const int N = 1000005;

int n, to[N], in[N];
bool vis[N], gone[N];

int solve() {
    int ans = 0;
    queue<int> q;
    for (int i = 0; i < n; i++) 
        if (in[i] == 0) q.push(i);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        vis[u] = 1;
        int v = to[u];
        if (gone[u]) {
            if (--in[v] == 0) q.push(v);
        } else {
            if (!gone[v]) {
                ans++;
                gone[v] = 1;
                q.push(v);
            }
        }
    }
    // only ring and seperate point left, cannot choose sep point
    // calc the ring
    for (int i = 0; i < n; i++) {
        if (!vis[i] && in[i]) {
            int ring = 0;
            for (int j = i; !vis[j]; j = to[j]) {
                vis[j] = 1;
                ring++;
            }
            ans += ring / 2;
        }
    }
    return ans;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &to[i]);
        to[i]--;
        in[to[i]]++;
    }
    int ans = solve();
    printf("%d\n", ans);
    return 0;
}