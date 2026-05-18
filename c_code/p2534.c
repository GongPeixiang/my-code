#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXN 16

int N, a[MAXN], cpy[MAXN];

void rev(int s, int d) 
{
    int mid = (s + d) / 2, tmp;
    for (int i = s; i <= mid; ++i) {
        tmp = a[i];
        a[i] = a[d - i + s];
        a[d - i + s] = tmp;
    }
}

int heuristic(void) 
{
    int cnt = 0;
    for (int i = 0; i < N - 1; ++i) {
        if (abs(a[i] - a[i + 1]) != 1) 
            ++cnt;
    }
    if (a[N - 1] != N - 1) 
        ++cnt;
    return cnt;
}

bool dfs(int dep, const int max_dep, int prev) // prev是上次反转的末位
{
    int h = heuristic();
    if (!h) 
        return true;
    if (dep + h > max_dep) 
        return false;
    for (int i = 1; i < N; ++i) {
        if (i == prev) continue;
        rev(0, i);
        if (dfs(dep + 1, max_dep, i)) 
            return true;
        rev(0, i);
    }
    return false;
}

int solve() 
{
    for (int max_dep = 0; ; ++max_dep) {
        if (dfs(0, max_dep, -1)) 
            return max_dep;
    }
    return -1;
}

int cmp(const void *a, const void *b) { return *(int *)a - *(int *)b; }

int main()
{
    scanf("%d", &N);
    for (int i = 0; i < N; ++i) {
        scanf("%d", &a[i]);
        cpy[i] = a[i];
    }
    qsort(cpy, N, sizeof(int), cmp);
    int tmp;
    for (int i = 0; i < N; ++i) {
        tmp = a[i];
        a[i] = (int *)bsearch(&tmp, cpy, N, sizeof(int), cmp) - cpy;
    }
    int min_step = solve();
    printf("%d\n", min_step);
    return 0;
}