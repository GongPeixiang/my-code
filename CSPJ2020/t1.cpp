#include <bits/stdc++.h>
using namespace std;

int num;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> num;
    if (num % 2) {
        cout << -1 << '\n';
        return 0;
    }
    int c = num;
    vector<int> a;
    while (c) {
        int tmp = c % 2;
        a.push_back(tmp);
        c /= 2;
    }
    reverse(a.begin(), a.end());
    a.pop_back();
    int d = a.size();
    for (int i = 0; i < d; ++i) {
        if (a[i]) 
            cout << (1 << (d - i)) << ' ';
    }
    return 0;
}