#include <stdio.h>
#include <stdbool.h>
#include <math.h>  // 编译加 -lm

#define MAXN 40
#define MAXSUM 1600

int n, len[MAXN], sum = 0;
bool dp[MAXSUM / 2 + 1][MAXSUM / 2 + 1];

static inline bool check(int a, int b, int c) 
{
    return a + b > c && a + c > b && b + c > a;
}

static inline double area(double a, double b, double c) 
{
    double p = (a + b + c) / 2;
    return sqrt(p * (p-a) * (p-b) * (p-c));
}

double solve() 
{
    dp[0][0] = true;
    for (int k = 1; k <= n; ++k) {
        int lk = len[k - 1];
        for (int i = sum / 2; i >= 0; --i) {
            for (int j = sum / 2; j >= 0; --j) {
                if (i >= lk) 
                    dp[i][j] |= dp[i - lk][j];
                if (j >= lk) 
                    dp[i][j] |= dp[i][j - lk];
            }
        }
    }
    double max_area = -1;
    for (int i = sum / 2; i >= 0; --i) {
        for (int j = sum / 2; j >= 0; --j) {
            if (dp[i][j] && check(i, j, sum - i - j)) {
                double tmp = area(i, j, sum - i - j);
                max_area = tmp > max_area ? tmp : max_area;
            }
        }
    }
    return max_area;
}

int main() 
{
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf(" %d", &len[i]);
        sum += len[i];
    }
    double tmp;
    int ans = (tmp = solve()) != -1 ? (int)(tmp * 100) : -1;
    printf("%d\n", ans);
    return 0;
}