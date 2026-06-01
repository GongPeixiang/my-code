#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXM 50
#define MAXN 1000

int m, n;
int timber[MAXM], need[MAXN], cpy[MAXM];

bool dfs(int done, int cur, const int t) {
    if (done == t) 
        return true;
    if (done + n - cur < t) 
        return false;
    for (int i = cur; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (timber[j] >= need[i]) {
                timber[j] -= need[i];
                if (dfs(done + 1, i + 1, t)) 
                    return true;
                timber[j] += need[i];
            }
        }
    }
    return false;
}

int solve() {
    memcpy(cpy, timber, sizeof(timber));
    int l = 0, r = n;
    while (l <= r) {
        memcpy(timber, cpy, sizeof(timber));
        int mid = l + (r - l) / 2; // 避免溢出
        if (dfs(0, 0, mid)) 
            l = mid + 1;
        else
            r = mid - 1;
    }
    return l - 1;
}

int cmp(const void *a, const void *b) { return *(int *)b - *(int *)a; }

int main() {
    scanf("%d", &m);
    for (int i = 0; i < m; ++i) 
        scanf("%d", &timber[i]);
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) 
        scanf("%d", &need[i]);
    qsort(timber, m, sizeof(int), cmp);
    qsort(need, n, sizeof(int), cmp);
    int ans = solve();
    printf("%d\n", ans);
    return 0;
}