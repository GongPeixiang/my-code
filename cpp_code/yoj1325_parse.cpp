#include <bits/stdc++.h>
using namespace std;

array<bool, 3> in_bound = {false, false, false};
string formula, result = "";
int pos = 0;

void parse_term() {
    if (formula[pos] == 'f' || formula[pos] == 'g') {
        char op = formula[pos] == 'f' ? '+' : '*';
        pos += 2;
        parse_term();
        result += op;
        if (formula[pos] == ',') 
            ++pos;
        parse_term();
        ++pos;
    }
    else if (formula[pos] == 'x' || formula[pos] == 'y' || formula[pos] == 'z') {
        int idx = formula[pos] - 'x';
        if (in_bound[idx]) 
            result += formula[pos];
        else 
            result += (idx + 1) + '0';
        ++pos;
    }
    else if (formula[pos] == 'a') {
        result += '0';
        ++pos;
    }
}

void parse_formula() {
    while (pos < formula.size()) {
        if (formula[pos] == 'F') {
            pos += 2;
            parse_term();
            result += '=';
            if (formula[pos] == ',') 
                ++pos;
            parse_term();
            ++pos;
        }
        else if (formula[pos] == '(' || formula[pos] == ')') {
            result += formula[pos];
            ++pos;
        }
        else 
            ++pos;
    }
}

int main() {
    if (!getline(cin, formula))
        return 0;
    while (formula[pos] == 'V' || formula[pos] == 'E') {
        result += formula[pos];
        result += formula[pos + 1];
        int idx = formula[pos + 1] - 'x';
        in_bound[idx] = true;
        pos += 2;
    }
    parse_formula();
    cout << result << '\n';
}