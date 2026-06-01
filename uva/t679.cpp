#include <bits/stdc++.h>
using namespace std;

constexpr int MAXD = 20;

bool s[1 << MAXD];

/* int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, D, I;
    cin >> n;
    while (n--) {
        cin >> D >> I;
        memset(s, 0, sizeof(s));
        int k, n = (1 << D) - 1;
        for (int i = 0; i < I; ++i) {
            k = 1;
            while (1) {
                s[k] = !s[k];
                k = s[k] ? k * 2 : k * 2 + 1;
                if (k > n) break;
            }
        }
        cout << k/2 << '\n';
    }
    return 0;
} */

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, D, I;
    cin >> n;
    while (n--) {
        cin >> D >> I;
        memset(s, 0, sizeof(s));
        int k = 1;
        for (int i = 0; i < D - 1; ++i) {
            if (I%2) {
                k = k * 2;
                I = (I + 1) / 2;
            } else {
                k = k * 2 + 1;
                I /= 2;
            }
        }
        cout << k << '\n';
    }
    return 0;
}