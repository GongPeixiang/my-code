#include <stdio.h>
#include <stdbool.h>

#define MAXN 50005

int N, M, L;
int d[MAXN];

bool check(int len) 
{
    int cnt = 0;
    int cur = 0, nxt = 1;
    while (nxt < N + 1) {
        if (d[nxt] - d[cur] < len) ++cnt;
        else cur = nxt;
        ++nxt;    
    }
    return cnt <= M;
}

int main() 
{
    scanf("%d %d %d", &L, &N, &M);
    d[0] = 0, d[N + 1] = L;
    for (int i = 1; i <= N; ++i) scanf("%d", &d[i]);
    int l = 1, r = L;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (check(mid)) l = mid + 1;
        else r = mid - 1;
    }
    int ans = l - 1;
    printf("%d\n", ans);
    return 0;
}