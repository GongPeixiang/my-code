#include <stdio.h>
#include <string.h>

#define MAXM 10

int m, n, a[MAXM][MAXM], res[MAXM][MAXM], tmp[MAXM][MAXM];

void init() 
{
    memset(res, 0, sizeof(res));
    for (int i = 0; i < m; ++i) 
        res[i][i] = 1;
}

void multi(int x[MAXM][MAXM], int y[MAXM][MAXM], int result[MAXM][MAXM]) 
{
    memset(tmp, 0, sizeof(tmp));
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < m; ++j) {
            for (int k = 0; k < m; ++k) {
                if (x[i][k] && y[k][j]) {
                    tmp[i][j] = 1;
                    break;
                }
            }
        }
    }
    memcpy(result, tmp, sizeof(tmp));
}

void qpow() 
{
    init();
    while (n > 0) {
        if (n & 1) 
            multi(res, a, res);  // res = res * base
        multi(a, a, a);          // base = base * base
        n >>= 1;
    }
}

int main() 
{
    scanf("%d %d", &m, &n);
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < m; ++j) {
            scanf(" %d", &a[i][j]);
        }
    }
    qpow();
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < m; ++j) 
            printf("%d ", res[i][j]);
        printf("\n");
    }
    return 0;
}