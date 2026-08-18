#include <bits/stdc++.h>
using namespace std;

constexpr int N = 35;

int n, cube[N][3];
bool ok[N][N][3][3];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int kase = 0, a[3];
    while (cin >> n && n) {
        kase++;
        memset(ok, 0, sizeof(ok));
        for (int i = 0; i < n; i++) {
            cin >> a[0] >> a[1] >> a[3];
            sort(a, a + 3);
            memcpy(cube[i], a, sizeof(cube[i]));
        }
        for (int i = 0; i < n; i++) {
            for (int ii = 0; ii < n; ii++) {
                if (ii == i) continue;
                
            }
        }
    }
}