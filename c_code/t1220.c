#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXN 20
#define MAXL 20

int n;
char word[MAXN * 2][MAXL + 5], beg;
char ans[2 * MAXN * MAXL + 5];
bool vis[MAXN * 2];

char *get_sub(char a[MAXL + 5], int s, int l) 
{
    char *ret = (char *)malloc(l + 1);
    if (!ret) exit(1);
    char *p = a + s;
    int cnt = 0;
    while (cnt < l) 
        ret[cnt++] = *p++;
    ret[cnt] = '\0';
    return ret;
}

bool check(char b[MAXL + 5], int *k)
{
    int la = strlen(ans), lb = strlen(b);
    if (la < lb && strcmp(ans, b) == 0)
        return false;
    *k = -1;
    int max_l = (la < lb ? la - 1 : lb - 1);
    for (int cnt = max_l; cnt >= 1; --cnt) { 
        // 从大到小找最大重叠
        char *sa = get_sub(ans, la - cnt, cnt);
        char *sb = get_sub(b, 0, cnt);
        if (strcmp(sa, sb) == 0) {
            *k = cnt;
            free(sa), free(sb);
            return true;
        }
        free(sa), free(sb);
    }
    return false;
}

void cat(char b[MAXL + 5], int k)
{
    int lb = strlen(b);
    char *tmp = get_sub(b, k, lb - k);
    strcat(ans, tmp);
    free(tmp);
}

void decat(char b[MAXL + 5], int k) 
{
    int lb = strlen(b), la = strlen(ans);
    ans[la - lb + k] = '\0';
}

int dfs(int cur) 
{
    int len = strlen(ans);
    for (int i = 0; i < 2 * n; ++i) {
        int k;
        if (!vis[i] && check(word[i], &k)) {
            vis[i] = true;
            cat(word[i], k);
            int tmp = dfs(i);
            len = tmp > len ? tmp : len;
            decat(word[i], k);
            vis[i] = false;
        }
    }
    return len;
}

int main() 
{
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf(" %s", &word[2 * i]);
        strcpy(word[2 * i + 1], word[2 * i]);
    }
    scanf(" %c", &beg);
    int max_len = -1;
    for (int i = 0; i < 2 * n; ++i) {
        if (word[i][0] != beg) 
            continue;
        strcpy(ans, word[i]);
        memset(vis, 0, sizeof(vis));
        vis[i] = true;
        int tmp = dfs(i);
        max_len = max_len > tmp ? max_len : tmp;
    }
    printf("%d\n", max_len);
    return 0;
}