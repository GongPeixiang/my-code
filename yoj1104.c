#include <stdio.h>
#include <string.h>

#define MAXN 205
#define MAXK 10

int N, K, f[MAXN][MAXK];

int main() 
{
    memset(f, 0, sizeof(f));
    scanf(" %d %d", &N, &K);
    f[1][1] = 1;
    for (int i = 2; i <= N; ++i) {
        for (int j = 1; j <= i && j <= K; ++j) {
            f[i][j] = f[i-j][j] + f[i-1][j-1];
        }
    }
    printf("%d\n", f[N][K]);
    return 0;
}