#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXN 15

int n, l[MAXN], sum = 0; 
bool vis[MAXN];

int cmp(const void *a, const void *b) { return (int *)b - (int *)a; }

bool check(int pos, int cur_len, int done, const int len, const int div) 
{
    if (done == div) return true;
    if (cur_len == len) 
        if (check(0, 0, done + 1, len, div)) return true;
    for (int i = pos; i < n; ++i) {
        if (!vis[i] && cur_len + l[i] <= len) {
            vis[i] = true; 
            if (check(i + 1, cur_len + l[i], done, len, div)) 
                return true;
            vis[i] = false;
        }
    }
    return false;
}

int main() 
{
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &l[i]);
        sum += l[i];
    }
    qsort(l, n, sizeof(int), cmp);
    int ans = sum;
    for (int len = l[0]; len <= sum; ++len) {
        if (sum % len != 0) continue;
        int div = sum / len;
        if (check(0, 0, 0, len, div)) {
            ans = len;
            break;
        }
    }
    printf("%d\n", ans);
    return 0;
}