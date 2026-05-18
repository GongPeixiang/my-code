#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXN 20
#define MAXL 20

int n, max_len = 0;
char word[MAXN * 2][MAXL + 5], beg, ans[2 * MAXN * MAXL + 5];
char final[2 * MAXN * MAXL + 5];
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

int check(char b[MAXL + 5]) 
{
    int la = strlen(ans), lb = strlen(b);
    int len = la > lb ? lb : la;
    for (int i = 1; i <= len - 1; ++i) {
        char *as = get_sub(ans, la - i, i);
        char *bs = get_sub(b, 0, i);
        int flg = strcmp(as, bs);
        if (flg == 0) 
            return i;
    }
    return -1;
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

void dfs() 
{
    int l = strlen(ans);
    if (l > max_len) {
        max_len = l;
        strcpy(final, ans);
    }
    for (int i = 0; i < 2 * n; ++i) {
        int k = check(word[i]);
        if (!vis[i] && k != -1) {
            vis[i] = true;
            cat(word[i], k);
            dfs();
            decat(word[i], k);
            vis[i] = false;
        }
    }
}

int main() 
{
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf(" %s", &word[2 * i]);
        strcpy(word[2 * i + 1], word[2 * i]);
    }
    scanf(" %c", &beg);
    for (int i = 0; i < 2 * n; ++i) {
        if (word[i][0] != beg) 
            continue;
        strcpy(ans, word[i]);
        memset(vis, 0, sizeof(vis));
        vis[i] = true;
        dfs();
    }
    printf("%d\n", max_len);
    //printf("%s\n", final);
    return 0;
}