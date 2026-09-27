#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define N 15

int n, a[N], sum = 0; 
bool vis[N];

int cmp(const void *a, const void *b) { return (int *)b - (int *)a; }

bool check(int pos, int l, int done, const int len, const int div) {
    if (done == div) return true;
    if (l == len) 
        if (check(0, 0, done + 1, len, div)) return true;
    for (int i = pos; i < n; ++i) {
        if (!vis[i] && l + a[i] <= len) {
            vis[i] = 1; 
            if (check(i+1, l+a[i], done, len, div)) return true;
            vis[i] = 0;
        }
    }
    return false;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
        sum += a[i];
    }
    qsort(a, n, sizeof(int), cmp);
    int ans = sum;
    for (int len = a[0]; len <= sum; ++len) {
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