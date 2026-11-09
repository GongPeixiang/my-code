#include <bits/stdc++.h>
using namespace std;

const int N = 105;

int n, a[N], step = 0;

void recur(int s) {
    if (s == n) return;
    int p = s;
    for (int i = s+1; i <= n; i++) if (a[i] < a[p]) p = i;
    if (p == s) recur(s+1);
    else {
        swap(a[s], a[p]);
        step++;
        int tmp[N];
        memcpy(tmp, a, sizeof(a));
        recur(s+1);
        printf("%d<->%d:", s, p);
        for (int i = 1; i <= n; i++) printf("%d%c", tmp[i], " \n"[i==n]);
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    recur(1);
    printf("Total steps:%d\n", step);
    printf("Right order:");
    for (int i = 1; i <= n; i++) printf("%d%c", a[i], " \n"[i==n]);
    return 0;
}