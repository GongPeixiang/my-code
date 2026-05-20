#include <bits/stdc++.h>
using namespace std;

constexpr int N = 100005;

int n, w, score[N];
vector<int> a;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> w;
    for (int i = 0; i < n; ++i) 
        cin >> score[i];
    for (int i = 0; i < n; ++i) {
        int tmp = score[i];
        if (a.empty()) 
            a.push_back(tmp);
        else {
            if (tmp >= a[0]) 
                a.insert(a.begin(), tmp);
            else if (tmp <= a[i-1]) 
                a.push_back(tmp);
            else {
                a.push_back(tmp);
                sort(a.begin(), a.end(), greater<int>());
            }
        }
        int p = max(1, (i + 1) * w / 100);
        int s = a[p-1];
        cout << s << ' ';
    }
    return 0;
}