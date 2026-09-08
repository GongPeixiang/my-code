#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAXN 10000
typedef long long ll;

int m, n, a[MAXN + 5], tp = 0;
bool p[MAXN + 5];

bool judge(int k) 
{
    for (int i = 2; i <= k / 2; ++i) 
        if (k % i == 0) return false;
    return true;
}

void preprocess() 
{
    memset(p, 0, sizeof(p));
    for (int i = 2; i <= MAXN; ++i) 
        p[i] = judge(i);
}

ll func(int val) 
{
    memset(a, 0, sizeof(a));
    tp = 0;
    if (p[val]) return val - 1;
    for (int i = 2; i <= val / 2; ++i) {
        if (p[i] && val % i == 0) a[tp++] = i;
    }
    ll res = val;
    for (int i = 0; i < tp; ++i) 
        res = res * (a[i] - 1);
    for (int i = 0; i < tp; ++i) 
        res /= a[i];
    return res;
}

int main() 
{
    preprocess();
    scanf("%d %d", &m, &n);
    for (int i = m; i <= n; ++i) 
        printf("%lld ", func(i));
    return 0;
}