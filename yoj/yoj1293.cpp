#include <bits/stdc++.h>
using namespace std;

string expression, line;
unordered_map<char, int> dict;

vector<string> preprocess(const string &line) {
    vector<string> ret;
    int i = 0, j = 1;
    string tmp;
    for (; j < line.size(); j++) {
        if (line[j] == ' ') {
            tmp = line.substr(i, j - i);
            ret.push_back(tmp);
            i = j + 1;
        } else if (j == line.size() - 1) {
            tmp = line.substr(i, j - i + 1);
            ret.push_back(tmp);
        }
    }
    return ret;
}

int main() {
    getline(cin, expression);
    getline(cin, line);
    auto vals = preprocess(line);
    int idx = 0;
    for (const auto &ch : expression) {
        if (isalpha(ch) && !dict.count(ch)) {
            dict[ch] = idx++;
        }
    }
    int i = 0;
    while (i != expression.size()) {
        if (dict.count(expression[i])) {
            int idx =  dict[expression[i]];
            string rep = vals[idx];
            expression.replace(i, 1, rep);
            i += rep.size();
        }
        else
            i++;
    }
    cout << expression << '\n';
} 