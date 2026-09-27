// segment tree
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 100005;

int n;
ll a[N], sum[4*N], laz[4*N];

void build(int l, int r, int p) {
    if (l == r) { 
        sum[p] = a[l]; 
        return; 
    }
    int mid = l + ((r-l)>>1);
    build(l, mid, p<<1);
    build(mid + 1, r, (p<<1)|1);
    sum[p] = sum[p<<1] + sum[(p<<1)|1];
}

void update(int l, int r, int s, int t, int p, ll c) {
    if (s >= l && t <= r) {
        sum[p] += (t - s + 1) * c;
        laz[p] += c;
        return;
    }
    int mid = s + ((t-s)>>1);
    if (laz[p]) {
        sum[p<<1] += laz[p] * (mid - s + 1);
        sum[(p<<1)|1] += laz[p] * (t - mid);
        laz[p<<1] += laz[p];
        laz[(p<<1)|1] += laz[p];
    }
    laz[p] = 0;
    if (l <= mid) update(l, r, s, mid, p<<1, c);
    if (r > mid) update(l, r, mid + 1, t, (p<<1)|1, c);
    sum[p] = sum[p<<1] + sum[(p<<1)|1];
}

ll get_sum(int l, int r, int s, int t, int p) {
    if (s >= l && t <= r) return sum[p];
    int mid = s + ((t-s)>>1);
    if (laz[p]) {
        sum[p<<1] += laz[p] * (mid - s + 1);
        sum[(p<<1)|1] += laz[p] * (t - mid);
        laz[p<<1] += laz[p];
        laz[(p<<1)|1] += laz[p];
    }
    laz[p] = 0;
    ll res = 0;
    if (l <= mid) res += get_sum(l, r, s, mid, p<<1);
    if (r > mid) res += get_sum(l, r, mid + 1, t, (p<<1)|1);
    return res;
}

int main() {
    int T;
    scanf("%d%d", &n, &T);
    for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
    build(1, n, 1);
    int i1, i2, i3, i4;
    while (T--) {
        scanf("%d%d%d", &i1, &i2, &i3);
        if (i1 == 1) {
            scanf("%d", &i4);
            update(i2, i3, 1, n, 1, i4);
        } else {
            ll ans = get_sum(i2, i3, 1, n, 1);
            printf("%lld\n", ans);
        }
    }
    return 0;
}