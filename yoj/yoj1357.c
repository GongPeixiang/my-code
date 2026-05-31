#include <stdio.h>
#include <stdbool.h>

#define MAXN 15

int n, a[MAXN];

bool check1(int i, int j) 
{
    for (int k = i + 1; k < j; ++k) {
        if (a[j] % a[k] == 0 && a[k] % a[i] == 0) 
            return false;
    }
    return true;
}

bool check(int i, int j) 
{
    bool l = false, r = false;
    for (int k = 0; k < n; ++k) {
        if (a[k] % a[i] == 0 && a[k] % a[j] == 0) 
            r = true;
        if (a[i] % a[k] == 0 && a[j] % a[k] == 0) 
            l = true;
    }
    return r && l;
}

int main() 
{
    scanf(" %d", &n);
    for (int i = 0; i < n; ++i) 
        scanf(" %d", &a[i]);
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (a[j] % a[i] == 0 && check1(i, j)) {
                printf("(%d,%d) ", a[i], a[j]);
            }
        }
    }
    printf("\n");
    bool flg = true;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (!check(i, j)) 
                flg = false;
        }
    }
    printf("%s\n", flg ? "YES" : "NO");
    return 0;
}