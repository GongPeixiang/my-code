/* monotone queue - sliding window */
#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1000;

int n, k, a[N];

vector<int> max_seq() {
    deque<int> dq;
    vector<int> res;
    for (int i = 0; i < n; ++i) {
        while (!dq.empty() && a[dq.back()] <= a[i]) dq.pop_back();
        dq.push_back(i);
        if (dq.front() <= i - k) dq.pop_front();
        if (i >= k - 1) res.push_back(a[dq.front()]);
    }
    return res;
}

vector<int> min_seq() {
    deque<int> dq;
    vector<int> res;
    for (int i = 0; i < n; ++i) {
        while (!dq.empty() && a[dq.back()] >= a[i]) dq.pop_back();
        dq.push_back(i);
        if (dq.front() <= i - k) dq.pop_front();
        if (i >= k - 1) res.push_back(a[dq.front()]);
    }
    return res;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k;
    for (int i = 0; i < n; ++i) cin >> a[i];
    vector<int> vec1 = max_seq(), vec2 = min_seq();
    for (int num: vec1) cout << num << ' '; 
    cout.put('\n');
    for (int num: vec2) cout << num << ' ';
    cout.put('\n');
    return 0;
}