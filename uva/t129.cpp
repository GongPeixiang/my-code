#include <bits/stdc++.h>
using namespace std;

constexpr int LEN = 85;

int N, L, seq[LEN], cnt = 0;

bool check(int dep) {
    if (!dep) return true;
    for (int l = 1; 2 * l <= dep + 1; ++l) {
        int s = dep + 1 - 2 * l;
        bool same = true;
        for (int i = 0; i < l; ++i) 
            if (seq[s+i] != seq[s+i+l]) { same = false; break; }
        if (same) return false;
    }
    return true;
}

void dfs(int dep) {
    if (cnt > N) return;
    if (cnt == N) {
        for (int i = 0; i < dep; ++i) putchar('A' + seq[i]);
        printf("\n%d\n", dep);
        return;
    }
    for (int i = 0; i < L; ++i) {
        seq[dep] = i;
        if (check(dep)) {
            ++cnt;
            dfs(dep + 1);
        }
    }
}

int main() {
    while (scanf("%d %d", &N, &L) == 2) {
        if (!N) break;
        cnt = 0; memset(seq, 0, sizeof(seq));
        dfs(0);
    }
    return 0;
}