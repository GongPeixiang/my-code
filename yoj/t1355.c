#include <stdio.h>
#include <stdlib.h>

typedef long long ll;
#define MAXN 20005

int n;
struct Seg {
    ll l, r;
} seg[MAXN];

int cmp(const void *a, const void *b) 
{
    struct Seg *sa = (struct Seg *)a, *sb = (struct Seg *)b;
    if (sa->l != sb->l) 
        return sa->l < sb->l ? -1 : 1;
    return sa->r < sb->r ? -1 : (sa->r > sb->r);
}

int main() 
{
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) 
        scanf(" %lld %lld", &seg[i].l, &seg[i].r);
    qsort(seg, n, sizeof(struct Seg), cmp);
    int st = seg[0].l, id = 0;
    ll res = 0;
    while (id < n) {
        st = (seg[id].l >= st) ? seg[id].l : st;
        if (seg[id].r > st) {
            res += seg[id].r - st;
            st = seg[id].r;
        }
        ++id;
    }
    printf("%lld\n", res);
    return 0;
}