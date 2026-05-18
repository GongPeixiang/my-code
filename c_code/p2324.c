#include <stdio.h>
#include <stdbool.h>

int num[4], path[3][3];
char op[3];

static inline void swap(int *a, int *b) 
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

bool dfs(int dep) 
{
    if (dep == 3) 
        return path[2][2] == 24;
    int ni, nj;
    int a, b, res;
    for (int i = 0; i < 4; ++i) {
        for (int j = i + 1; j < 4; ++j) {
            if (num[i] == -1 || num[j] == -1) 
                continue;
            a = ni = num[i], b = nj = num[j];
            if (b > a) 
                swap(&a, &b);
            
            res = a + b;
            op[dep] = '+';
            num[i] = res, num[j] = -1;
            path[dep][0] = a, path[dep][1] = b, path[dep][2] = res;
            if (dfs(dep + 1)) 
                return true;
            num[i] = ni, num[j] = nj;
            
            res = a - b;
            op[dep] = '-';
            num[i] = res, num[j] = -1;
            path[dep][0] = a, path[dep][1] = b, path[dep][2] = res;
            if (dfs(dep + 1)) 
                return true;
            num[i] = ni, num[j] = nj;

            res = a * b;
            op[dep] = '*';
            num[i] = res, num[j] = -1;
            path[dep][0] = a, path[dep][1] = b, path[dep][2] = res;
            if (dfs(dep + 1)) 
                return true;
            num[i] = ni, num[j] = nj;

            if (b && a % b == 0) {
                res = a / b;
                op[dep] = '/';
                num[i] = res, num[j] = -1;
                path[dep][0] = a, path[dep][1] = b, path[dep][2] = res;
                if (dfs(dep + 1)) 
                    return true;
                num[i] = ni, num[j] = nj;
            } 
        }
    }
    return false;
}

int main()
{
    for (int i = 0; i < 4; ++i) 
        scanf("%d", &num[i]);
    bool flg = dfs(0);
    if (flg) {
        for (int i = 0; i < 3; ++i) 
            printf("%d%c%d=%d\n", 
                path[i][0], op[i], path[i][1], path[i][2]);
    } else
        printf("No answer!\n");
    return 0;
}