#include <stdio.h>
#include <string.h>

#define MAXN 1000

int n, num[MAXN], tmp[MAXN];

void merge(int l, int mid, int r) 
{
    memset(tmp, 0, sizeof(tmp));
    int i = l, j = mid + 1, k = 0;  //三指针
    while (i <= mid && j <= r) {
        if (num[i] < num[j]) 
            tmp[k++] = num[i++];
        else    
            tmp[k++] = num[j++];
    }
    while (i <= mid) 
        tmp[k++] = num[i++];
    while (j <= r) 
        tmp[k++] = num[j++];
    // 合并
    for (i = l, j = 0; i <= r; ++i) 
        num[i] = tmp[j++];
}

void msort(int l, int r) 
{
    if (l >= r) 
        return;
    int mid = l + (r - l) / 2;
    msort(l, mid);
    msort(mid + 1, r);
    merge(l, mid, r);
}

int main() 
{
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) 
        scanf("%d", &num[i]);
    msort(0, n - 1);
    for (int i = 0; i < n; ++i) 
        printf("%d ", num[i]);
    return 0;
}