#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 105;

int n;
double x[MAXN*2];
struct Build {
    int id;
    double x, y, w, d, h;
} bd[MAXN];

inline bool cover(int i, double mx) {
    return bd[i].x <= mx && bd[i].x + bd[i].w >= mx;
}

bool visible(int i, double mx) {
    if (!cover(i, mx)) return false;
    for (int k = 0; k < n; ++k) {
        if (bd[k].y < bd[i].y && bd[k].h >= bd[i].h && cover(k, mx)) 
            return false;
    }
    return true;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int T = 0; //case是cpp关键字
    while (cin >> n && n) {
        for (int i = 0; i < n; ++i) {
            bd[i].id = i + 1;
            cin >> bd[i].x >> bd[i].y >> bd[i].w >> bd[i].d >> bd[i].h;
            x[i*2] = bd[i].x; x[i*2+1] = bd[i].x + bd[i].w;
        }
        sort(bd, bd + n, [](const Build &a, const Build &b) {
            return a.x < b.x || a.x == b.x && a.y < b.y;
        });
        sort(x, x + 2*n);
        int m = unique(x, x + 2*n) - x;
        if (T++) cout << '\n';
        cout << "For map #" << T << ", the visible buildings are numbered as follows:\n" << bd[0].id;
        for (int i = 1; i < n; ++i) {
            bool flg = false;
            for (int j = 0; j < m - 1; ++j) {
                if (visible(i, (x[j] + x[j+1]) / 2)) {
                    flg = true;
                    break;
                }
            }
            if (flg) cout << ' ' << bd[i].id;
        }
        cout << '\n';
    }
    return 0;
}