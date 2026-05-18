#include <bits/stdc++.h>
using namespace std;

vector<char> val;
string output = "";

void dfs(int pos) {
    if (pos == val.size()) 
        return;
    for (int i = pos; i < val.size(); ++i) {
        output.push_back(val[i]);
        cout << output << '\n';
        dfs(i + 1);
        output.pop_back();
    }
}

int main() {
    string line;
    cin >> line;
    for (char ch : line) 
        val.push_back(ch);
    sort(val.begin(), val.end(), [](const char &a, const char &b) {
        return a < b;
    });
    dfs(0);
}