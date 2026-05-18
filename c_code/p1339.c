#include <stdio.h>
#include <string.h>

#define MAXN 5

int n, a[MAXN][MAXN], r[MAXN][MAXN], s[MAXN][MAXN], t[MAXN][MAXN];
int tmp[MAXN][MAXN];

void get_r() 
{
    memcpy(r, a, sizeof(r));
    for (int i = 0; i < n; ++i) 
        r[i][i] = 1;
}

void get_s() 
{
    memcpy(s, a, sizeof(s));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (a[i][j] == 1 &&a[j][i] != 1) 
                s[j][i] = 1;
        }
    }
}

void get_t() 
{
    memcpy(t, a, sizeof(t));
    memset(tmp, 0, sizeof(tmp));
    while (memcmp(t, tmp, sizeof(t)) != 0) {
        memcpy(tmp, t, sizeof(tmp));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                for (int k = 0; k < n; ++k) {
                    if (t[i][k] && t[k][j] && !t[i][j]) 
                        t[i][j] = 1;
                }
            }
        }
    }
}

void print_matrix(int m[MAXN][MAXN]) 
{
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) 
            printf("%d ", m[i][j]);
        printf("\n");
    }
}

int main() 
{
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            scanf("%d", &a[i][j]);
        }
    }
    get_r();
    get_s();
    get_t();
    printf("Reflexive Closure:\n");
    print_matrix(r);
    printf("Symmetric Closure:\n");
    print_matrix(s);
    printf("Transitive Closure:\n");
    print_matrix(t);
    return 0;
}