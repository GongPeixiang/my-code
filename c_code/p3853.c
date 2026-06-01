#include <stdio.h>

#define MAXN 100000

int L, N, pos[MAXN];
int K, max_dis = -1;

_Bool check(int dis) {
    int cnt = 0;
    int cur = 0, nxt = 1;
    while (nxt < N) {
        int ds = pos[nxt] - pos[cur];
        if (ds > dis) 
            cnt += (ds - 1) / dis;
        ++cur, ++nxt;
    }
    return cnt <= K;
}

int main() {
    scanf(" %d %d %d", &L, &N, &K);
    for (int i = 0; i < N; ++i) {
        scanf(" %d", &pos[i]);
        if (i > 0) 
            max_dis = max_dis > (pos[i] - pos[i - 1]) ? max_dis : (pos[i] - pos[i - 1]);
    }
    int l = 1, r = max_dis;
    int ans;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (check(mid)) {
            ans = mid;
            r = mid - 1;
        }
        else 
            l = mid + 1;
    }
    printf("%d\n", ans);
    return 0;
}