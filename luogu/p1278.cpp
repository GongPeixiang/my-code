#include <bits/stdc++.h>
using namespace std;

// a, e, i, o, u

const int N = 16, LEN = 105;

int n, l[N], dp[1<<N][N];
char dict[N][LEN];
vector<int> g[5];

inline int c2i(char c);

int dfs(int stat, int u) {
    if (~dp[stat][u]) return dp[stat][u];
    int id = c2i(dict[u][l[u]-1]);
    int ans = 0;
    for (int i = 0; i < g[id].size(); i++) {
        int v = g[id][i];
        if ((stat>>v) & 1) continue;
        int nstat = stat | (1<<v);
        ans = max(ans, dfs(nstat, v));
    }
    return dp[stat][u] = ans + l[u];
}

inline int c2i(char c) {
    switch(c) {
        case 'A': return 0;
        case 'E': return 1;
        case 'I': return 2;
        case 'O': return 3;
        case 'U': return 4;
    }
    return -1;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s", dict[i]);
        l[i] = strlen(dict[i]);
        int id = c2i(dict[i][0]);
        g[id].push_back(i);
    }
    memset(dp, -1, sizeof(dp));
    int ans = 0;
    for (int i = 0; i < n; i++) {
        int init = (1<<i);
        ans = max(ans, dfs(init, i));
    }
    printf("%d\n", ans);
    return 0;
}