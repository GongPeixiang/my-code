#include <stdio.h>

#define MAXN 100000
#define MAXLEN 5000
#define MOD 1000000007
//          2147483647

int n, a[MAXN];
int len_cnt[MAXLEN + 5], max_l = -1, min_l = 0x3f3f3f3f;

int solve() 
{
    long long ans = 0;
    for (int i = min_l + 1; i <= max_l; ++i) {
        if (len_cnt[i] < 2) 
            continue;
        long long c1 = (len_cnt[i] * (len_cnt[i] - 1)) / 2;
        for (int j = min_l; j <= i / 2; ++j) {
            if (len_cnt[j] && len_cnt[i - j]) {
                long long c2;
                if (j == i - j) 
                    c2 = (len_cnt[j] * (len_cnt[j] - 1)) / 2;
                else 
                    c2 = len_cnt[j] * len_cnt[i - j];
                ans = (ans + (c1 * c2) % MOD) % MOD;
            }
        }
    }
    return ans % MOD;
}

int main() 
{
    scanf(" %d", &n);
    for (int i = 0; i < n; ++i) {
        scanf(" %d", &a[i]);
        ++len_cnt[a[i]];
        max_l = a[i] > max_l ? a[i] : max_l;
        min_l = a[i] < min_l ? a[i] : min_l;
    }
    int ans = solve();
    printf("%d\n", ans);
    return 0;
}