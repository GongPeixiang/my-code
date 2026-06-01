#include <bits/stdc++.h>
using namespace std;

bool solve(int &w) {
    int w1, d1, w2, d2;
    cin >> w1 >> d1 >> w2 >> d2;
    bool b1 = true, b2 = true;
    if (!w1) b1 = solve(w1);
    if (!w2) b2 = solve(w2);
    w = w1 + w2;
    return b1 && b2 && (w1 * d1 == w2 * d2);
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int T, w;
    cin >> T;
    while (T--) {
        if (solve(w)) cout << "YES\n";
        else cout << "NO\n";
        if (T) cout << '\n';
    }
    return 0;
}