#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 20005;
using ll = long long;

int n, ans = 0;
struct Segment {
    ll l, r;
} seg[MAXN];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for (int i = 0; i < n; i++) 
        cin >> seg[i].l >> seg[i].r;
    sort(seg, seg + n, [](const Segment &a, const Segment &b) {
        return a.l < b.l;
    });
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
    cout << res << '\n';
    return 0;
}