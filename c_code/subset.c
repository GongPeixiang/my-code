#include <stdio.h>

#define MAXN 25

int n, num[MAXN], a[MAXN], cnt = 0;

/* 方法一
void dfs(int dep) {
    if (dep == n) {
        if (!cnt) return;
        for (int i = 0; i < cnt; ++i) 
            printf("%d ", a[i]);
        putchar('\n');
        return;
    }

    dfs(dep + 1);

    a[cnt++] = num[dep];
    dfs(dep + 1);
    --cnt;
}*/

// 方法二
void dfs(int s, int cnt) {
    if (cnt) {
        for (int i = 0; i < cnt; ++i) 
            printf("%d ", a[i]);
        putchar('\n');
    }
    for (int i = s; i < n; ++i) {
        a[cnt] = num[i];
        dfs(i + 1, cnt + 1);
    }
}

// 方法三: 位运算

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) scanf("%d", &num[i]);
    dfs(0, 0);
    return 0;
}