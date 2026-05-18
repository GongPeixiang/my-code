#include<bits/stdc++.h>
using namespace std;

void solve(const int &n, vector<int> &a) {
    if (a[0] == -1 && a[n-1] == -1) {
        a[0] = a[n-1] = 0;
    }
    else if (a[0] != -1 && a[n-1] == -1) {
        a[n-1] = a[0];
    }
    else if (a[0] == -1 && a[n-1] != -1) {
        a[0] = a[n-1];
    }

    for (int i = 1; i < n-1; i++) {
        if (a[i] == -1) a[i] = 0;
    }
    int ans;
    ans = max(a[0], a[n-1]) - min(a[0],a[n-1]);
    cout << ans << endl;
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << endl;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        solve(n, a);
    }
    return 0;
}