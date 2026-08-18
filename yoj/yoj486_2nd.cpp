#include<bits/stdc++.h>
using namespace std;

constexpr int N = 55;

int n;
string base, seq[N];

bool cmp(const string& a, const string& b) {
    for (int i = 0; i < a.size(); i++) {
        int p1 = base.find(a[i]), p2 = base.find(b[i]);
        if (p1 != p2) return p1 < p2;
    }
    return false;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> base;
    for (int i = 0; i < n; i++) cin >> seq[i];
    sort(seq, seq + n, cmp);
    for (string str : seq) cout << str << '\n';
    return 0;
}