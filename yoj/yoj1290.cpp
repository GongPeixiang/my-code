#include <bits/stdc++.h>
using namespace std;

string postfix = "";
vector<bool> vals;
unordered_map<char, int> idx_dict;
unordered_map<char, int> order = { {'!', 5}, {'&', 4}, {'|', 3}, {'>', 2}, {'-', 2} };

void pre_process(const string &rules) {
    stack<char> ops;

    for (const auto &ch : rules) {
        if (isalpha(ch)) 
            postfix += ch;
        else if (ch == '(') 
            ops.push(ch);
        else if (ch == ')') {
            while (!ops.empty() && ops.top() != '(') {
                postfix += ops.top();
                ops.pop();
            }
            ops.pop(); // 弹出'('
        } 
        else {
            while (!ops.empty() && ops.top() != '(' && 
            order[ops.top()] >= order[ch]) {
                if (ops.top() == '!' && ch == '!') 
                    break;
                postfix += ops.top();
                ops.pop();
            }
            ops.push(ch);
        }
    }

    while (!ops.empty()) {
        postfix += ops.top();
        ops.pop();
    }
}

bool judge() {
    stack<bool> s;
    for (const auto &ch : postfix) {
        if (isalpha(ch)) {
            bool val = vals[idx_dict[ch]];
            s.push(val);
        }
        else {
            bool a, b;
            switch(ch) {
            case '!': 
                s.top() = 1 - s.top(); 
                break;
            case '&': 
                a = s.top(); s.pop();
                b = s.top(); s.pop();
                s.push(a && b);
                break;
            case '|':
                a = s.top(); s.pop();
                b = s.top(); s.pop();
                s.push(a || b);
                break;
            case '>': 
                a = s.top(); s.pop();
                b = s.top(); s.pop();
                s.push(a >= b);
                break;
            case '-':
                a = s.top(); s.pop();
                b = s.top(); s.pop();
                s.push(a == b);
                break;
            }
        }
    }
    return s.top();
}

void dfs(int dep) {
    if (dep == idx_dict.size()) {
        for (bool val : vals) 
            cout << val << ' ';
        cout << judge() << '\n';
        return;
    }
    for (int i = 0; i < 2; i++) {
        vals.push_back(i);
        dfs(dep + 1);
        vals.pop_back();
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string rules;
    getline(cin, rules);

    set<char> abc;
    for (const auto &ch : rules) {
        if (isalpha(ch) && !abc.count(ch)) {
            abc.insert(ch);
        }
    }
    int n = abc.size(), idx = 0;
    for (auto it = abc.begin(); it != abc.end(); ++it) {
        char ch = *it;
        cout << ch << ' ';
        idx_dict[ch] = idx++;
    }
    cout << rules << '\n';
    
    pre_process(rules);

    dfs(0);
}