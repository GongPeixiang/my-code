#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define LEN 205
#define MAXK 45
#define MAXS 10

int N, K, s;
char str[LEN], dict[MAXS][LEN], tmp[LEN];
int f[LEN][MAXK], dp[LEN][LEN];

static inline int max(int a, int b) { return a > b ? a : b; }

void get_sub(int src, int l) 
{
    char *p = str + src;
    int cnt = 0;
    while (cnt < l) tmp[cnt++] = *(p++);
    tmp[cnt] = '\0';
}

void preprocess() 
{
    for (int i = 0; i < N; ++i) {
        get_sub(i, 1);
        for (int k = 0; k < s; ++k) {
            if (strcmp(tmp, dict[k]) == 0) dp[i][i] = 1;
        }
    }
    for (int len = 2; len <= N; ++len) {
        for (int i = 0; i + len - 1 < N; ++i) {
            int j = i + len - 1;
            dp[i][j] = dp[i+1][j];
            bool flg = false;
            for (int k = i; k <= j; ++k) {
                get_sub(i, k - i + 1);
                for (int l = 0; l < s; ++l) {
                    if (strcmp(tmp, dict[l]) == 0) {
                        ++dp[i][j];
                        flg = true;
                        break;
                    }
                }
                if (flg) break;
            }
        }
    }
}

int solve() 
{
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= K; ++j) {
            for (int l = j - 1; l < i; ++l) {
                f[i][j] = max(f[i][j], f[l][j-1] + dp[l][i-1]);
            }
        }
    }
    return f[N][K];
}

int main() 
{
    int p;
    scanf("%d %d", &p, &K);
    N = p * 20;
    for (int i = 0; i < p; ++i) 
        for (int j = 0; j < 20; ++j) 
            scanf(" %c", &str[i*20+j]);
    scanf("%d", &s);
    for (int i = 0; i < s; ++i) scanf(" %s", dict[i]);
    preprocess();
    int ans = solve();
    printf("%d\n", ans);
    return 0;
}