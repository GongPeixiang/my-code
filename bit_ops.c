#include <stdio.h>
#include <stdbool.h>

typedef long long ll;

// 最低位的1所在位的权值
static inline int lowbit(int x) { return x & -x; }

int cnt_bit(int x) 
{
    int res = 0;
    while (x) {
        x -= lowbit(x);
        ++res;
    }
    return res;
}

static inline bool kth_bit_one(ll x, int k) { return (x >> k) & 1ll; }

static inline ll set_kth_bit(ll x, int k) { return x | (1ll << k); }

static inline ll clear_kth_bit(ll x, int k) { return x & ~(1ll << k); }