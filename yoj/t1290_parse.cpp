#include <bits/stdc++.h>
using namespace std;

string formula;
unordered_map<char, int> idx_tab;
vector<bool> vals;
int pos = 0;

bool eval_formula();
bool eval_impl();
bool eval_or();
bool eval_and();
bool eval_not();
bool eval_atom();

bool eval_formula() {
    bool left = eval_impl();
    while (formula[pos] == '-') {
        bool right = eval_impl();
        left = left == right;
    }
    return left;
}

bool eval_impl() {
    bool left = eval_or();
    while (formula[pos] == '>') {
        bool right = eval_or();
        left = !left || right;
    }
    return left;
}

bool eval_or() {
    bool left = eval_and();
    while (formula[pos] == '|') {
        bool right = eval_and();
        left = left || right;
    }
    return left;
}

bool eval_and() {
    bool left = eval_not();
    while (formula[pos] == '&') {
        bool right = eval_not();
        left = left && right;
    }
    return left;
}

bool eval_not() {
    if (formula[pos] == '!') {
        ++pos;
        bool val = eval_not();
        return !val;
    }
    else 
        return eval_atom();
}

bool eval_atom() {
    if (formula[pos] == '(') {
        ++pos;
        bool val = eval_formula();
        if (formula[pos] == ')') 
            ++pos;
        return val;
    }
    else if (isalpha(formula[pos])) {
        int idx = idx_tab[formula[pos]];
        return vals[idx];
        ++pos;
    }
    else // 正常不会执行到此处
        return false;
}

// 位运算简化, 但时间复杂度和dfs一样
void solve() {
    int n = idx_tab.size();
    vals.resize(n);
    int total = 1 << n;
    for (int i = 0; i < total; ++i) {
        for (int j = 0; j < n; ++j) {
            bool bit = (i >> (n - 1 - j)) & 1;
            vals[j] = bit;
        }
        pos = 0;
        bool result = eval_formula();
        for (auto val : vals) cout << val << ' ';
        cout << result << '\n';
    } 
}

int main() {
    if (!getline(cin, formula)) 
        return 0;
    set<char> abc;
    for (auto ch : formula) {
        if (isalpha(ch) && !abc.count(ch)) 
            abc.insert(ch);
    }
    int idx = 0;
    for (auto ch : abc) {
        cout << ch << ' ';
        idx_tab[ch] = idx++;
    }
    cout << formula << '\n';
    solve();
}