#include <bits/stdc++.h>
using namespace std;

constexpr int N = 35;

int n = 0, a[N], b[N];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    string line;
    while (getline(cin, line)) {
        stringstream ss(line);
        n = 0;  memset(a, 0, sizeof(a));
        int tmp;
        while (ss >> tmp) a[n++] = tmp;
        memcpy(b, a, sizeof(a));
        sort(b, b + n);
        for (int i = n - 1; i >= 0; i--) {
            if (a[i] == b[i]) continue;
            for (int j = 1; j < i; j++) {
                if (a[j] == b[i]) {
                    reverse(a, a + j + 1);
					cout << n - j << ' ';
					break;
                }
            }
            reverse(a, a + i + 1);
            cout << n - i << ' ';
        }
        cout << "0\n";
    }
    return 0;
}