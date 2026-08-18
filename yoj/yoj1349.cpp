#include <bits/stdc++.h>
using namespace std;

constexpr int N = 15; // the 11th bell number

int n, rgs[N];
string str, tmp;
vector<string> res;

void dfs(int pos, int part) {
    if (pos == n) {
        tmp.clear();
        for (int k = 0; k <= part; k++) {
            for (int i = 0; i < n; i++) 
                if (rgs[i] == k) tmp += str[i];
            if (k < part) tmp += '|';
        }
        res.push_back(tmp);
        return;
    }
    for (int k = 0; k <= part; k++) {
        rgs[pos] = k;
        dfs(pos + 1, part);
    }
    rgs[pos] = part + 1;
    dfs(pos + 1, part + 1);
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> str;
    n = str.size();
    memset(rgs, -1, sizeof(rgs));
    rgs[0] = 0;
    dfs(1, 0);
    sort(res.begin(), res.end(), [](const string& a, const string& b) {
        return a < b;
    });
    for (string& s: res) cout << s << '\n';
    return 0;
}