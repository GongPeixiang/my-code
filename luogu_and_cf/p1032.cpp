#include <bits/stdc++.h>
using namespace std;

constexpr int N = 10, LEN = 20;

int n = 0, maxdep;
string A, B;
struct Item {
    string key, val;
} dict[N];

bool dfs(int dep) {
    if (dep == maxdep) return A == B;
    for (int i = 0; i < A.size(); i++) {
        for (int j = 0; j < n; j++) {
            const string& key = dict[j].key, val = dict[j].val;
            if (A.substr(i, key.size()) == key) {
                A.erase(i, key.size());
                A.insert(i, val);
                if (dfs(dep + 1)) return true;
                A.erase(i, val.size());
                A.insert(i, key);
            }
        }
    }
    return false;
}

int solve() {
    for (maxdep = 0; maxdep <= 10; maxdep++) 
        if (dfs(0)) return maxdep;
    return -1;
}

int main() {
    cin >> A >> B;
    cin.ignore(1000, '\n');
    string line, a, b;
    while (getline(cin, line)) {
        stringstream ss(line);
        ss >> a >> b;
        dict[n++] = (Item){a, b};
    }
    int ans = solve();
    if (~ans) cout << ans << '\n';
    else cout << "NO ANSWER!\n";
}