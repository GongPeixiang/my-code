#include <stdio.h>
#include <stdbool.h>

#define MAXN 55

int n, table[MAXN][MAXN];

int main() 
{
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            scanf("%d", &table[i][j]);
        }
    }
    bool flg[2] = {true, true};
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                int res1 = table[table[i][j]][k];
                int res2 = table[i][table[j][k]];
                if (res1 != res2) {
                    flg[0] = false;
                    break;
                }
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (table[i][j] != table[j][i]) {
                flg[1] = false;
                break;
            }
        }
    }
    int one = -1;
    for (int i = 0; i < n; ++i) {
        bool isone = true;
        for (int j = 0; j < n; ++j) {
            if (table[i][j] != j || table[j][i] != j) {
                isone = false;
                break;
            }
        }
        if (isone) 
            one = i;
    }
    printf("ASSOCIATIVE: %s\n", flg[0] ? "YES": "NO");
    printf("COMMUTATIVE: %s\n", flg[1] ? "YES": "NO");
    if (~one)
        printf("IDENTITY: %d\n", one);
    else 
        printf("IDENTITY: NONE\n");
    return 0;
}