#include<bits/stdc++.h>
using namespace std;

void solve(int legs) {
    int cnt = 0;
    for (int i = 0; 2 * i <= legs; i++) {
        for (int j = 0; 4 * j <= legs; j++) {
            if (2 * i + 4 * j == legs) cnt++;
        }
    }
    cout << cnt << endl;
}

int main() {
    int t;
    cin >> t;
    while(t--) {
        int legs;
        cin >> legs;
        solve(legs);
    }
    return 0;
}