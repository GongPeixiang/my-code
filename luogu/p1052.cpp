#include <bits/stdc++.h>
using namespace std;

constexpr int K = 105, M = 105;

int l, s, t, m, a[M], dp[M*K];
bool stone[M*K];

void compress() {
    int delta = 0, k = s * t, gap;
    for (int i = 1; i <= m; i++) {
        gap = a[i] - a[i-1] - delta;
        if (gap > k) delta += gap - k;
        a[i] -= delta;
        stone[a[i]] = 1;
    }
    l = a[m] + k;
}

int main() {
    scanf("%d%d%d%d", &l, &s, &t, &m);
    for (int i = 1; i <= m; i++) scanf("%d", &a[i]);
    sort(a+1, a+m+1);
    if(s == t){
        int cnt = 0;
        for(int i = 1; i <= m; i++)
            if(a[i]%s == 0) cnt++;
        printf("%d\n", cnt);
        return 0;
    }
    a[0] = 0; a[m+1] = l;
    compress();
    memset(dp, 0x3f, sizeof(dp));
    dp[0] = 0;
    for (int i = 1; i <= l; i++) 
        for (int j = s; j <= t && j <= i; j++) 
            dp[i] = min(dp[i], dp[i-j] + stone[i]);
    int ans = INT_MAX;
    for (int i = a[m]; i <= l; i++) ans = min(ans, dp[i]);
    printf("%d\n", ans);
    return 0;
}