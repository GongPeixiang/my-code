#include <bits/stdc++.h>
using namespace std;

const int N = 20005;

string a, b;
int x[N], y[N], res[N*2];

string multi() {
    memset(res, 0, sizeof(res));
    int la = a.size(), lb = b.size();
    for (int i = 0; i < la; i++) x[i] = a[la-1-i] - '0';
    for (int i = 0; i < lb; i++) y[i] = b[lb-1-i] - '0';
    for (int i = 0; i < la; i++) 
        for (int j = 0; j < lb; j++) 
            res[i+j] += x[i] * y[j];
    for (int i = 0; i < la + lb + 5; i++) { // 小心处理最高位
        if (res[i] > 9) {
            res[i+1] += res[i] / 10;
            res[i] %= 10;
        }
    }
    int l = la + lb;
    while (res[l] == 0 && l > 0) l--;
    string ans = "";
    for (int i = l; i >= 0; i--)  ans += (char)(res[i] + '0');
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    cin >> a >> b;
    cout << multi() << '\n';
    return 0;
}