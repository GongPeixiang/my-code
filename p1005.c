#include <stdio.h>
#include <string.h>

#define MAXN 80
#define MAXL 1000

int n, m;
char matrix[MAXN][MAXN][20];
char dp[MAXN][MAXN][MAXL + 5], ans[MAXL + 5];

// 高精度
int res[MAXL + 5];
char result[MAXL + 5], tmp1[MAXL + 5], tmp2[MAXL + 5];
char zero[2] = {'0', '\0'}, two[2] = {'2', '\0'}, powtab[MAXN + 5][MAXL + 5];

void multiply(char *a, char *b) 
{
    memset(res, 0, sizeof(res));
    if (strcmp(a, zero) == 0 || strcmp(b, zero) == 0) {
        strcpy(result, zero);
        return;
    }
    int la = strlen(a), lb = strlen(b);
    int len = la + lb;
    for (int i = la - 1; i >= 0; --i) {;
        for (int j = lb - 1; j >= 0; --j) {
            int x = a[i] - '0', y = b[j] - '0';
            res[i + j + 1] += x * y;
        }
    }
    for (int i = len - 1; i > 0; --i) {
        if (res[i] >= 10) {
            res[i - 1] += res[i] / 10;
            res[i] %= 10;
        }
    }
    int i = 0, cnt = 0;
    while (res[i] == 0) ++i;
    for (; i < len; ++i) 
        result[cnt++] = (char)(res[i] + '0');
    result[cnt] = '\0';
}

void add(char *a, char *b) 
{
    memset(res, 0, sizeof(res));
    int la = strlen(a), lb = strlen(b);
    int len = la > lb ? la : lb;
    int i = la - 1, j = lb - 1, k = len - 1;
    int carry = 0;
    while (k >= 0) {
        int x = i >= 0 ? a[i] - '0' : 0;
        int y = j >= 0 ? b[j] - '0' : 0;
        int tmp = x + y + carry;
        res[k] = tmp % 10;
        carry = tmp / 10;
        --i, --j, --k;
    }
    int cnt = 0;
    if (carry) 
        result[cnt++] = '1' ;
    for (int i = 0; i < len; ++i) 
        result[cnt++] = (char)(res[i] + '0');
    result[cnt] = '\0';
}

void get_max(char a[MAXL + 5], char b[MAXL + 5]) 
{
    int la = strlen(a), lb = strlen(b);
    if (la == lb) {
        int flg = strcmp(a, b);
        if (flg < 0) strcpy(result, b);
        else strcpy(result, a);
        return;
    }
    if (la < lb) strcpy(result, b);
    else strcpy(result, a);
}

void get_pow2() 
{
    powtab[0][0] = '1', powtab[0][1] = '\0';
    for (int i = 1; i <= m; ++i) {
        multiply(powtab[i - 1], two);
        strcpy(powtab[i], result);
    }
}

void solve() 
{
    get_pow2();
    //for (int i = 0; i <= m; ++i) 
        //printf("%s\n", powtab[i]);
    strcpy(ans, zero);
    for (int r = 0; r < n; ++r) {
        memset(dp, '\0', sizeof(dp));
        for (int i = 0; i < m; ++i) {
            multiply(matrix[r][i], powtab[m]);
            strcpy(dp[i][i], result);
            //printf("dp[%d][%d] = %s\n", i, i, dp[i][i]);
        }
        for (int len = 2; len <= m; ++len) {
            for (int i = 0; i + len - 1 < m; ++i) {
                int j = i + len - 1;
                multiply(powtab[m - len + 1], matrix[r][j]);
                add(dp[i][j - 1], result);
                strcpy(tmp1, result);  // 暂存

                multiply(powtab[m - len + 1], matrix[r][i]);
                add(dp[i + 1][j], result);
                strcpy(tmp2, result);

                //printf("tmp1 = %s, tmp2 = %s\n", tmp1, tmp2);
                get_max(tmp1, tmp2);
                strcpy(dp[i][j], result);
                //printf("dp[%d][%d] = %s\n", i, j, dp[i][j]);
            }
        }
        add(ans, dp[0][m - 1]);
        //printf("Row %d: dp[0][%d] = %s\n", r, m-1, dp[0][m-1]);
        strcpy(ans, result);
    }
}

int main() 
{
    scanf(" %d %d", &n, &m);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            scanf(" %s", &matrix[i][j]);
        }
    }
    solve();
    printf("%s\n", ans);
    return 0;
}