#include <stdio.h>

#define MAXN 100000

int h[MAXN], n = 0;
int lnis[MAXN], tp1 = 0, lis[MAXN], tp2 = 0;

int main() 
{
    int tmp;
    while (scanf("%d", &tmp) == 1) // EOF为-1 
        h[n++] = tmp;
    lnis[tp1++] = h[0];
    for (int i = 1; i < n; ++i) {
        int l = 0, r = tp1, mid;
        while (l < r) {
            mid = l + (r - l) / 2;
            if (lnis[mid] < h[i]) 
                r = mid;
            else 
                l = mid + 1;
        }
        if (l != tp1) 
            lnis[l] = h[i];
        else
            lnis[tp1++] = h[i];
    }
    lis[tp2++] = h[0];
    for (int i = 1; i < n; ++i) {
        int l = 0, r = tp2, mid;
        while (l < r) {
            mid = l + (r - l) / 2;
            if (lis[mid] >= h[i]) 
                r = mid;
            else
                l = mid + 1;
        }
        if (l != tp2) 
            lis[l] = h[i];
        else
            lis[tp2++] = h[i];
    }
    printf("%d\n%d\n", tp1, tp2);
    return 0;
}