#include <bits/stdc++.h>
using namespace std;

// 原个体域等价于D={0, 1}
string formula;
int pos = 0;
bool is_uni[2] = {false, false}, vals[2];

bool eval(char func, bool m, bool n = false) {
    switch (func) {
        case 'F': return m;
        case 'G': return !(m && n);
        case 'L': return m == n;
        default: return false;
    }
}

bool parse_term() {
    bool ret = false;
    if (formula[pos] == 'x' || formula[pos] == 'y') {
        ret = vals[formula[pos] - 'x'];
        ++pos;
    } else if (formula[pos] == 'a') {
        ret = false;
        ++pos;
    } else if (formula[pos] == 'f') {
        pos += 2;
        bool val = parse_term();
        if (formula[pos] == ')') pos++;
        ret = !val;
    }
    return ret;
}

bool parse_formula() {
    if (formula[pos] == 'F' || formula[pos] == 'G' || formula[pos] == 'L') {
        char func = formula[pos];
        pos += 2;
        if (func == 'F') {
            bool m = parse_term();
            return eval(func, m);
        }
        else {
            bool m = parse_term();
            if (formula[pos] == ',') pos++;
            bool n = parse_term();
            return eval(func, m, n);
        }
    }
    return false;
}

bool judge(const int start) {
    vals[0] = true, vals[1] = true;
    pos = start;
    bool res1 = parse_formula();

    vals[0] = true, vals[1] = false;
    pos = start;
    bool res2 = parse_formula();

    vals[0] = false, vals[1] = true;
    pos = start;
    bool res3 = parse_formula();

    vals[0] = false, vals[1] = false;
    pos = start;
    bool res4 = parse_formula();

    if (is_uni[0] && is_uni[1]) 
        return res1 && res2 && res3 && res4;
    else if (is_uni[0] && !is_uni[1]) 
        return (res1 || res2) && (res3 || res4);
    else if (!is_uni[0] && is_uni[1])
        return (res1 && res2) || (res3 && res4);
    else 
        return res1 || res2 || res3 || res4;
}

int main() {
    if (!getline(cin, formula)) return 0;
    while (formula[pos] == 'V' || formula[pos] == 'E') {
        int idx = formula[pos + 1] - 'x';
        if (formula[pos] == 'V') is_uni[idx] = true;
        else is_uni[idx] = false;
        pos += 2;
    }
    int start = pos;
    cout << judge(start) << '\n';
}