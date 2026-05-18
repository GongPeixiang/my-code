#include <stdio.h>

typedef long long ll;

int main() 
{
    int n, m;
    scanf(" %d %d", &n, &m);
    ll ans1 = 0, ans2 = 0;
    for (int a = 1; a <= m; ++a) {
        for (int b = 1; b <= n; ++b) {
            int i = m - a + 1, j = n - b + 1;
            if (a == b) 
                ans1 += i * j;
            else
                ans2 += i * j;
        }
    }
    printf("%lld %lld\n", ans1, ans2);
}
