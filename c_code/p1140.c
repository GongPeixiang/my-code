#include <stdio.h>
#include <string.h>

#define LEN 105

char str1[LEN], str2[LEN];
int l1, l2, a[LEN], b[LEN], dp[LEN][LEN];

int table[5][5] = {
    {5, -1, -2, -1, -3},
    {-1, 5, -3, -2, -4},
    {-2, -3, 5, -2, -2},
    {-1, -2, -2, 5, -1},
    {-3, -4, -2, -1, (int)1e8}
};

#define max(a, b) ((a) > (b) ? (a) : (b))

void preprocess()
{
    for (int i = 0; i < l1; ++i) {
        switch (str1[i]) {
            case 'A': a[i] = 0;break;
            case 'C': a[i] = 1; break;
            case 'G': a[i] = 2; break;
	        case 'T': a[i] = 3; break;
            default: a[i] = 4; break;
        }
    }
    for (int i = 0; i < l2; ++i) {
        switch (str2[i]) {
            case 'A': b[i] = 0; break;
            case 'C': b[i] = 1; break;
	        case 'G': b[i] = 2; break;
            case 'T': b[i] = 3; break;
            default: b[i] = 4; break;  
        }
    }        
}

int solve()
{
    // dp[i][j]表示a的前i个碱基和b的前j个碱基的最大相似度
    memset(dp, 0, sizeof(dp));
    for (int i = 1; i <= l1; ++i) 
    	dp[i][0] = dp[i-1][0] + table[a[i-1]][4];
    for (int j = 1; j <= l2; ++j) 
        dp[0][j] = dp[0][j-1] + table[b[j-1]][4];
    for (int i = 1; i <= l1; ++i) {
        for (int j = 1; j <= l2; ++j) {
            int ai = a[i-1], bj = b[j-1];
	        dp[i][j] = max(dp[i-1][j-1] + table[ai][bj], max(dp[i][j-1] + table[4][bj], dp[i-1][j] + table[ai][4]));
        }
    }
    return dp[l1][l2];
}

int main()
{
    scanf(" %d %s", &l1, str1);
    scanf(" %d %s", &l2, str2);
    preprocess();
    int ans = solve();
    printf("%d\n", ans);
    return 0;
}