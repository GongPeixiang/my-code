#include <bits/stdc++.h>
using namespace std;

int n;
string expression;
vector<bool> vals;
unordered_map<char, int> idx_dict, order = { {'!', 4}, {'&', 3}, {'|', 2}, {'>', 1}, {'-', 1} };

bool calculate(char op, bool a, bool b = false) {
    switch(op) {
        case '!': return !a;
        case '&': return a && b;
        case '|': return a || b;
        case '>': return (!a || b);
        case '-': return a == b;
        default: break;
    }
    return false;
}

bool judge() {
    stack<char> ops;
    stack<bool> exp;

    for (char ch : expression) {
        if (isalpha(ch)) {
            bool val = vals[idx_dict[ch]];
            exp.push(val);
        }
        else {
            if (ch == '(') 
                ops.push(ch);
            else if (ch == ')') {
                while (!ops.empty() && ops.top() != '(') {
                    char op = ops.top(); ops.pop();
                    if (op == '!') {
                        bool a = exp.top(); exp.pop();
                        exp.push(calculate(op, a));
                    }
                    else {
                        bool b = exp.top(); exp.pop();
                        bool a = exp.top(); exp.pop();
                        exp.push(calculate(op, a, b));
                    }
                }
                if (!ops.empty())
                    ops.pop(); // 弹出'('
            }
            else {
                while (!ops.empty() && ops.top() != '(' && 
                    order[ops.top()] >= order[ch]) {
                    char op = ops.top(); ops.pop();
                    if (op == '!') {
                        bool a = exp.top(); exp.pop();
                        exp.push(calculate(op, a));
                    }
                    else {
                        bool b = exp.top(); exp.pop();
                        bool a = exp.top(); exp.pop();
                        exp.push(calculate(op, a, b));
                    }
                }
                ops.push(ch);
            }
        }
    }

    while (!ops.empty()) {
        char op = ops.top(); ops.pop();
        if (op == '!') {
            bool a = exp.top(); exp.pop();
            exp.push(calculate(op, a));
        }
        else {
            bool b = exp.top(); exp.pop();
            bool a = exp.top(); exp.pop();
            exp.push(calculate(op, a, b));
        }
    }

    return exp.top();
}

void dfs(int dep) {
    if (dep == n) {
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
    getline(cin, expression);

    set<char> abc;
    for (char ch : expression) {
        if (isalpha(ch) && !abc.count(ch)) 
            abc.insert(ch);
    }
    n = abc.size();
    int idx = 0;
    for (auto ch : abc) {
        cout << ch << ' ';
        idx_dict[ch] = idx++;
    }
    cout << expression << '\n';

    dfs(0);
}