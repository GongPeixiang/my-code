#include <bits/stdc++.h>
using namespace std;

constexpr int N = 5005;

int n, x[N], y[N];
bool v[N];
struct Node {
    int rk;
    int l, r;
    bool operator<(const Node& other) const {
        if (r != other.r) return r < other.r;
        return l < other.l;
    }
} xcord[N], ycord[N];

bool calc(Node a[N], int ans[N]) {
    for (int i = 0; i < n; i++) {
        int r = a[i].l;
        while (v[r] && r <= a[i].r) r++;
        if (r == a[i].r + 1) return false;
        ans[a[i].rk] = r;
        v[r] = true;
    }
    return true;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    while (cin >> n && n) {
        for (int i = 0; i < n; i++) {
            xcord[i].rk = ycord[i].rk = i;
            cin >> xcord[i].l >> ycord[i].l >> xcord[i].r >> ycord[i].r;
        }
        sort(xcord, xcord + n);
        sort(ycord, ycord + n);
        memset(v, 0, sizeof(v));
        bool flg = calc(xcord, x);
        memset(v, 0, sizeof(v));
        flg &= calc(ycord, y);
        if (!flg) cout << "IMPOSSIBLE\n";
        else 
            for (int i = 0; i < n; i++) cout << x[i] << ' ' << y[i] << '\n';
    }
    return 0;
}