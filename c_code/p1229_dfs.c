#include <stdio.h>
#include <string.h>

#define MAXLEN 256

int n;
char pre[MAXLEN + 1], post[MAXLEN + 1];

int dfs(int al, int ar, int bl, int br) 
{
    if (al >= ar) 
        return 1;
    char lr = pre[al + 1];
    int pos = strchr(post, lr) - post;
    int left_size = pos - bl + 1;
    if (left_size == ar - al) 
        return 2 * dfs(al + 1, ar, bl, br - 1);
    else { // 左右子树都存在
        int lcnt = dfs(al + 1, al + left_size, bl, pos);
        int rcnt = dfs(al + left_size + 1, ar, pos + 1, br - 1);
        return lcnt * rcnt;
    }
}

int main() 
{
    scanf(" %s %s", pre, post);
    n = strlen(pre);
    int ans = dfs(0, n - 1, 0, n - 1);
    printf("%d\n", ans);
    return 0;
}