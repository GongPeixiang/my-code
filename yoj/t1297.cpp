#include <bits/stdc++.h>
using namespace std;

int cnt = 0, vals[3], order[256];
string a, b;

inline void init() {
    order['!'] = 4;
    order['&'] = 3;
    order['|'] = 2;
    order['>'] = order['-'] = 1;
}

bool calc(char op, bool a, bool b = 0) {
    switch(op) {
        case '!': return !a;
        case '&': return a && b;
        case '|': return a || b;
        case '>': return (!a || b);
        case '-': return a == b;
    }
    return false;
}

bool judge(const string& expr) {
    stack<char> ops;
    stack<bool> exp;
    for (char ch: expr) {
        if (isalpha(ch)) {
            bool val = vals[ch-'p'];
            exp.push(val);
        } else {
            if (ch == '(') ops.push(ch);
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
                if (!ops.empty()) ops.pop(); // 弹出'('
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
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 3; j++) {
            int bit = (i >> (2 - j)) & 1;
            vals[j] = bit;
        }
        cout << "p=" << vals[0] << ' ';
        cout << "q=" << vals[1] << ' ';
        cout << "r=" << vals[2] << ' ';
        bool ea = judge(a), eb = judge(b);
        cout << 'A' << '=' << ea << ' ';
        cout << 'B' << '=' << eb << ' ';
        cout << "A>B=" << (int)(ea <= eb) << '\n';
        if (ea <= eb) cnt++;
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    init();
    cin >> a >> b;
    solve();
    if (cnt == 8) cout << "yes" << '\n';
    else cout << "no" << '\n';
}