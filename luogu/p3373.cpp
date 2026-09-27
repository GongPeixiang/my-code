#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 100005;

int n, mod, a[N];
struct Node { // segment tree
    ll sum, add, mul;
    int l, r;
} s[4*N];

inline void pull(int p) { s[p].sum = (s[p<<1].sum + s[(p<<1)|1].sum) % mod; }

void push(int p) {
    int l = p<<1, r = (p<<1)|1;
    s[l].sum = (s[l].sum * s[p].mul + s[p].add * (s[l].r-s[l].l+1)) % mod;
    s[r].sum = (s[r].sum * s[p].mul + s[p].add * (s[r].r-s[r].l+1)) % mod;
    s[l].mul = (s[l].mul * s[p].mul) % mod;
    s[r].mul = (s[r].mul * s[p].mul) % mod;
    s[l].add = (s[l].add * s[p].mul + s[p].add) % mod;
    s[r].add = (s[r].add * s[p].mul + s[p].add) % mod;
    s[p].add = 0;
    s[p].mul = 1;
}

void build(int p, int l, int r) {
    s[p].l = l; s[p].r = r;
    s[p].mul = 1; s[p].add = 0;
    if (l == r) {
        s[p].sum = a[l];
        return;
    }
    int mid = l + ((r-l)>>1);
    build(p<<1, l, mid);
    build((p<<1)|1, mid + 1, r);
    pull(p);
}

void rng_mul(int p, int l, int r, int k) {
    if (s[p].l >= l && s[p].r <= r) {
        s[p].add = (s[p].add * k) % mod;
        s[p].mul = (s[p].mul * k) % mod;
        s[p].sum = (s[p].sum * k) % mod;
        return;
    }
    push(p);
    int mid = s[p].l + ((s[p].r-s[p].l)>>1);
    if (l <= mid) rng_mul(p<<1, l, r, k);
    if (r > mid) rng_mul((p<<1)|1, l, r, k);
    pull(p);
}

void rng_add(int p, int l, int r, int k) {
    if (s[p].l >= l && s[p].r <= r) {
        s[p].add = (s[p].add + k) % mod;
        s[p].sum = (s[p].sum + k * (s[p].r-s[p].l+1)) % mod;
        return;
    }
    push(p);
    int mid = s[p].l + ((s[p].r-s[p].l)>>1);
    if (l <= mid) rng_add(p<<1, l, r, k);
    if (r > mid) rng_add((p<<1)|1, l, r, k);
    pull(p);
}

ll get_sum(int p, int l, int r) {
    if (s[p].l >= l && s[p].r <= r) return s[p].sum;
    push(p);
    ll val = 0;
    int mid = s[p].l + ((s[p].r-s[p].l)>>1);
    if (l <= mid) val = (val + get_sum(p<<1, l, r)) % mod;
    if (r > mid) val = (val + get_sum((p<<1)|1, l ,r)) % mod;
    return val;
}

int main() {
    int T;
    scanf("%d%d%d", &n, &T, &mod);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    build(1, 1, n);
    int op, x, y, k;
    while (T--) {
        scanf("%d%d%d", &op, &x, &y);
        if (op == 3) printf("%lld\n", get_sum(1, x, y));
        else {
            scanf("%d", &k);
            if (op == 1) rng_mul(1, x, y, k);
            else if (op == 2) rng_add(1, x, y, k);
        }
    }
    return 0;
}