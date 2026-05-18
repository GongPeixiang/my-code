#include <bits/stdc++.h>
using namespace std;

int cnt = 0;
string a, b;
vector<bool> vals(3, 0);
unordered_map<char, int> idx_dict = { {'p', 0}, {'q', 1}, {'r', 2} };
unordered_map<char, int> order = { {'!', 4}, {'&', 3}, {'|', 2}, {'>', 1}, {'-', 1} };

bool calculate(char op, bool a, bool b = false) {
    switch(op) {
    case '!': return !a;
    case '&': return a && b;
    case '|': return a || b;
    case '>': return (!a || b);
    case '-': return a == b;
    }
    return false;
}

bool judge(const string &expression) {
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
    if (dep == 3) {
        cout << "p=" << vals[0] << ' ';
        cout << "q=" << vals[1] << ' ';
        cout << "r=" << vals[2] << ' ';
        bool ea = judge(a), eb = judge(b);
        cout << 'A' << '=' << ea << ' ';
        cout << 'B' << '=' << eb << ' ';
        cout << "A>B=" << (int)(ea <= eb) << '\n';
        if (ea <= eb) 
            cnt++;
        return;
    }

    for (int i = 0; i < 2; ++i) {
        vals[dep] = i;
        dfs(dep + 1);
        vals[dep] = 0;
    }
}

int main() {
    cin >> a >> b;
    dfs(0);
    if (cnt == 8) 
        cout << "yes" << '\n';
    else 
        cout << "no" << '\n';
}