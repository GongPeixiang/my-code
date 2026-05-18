#include <bits/stdc++.h>
using std::vector;

using ll = long long;
ll n, k;
vector<ll> len, cpy;

bool check(ll l) {
    ll need = 0;
    for (ll x : len) {
        if (x > l) {
            need += (x + l - 1) / l - 1;
            if (need > k) 
                return false;
        }
    }
    return need <= k;
}

ll solve() {
    ll left = 1, right = len.back();
    while (left < right) {
        ll mid = (left + right) / 2;
        if (check(mid))
            right = mid;
        else
            left = mid + 1;
    }
    return left;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cin >> n >> k;
    len.resize(n);
    for (int i = 0; i < n; ++i) 
        std::cin >> len[i];
    std::sort(len.begin(), len.end());
    ll ans = solve();
    std::cout << ans << '\n';
}