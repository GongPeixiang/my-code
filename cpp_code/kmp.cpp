#include <bits/stdc++.h>
using namespace std;

void get_next(const string &pattern, vector<int> &next) {
    if (pattern.size() < 2) 
        return;
    next.resize(pattern.size());
    next[0] = next[1] = 0;
    int cur = 2, cmp = 0;
    while (cur < pattern.size()) {
        if (pattern[cur - 1] == pattern[cmp]) 
            next[cur++] = ++cmp;
        else if (cmp > 0) 
            cmp = next[cmp];
        else 
            next[cur++] = 0;
    }
}

vector<int> kmp_search(const string &text, const string &pattern) {
    vector<int> next, pos;
    get_next(pattern, next);
    int i = 0, j = 0;
    while (i < text.size()) {
        if (text[i] == pattern[j]) {
            i++;
            j++;
        }
        else if (j > 0) 
            j = next[j];
        else 
            i++;

        if (j == pattern.size()) {
            pos.push_back(i - pattern.size());
            j = next[pattern.size() - 1];
        }
    }
    return pos;
}

int main() {
    string text, pattern;
    cin >> text >> pattern;
    vector<int> pos = kmp_search(text, pattern);
    for (auto p : pos) 
        cout << p << ' ';
    cout << '\n';
    return 0;
}