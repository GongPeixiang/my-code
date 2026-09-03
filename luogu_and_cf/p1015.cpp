#include <bits/stdc++.h>
using namespace std;

const int N = 105;

int n, a[N], b[N], c[N+5];
string num, rev;

bool judge() {
    int l = num.size();
    for (int i = 0; i < l / 2; i++) 
        if (num[i] != num[l-1-i]) return false;
    return true;
}

string add() {
    memset(c, 0, sizeof(c));
    int la = num.size(), lb = rev.size();
    int l = max(la, lb);
    for (int i = 0; i < la; i++) {
        if (isdigit(num[la-1-i])) a[i] = num[la-1-i] - '0';
        else a[i] = num[la-1-i] - 'A' + 10;
    }
    for (int i = 0; i < lb; i++) {
        if (isdigit(rev[lb-1-i])) b[i] = rev[lb-1-i] - '0';
        else b[i] = rev[lb-1-i] - 'A' + 10;
    }
    for (int i = la; i < l; i++) a[i] = 0;
    for (int i = lb; i < l; i++) b[i] = 0;
    for (int i = 0; i < l; i++) {
        c[i] += a[i] + b[i];
        c[i+1] += c[i] / n;
        c[i] %= n; 
    }
    while (c[l] == 0 && l > 0) l--;
    string res = "";
    for (int i = l; i >= 0; i--) {
        if (c[i] < 10) res += (char)(c[i] + '0');
        else res += (char)(c[i] - 10 + 'A');
    }
    return res;
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    cin >> n >> num;
    int step = 0;
    while (!judge() && step <= 30) {
        rev = num;
        reverse(rev.begin(), rev.end());
        num = add();
        step++;
    }
    if (step < 31) cout << "STEP=" << step << '\n';
    else cout << "Impossible!\n";
    return 0;
}