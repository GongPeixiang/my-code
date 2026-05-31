#include <stdio.h>
#include <stdbool.h>

#define MAXN 100000

int n, m, a[MAXN];

bool check(int maxs) 
{
    int cnt = 1, s = 0;
    for (int i = 0; i < n; ++i) {
        if (s + a[i] <= maxs) 
            s += a[i];
        else {
            ++cnt;
            s = a[i];
        }
    }
    return cnt <= m;
}

int main() 
{
    scanf(" %d %d", &n, &m);
    int sum = 0, max_ele = -1;
    for (int i = 0; i < n; ++i) {
        scanf(" %d", &a[i]);
        sum += a[i];
        max_ele = a[i] > max_ele ? a[i] : max_ele;
    }
    int l = max_ele, r = sum;
    int ans;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (check(mid)) {
            ans = mid;
            r = mid - 1;
        }
        else 
            l = mid + 1;
    }
    printf("%d\n", ans);
    return 0;
}