#include <stdio.h>

#define MAXN 100000

// 巧妙! 转化成求LIS,因为数字各不相同,因此可以这么操作

int N, a[MAXN], b[MAXN], m[MAXN + 5];
int lis[MAXN + 5], tp = 0;

int solve()
{
    lis[tp++] = b[0];
    for (int i = 1; i < N; ++i) {
        int l = 0, r = tp, mid;
        while (l < r) {
            mid = l + (r - l) / 2;
            if (lis[mid] >= b[i]) 
                r = mid;
            else 
                l = mid + 1;
        }
        if (l != tp) 
            lis[l] = b[i];
        else 
            lis[tp++] = b[i];
    }
    return tp;
}

int main() 
{
    scanf("%d", &N);
    for (int i = 0; i < N; ++i) {
        scanf("%d", &a[i]);
        m[a[i]] = i;
    }
    for (int i = 0; i < N; ++i) {
        scanf("%d", &b[i]);
        b[i] = m[b[i]];
    }
    int ans = solve();
    printf("%d\n", ans);
    return 0;
}