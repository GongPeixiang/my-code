// 集合划分问题
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXN 15
#define MAXCNT 678570 // B11, 第11个贝尔数

int n, rgs[MAXN], cnt = 0;
char str[MAXN], res[MAXCNT][2 * MAXN], tmp[2 * MAXN];

void dfs(int pos, int part) 
{
    if (pos == n) {
        memset(tmp, 0, sizeof(tmp));
        int tp = 0;
        for (int k = 0; k <= part; ++k) {
            for (int i = 0; i < n; ++i) {
                if (rgs[i] == k) 
                    tmp[tp++] = str[i];
            }
            if (k < part) tmp[tp++] = '0';
        }
        tmp[tp] = '\0';
        strcpy(res[cnt++], tmp);
        return;
    }
    for (int i = 0; i <= part; ++i) {
        rgs[pos] = i;
        dfs(pos + 1, part);
    }
    rgs[pos] = part + 1;
    dfs(pos + 1, part + 1);
}

int cmp(const void *a, const void *b) 
{
    return strcmp((const char *)a, (const char *)b);
}

int main() 
{
    scanf(" %s", str);
    n = strlen(str);
    memset(rgs, 0xff, sizeof(rgs));
    rgs[0] = 0; // 必须rgs[0] = 0
    dfs(1, 0);
    qsort(res, cnt, sizeof(res[0]), cmp);
    printf("%d\n", cnt);
    for (int i = 0; i < cnt; ++i) 
        printf("%s\n", res[i]);
    return 0;
}