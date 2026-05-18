#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll N = 2026202620262026ll;

ll min_balanced(ll len) {
    ll res = 1ll << (len - 1);
    int ones_left = len / 2 - 1;
    for (int i = 0; i < ones_left; ++i) 
        res |= (1ll << i);
    return res;
}

ll max_balanced(ll len) {
    ll res = 1ll << (len - 1);
    int ones_left = len / 2 - 1;
    for (int i = 0; i < ones_left; ++i) 
        res |= (1ll << (len - 2 - i));
    return res;
}

int main() {
    // N 的二进制长度是 51（因为 2^50 <= N < 2^51）
    ll cand1 = max_balanced(50), cand2 = min_balanced(52);
    ll diff1 = N - cand1, diff2 = cand2 - N;
    if (diff1 <= diff2) 
        cout << cand1 << endl;
    else 
        cout << cand2 << endl;
}