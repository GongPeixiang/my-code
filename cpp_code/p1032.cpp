#include <bits/stdc++.h>
using namespace std;

string A, B;
vector<pair<string, string>> dict;

bool dfs(int dep, const int max_dep) {
    if (dep == max_dep) {
        return A == B;
    }
    for (int i = 0; i < A.size(); i++) {
        for (const auto &[key, value] : dict) {
            if (A.substr(i, key.size()) == key) {
                A.erase(i, key.size());
                A.insert(i, value);
                if (dfs(dep + 1, max_dep)) 
                    return true;
                A.erase(i, value.size());
                A.insert(i, key);
            }
        }
    }
    return false;
}

int solve() {
    for (int max_dep = 0; max_dep <= 10; max_dep++) {
        if (dfs(0, max_dep)) {
            return max_dep;
        }
    }
    return -1;
}

int main() {
    cin >> A >> B;
    cin.ignore();
    string line, a, b;
    while (getline(cin, line)) {
        stringstream ss(line);
        ss >> a >> b;
        if (!a.empty() && !b.empty()) {
            dict.push_back({a, b});
        }
    }

    int steps = solve();

    if (steps != -1) 
        cout << steps << '\n';
    else 
        cout << "NO ANSWER!\n";
}