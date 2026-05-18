#include <bits/stdc++.h>
using namespace std;

int n = 0;
string expression;
vector<short> assign;

vector<string> preprocess(const string &line) {
    vector<string> ret;
    int i = 0, j = 1;
    string tmp;
    for (; j < line.size(); j++) {
        if (line[j] == '|') {
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

vector<bool> get_flip(const string &val) {
    vector<bool> flip;
    for (int i = 0; i < val.size(); i++) {
        if (isalpha(val[i])) {
            if (i == 0 || val[i - 1] != '!') 
                flip.push_back(false);
            else if (val[i - 1] == '!') 
                flip.push_back(true);
        }
    }
    return flip;
}

int assignment(const string &val) {
    auto flip = get_flip(val);
    for (int i = 0; i < n; i++) {
        if (flip[i]) 
            assign[i] = 0;
        else 
            assign[i] = 1;
    }
    int ret = 0;
    for (int i = 0; i < n; i++) 
        ret = ret * 2 + assign[i];
    return ret;
}

int main() {
    cin >> expression;
    auto vals = preprocess(expression);
    for (auto &ch : vals[0]) {
        if (isalpha(ch)) 
            n++;
    }
    assign.resize(n);
    int cnt = 0;
    for (const auto &val : vals) {
        if (cnt > 0) 
            cout << '|';
        int idx = assignment(val);
        cout << 'm' << idx;
        cnt++;
    }
}