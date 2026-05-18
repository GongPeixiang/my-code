#include <stdio.h>

#define MAXN 1000000
typedef long long ll;

int n, m, h[MAXN], max_h = 0;

int main() 
{
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &h[i]);
        max_h = h[i] > max_h ? h[i] : max_h;
    }
    int l = 0, r = max_h;
    int ans;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        ll get = 0;
        for (int i = 0; i < n; ++i) {
            if (h[i] > mid) 
                get += h[i] - mid;
        }
        if (get >= m) {
            ans = mid;
            l = mid + 1;
        }
        else 
            r = mid - 1; 
    }
    printf("%d\n", ans);
    return 0;
}