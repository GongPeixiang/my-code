#include<bits/stdc++.h>
using namespace std;

using ll = long long;
constexpr int MAXN = 105;

int n, m, k;
struct Student {
    ll num;
    vector<int> s;
} stu[MAXN];

int main() {
    cin >> n >> m >> k;
    for (int i = 0; i < n; i++) {
        cin >> stu[i].num;
        stu[i].s.resize(m);
        for (int j = 0; j < m; j++) cin >> stu[i].s[j];
    }
    float sum = 0;
    for (int i = 0; i < n; i++) sum += stu[i].s[k-1];
    float ave = sum / n;
    sort(stu, stu + n, [](const Student& a, const Student& b) {
        if (a.s[k-1] != b.s[k-1]) return a.s[k-1] > b.s[k-1];
        return a.num < b.num;
    });
    int c = (n + 1) / 2, mid = stu[c-1].s[k-1];
    cout << fixed << setprecision(1) << ave << mid;
    cout << defaultfloat;
    cout.unsetf(ios_base::floatfield);
    for (int i = 0; i < n; i++) {
        if (stu[i].s[k-1] == mid) {
            cout << stu[i].num << ' ';
            for (int j = 0; j < m; j++) cout << stu[i].s[j] << " \n"[j == m-1];
        }
    }
    return 0;
}