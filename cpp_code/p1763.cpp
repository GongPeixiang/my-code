#include <bits/stdc++.h>
using namespace std;

using ll = long long;
constexpr int MAXD = 1000005;

int maxdep, cur[MAXD], ans[MAXD];

ll gcd(ll x, ll y) { return y ? gcd(y, x % y) : x; }

bool check() {
    for (int i = maxdep - 1; i >= 0; --i) 
        if (cur[i] != ans[i]) return ans[i] == -1 || cur[i] < ans[i];
    return false;
}

bool dfs(ll aa, ll bb, int from, int dep) {
    if (dep == maxdep - 1) {
        if (bb % aa) return false;
        cur[dep] = bb / aa;
        if (check()) memcpy(ans, cur, sizeof(int) * maxdep);
        return true;
    }
    bool flg = false;
    int s = max(from, (int)ceil((double)bb/(double)aa));
    for (int i = s; ; ++i) {
        if (i * aa >= (maxdep - dep) * bb) break;
        cur[dep] = i;
        ll na = aa * i - bb, nb = bb * i;
        ll g = gcd(na, nb);
        if (dfs(na/g, nb/g, i + 1, dep + 1)) flg = true;
    }
    return flg;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    ll a, b;
    cin >> a >> b;
    ll g = gcd(a, b);
    a /= g, b /= g;
    for (maxdep = 2; ; ++maxdep) {
        memset(ans, 0xff, sizeof(ans));
        if (dfs(a, b, (int)ceil(b/a), 0)) {
            // sort(ans, ans + maxdep);
            for (int i = 0; i < maxdep; ++i) cout << ans[i] << " \n"[i == maxdep-1];
            return 0;
        }
    }
    return 0;
}