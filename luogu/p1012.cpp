#include <bits/stdc++.h>
using namespace std;

constexpr int N = 20;

int n;
string num[N];

bool cmp(const string& x, const string& y) {
    return x + y > y + x;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for (int i = 0; i < n; i++) cin >> num[i];
    sort(num, num+n, cmp);
    for (int i = 0; i < n; i++) cout << num[i];
    cout.put('\n');
    return 0;
}