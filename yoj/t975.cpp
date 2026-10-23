// huffman
// 利用WPL的性质! WPL = Σ weight of internal node
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr int N = 1000010;

int n;
ll freq, ans = 0;

int main() {
    scanf("%d", &n);
    priority_queue<ll, vector<ll>, greater<ll>> pq;
    for (int i = 0; i < n; i++) {
        scanf("%lld", &freq);
        if (freq) pq.push(freq);
    }
    if (n == 1) {
        printf("0\n");
        return 0;
    }
    while (pq.size() > 1) {
        ll a = pq.top(); pq.pop();
        ll b = pq.top(); pq.pop();
        ll s = a + b;
        ans += s;
        pq.push(s);
    }
    printf("%lld\n", ans);
    return 0;
}