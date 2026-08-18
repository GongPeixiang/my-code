#include <bits/stdc++.h>
using namespace std;

int n = 0, vals[26], idx[26], order[256];
string expr;

inline void init() {
    order['!'] = 4;
    order['&'] = 3;
    order['|'] = 2;
    order['>'] = order['-'] = 1;
}

bool calc(char op, bool a, bool b = 0) {
    switch (op) {
        case '!': return !a;
        case '&': return a && b;
        case '|': return a || b;
        case '>': return !a || b;
        case '-': return a == b;
    }
    return false;
}

bool eval() {
    stack<char> ops;
    stack<bool> exp;
    for (char ch: expr) {
        if (isalpha(ch)) {
            bool val = vals[idx[ch-'a']];
            exp.push(val);
        } else {
            if (ch == '(') ops.push('(');
            else if (ch == ')') {
                while (!ops.empty() && ops.top() != '(') {
                    char op = ops.top(); ops.pop();
                    if (op == '!') {
                        bool a = exp.top(); exp.pop();
                        exp.push(calc(op, a));
                    } else {
                        bool b = exp.top(); exp.pop();
                        bool a = exp.top(); exp.pop();
                        exp.push(calc(op, a, b));
                    }
                }
                if (!ops.empty()) ops.pop(); // pop the '('
            } else {
                while (!ops.empty() && ops.top() != '(' && order[ops.top()] >= order[ch]) {
                    char op = ops.top(); ops.pop();
                    if (op == '!') {
                        bool a = exp.top(); exp.pop();
                        exp.push(calc(op, a));
                    } else {
                        bool b = exp.top(); exp.pop();
                        bool a = exp.top(); exp.pop();
                        exp.push(calc(op, a, b));
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
            exp.push(calc(op, a));
        } else {
            bool b = exp.top(); exp.pop();
            bool a = exp.top(); exp.pop();
            exp.push(calc(op, a, b));
        }
    }
    return exp.top();
}

void solve() {
    for (int i = 0; i < 26; i++) {
        if (idx[i] == -1) continue;
        char c = (char)(i + 'a');
        cout << c << ' ';
    }
    cout << expr << '\n';
    int tot = 1 << n;
    for (int k = 0; k < tot; k++) {
        for (int i = 0; i < n; i++) {
            int bit = (k >> (n - 1 - i)) & 1;
            vals[i] = bit;
            cout << vals[i] << ' ';
        }
        cout << eval() << '\n';
    }
}

int main() {
    init();
    memset(idx, -1, sizeof(idx));
    cin >> expr;
    for (char ch: expr) {
        if (isalpha(ch)) {
            if (~idx[ch-'a']) continue;
            idx[ch-'a'] = n++;
        }
    }
    solve();
    return 0;
}