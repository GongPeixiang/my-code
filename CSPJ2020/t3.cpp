#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 10005;

string line;
int n, T;
bool x[MAXN];

bool cal(char op, bool a, bool b = false) {
    switch (op) {
        case '!': return !a;
        case '&': return a && b;
        case '|': return a || b;
        default: return false;
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    getline(cin, line);
    cin >> n;
    for (int i = 1; i <= n; ++i) 
        cin >> x[i];
    cin >> T;
    int p;
    while (T--) {
        cin >> p;
        bool pre = x[p];
        x[p] = !x[p];
        stack<bool> val;
        for (int i = 0; i < line.size(); ) {
            if (line[i] == 'x') {
                int idx = 0;
                ++i;
                while (isdigit(line[i])) 
                    idx = idx * 10 + (int)(line[i++] - '0');
                val.push(x[idx]);
            } else if (line[i] != ' ') {
                char op = line[i];
                if (op == '!') {
                    bool a = val.top(); val.pop();
                    bool res = cal(op, a);
                    val.push(res);
                } else {
                    bool b = val.top(); val.pop();
                    bool a = val.top(); val.pop();
                    bool res = cal(op, a, b);
                    val.push(res);
                }
                ++i;
            } else 
                ++i;
        }
        cout << val.top() << '\n';
        x[p] = pre;
    }
    return 0;
}