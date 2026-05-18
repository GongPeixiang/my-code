#include <stdio.h>

int n, need[10] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};

// n <= 24
// 24 - 4 = 20, 20 / 2 = 10, 10 / 2 = 5
// 11111
#define MAXA 1111

int stick_cnt(int k) 
{
    if (k == 0) 
        return need[0];
    int cnt = 0, tmp;
    while (k > 0) {
        tmp = k % 10;
        cnt += need[tmp];
        k /= 10;
    }
    return cnt;
}

int main() 
{
    scanf(" %d", &n);
    int ans = 0;
    for (int a = 0; a < MAXA; ++a) {
        for (int b = 0; b < MAXA; ++b) {
            int c = a + b;
            int x = stick_cnt(a);
            int y = stick_cnt(b);
            int z = stick_cnt(c);
            if (x + y + z == n - 4) 
                ++ans;
        }
    }
    printf("%d\n", ans);
    return 0;
}