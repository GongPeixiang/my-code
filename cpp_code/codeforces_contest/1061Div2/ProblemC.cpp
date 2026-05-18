#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    int ans = 1;
    for (int d = n; d >= 1; d--) {
        vector<int> cnt(n + 1, 0);
        for (int i = 0; i < n; i++) {
            if (a[i] <= n) {
                cnt[a[i]]++;
            }
        }
        
        int multiples = 0;
        int can_split = 0;
        
        for (int v = 1; v <= n; v++) {
            if (cnt[v] == 0) continue;
            if (v % d == 0) {
                multiples += cnt[v];
            } else if (v >= 2 * d) {
                can_split += cnt[v];
            }
        }
        
        if (n - multiples - can_split <= k) {
            ans = d;
            break;
        }
    }
    
    cout << ans << endl;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}