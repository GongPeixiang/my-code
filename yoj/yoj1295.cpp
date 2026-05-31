#include <bits/stdc++.h>
using namespace std;

string line;
vector<char> vals;
vector<int> s1;

int encode(const string &tmp) {
    int code = 0;
    vector<int> bit_val(vals.size(), 0);
    int i = 0;
    while (i < tmp.size()) {
        if (tmp[i] == '!') {
            char val = tmp[i + 1];
            for (int j = 0; j < vals.size(); ++j) {
                if (val == vals[j]) {
                    bit_val[j] = 2;
                    break;
                }
            }
            i += 3;
        }
        else if (isalpha(tmp[i])) {
            char val = tmp[i];
            for (int j = 0; j < vals.size(); ++j) {
                if (val == vals[j]) {
                    bit_val[j] = 1;
                    break;
                }
            }
            i += 2;
        }
    }
    for (auto bit : bit_val) 
        code = code * 3 + bit;
    return code;
}

vector<int> decode(int code) {
    vector<int> bits(vals.size(), 0);
    for (int i = vals.size() - 1; i >= 0; --i) {
        bits[i] = code % 3;
        code /= 3;
    }
    return bits;
}

bool can_resolve(int code1, int code2, int &pos) {
    vector<int> c1 = decode(code1);
    vector<int> c2 = decode(code2);
    int dif_cnt = 0;
    for (int i = 0; i < vals.size(); ++i) {
        if (c1[i] != 0 && c2[i] != 0 && c1[i] + c2[i] == 3) {
            pos = i;
            dif_cnt++;
        }
    }
    return dif_cnt == 1;
}

int get_resolvent(int code1, int code2, int resolve_pos) {
    vector<int> c1 = decode(code1);
    vector<int> c2 = decode(code2);
    vector<int> result(vals.size(), 0);
    
    for (int i = 0; i < vals.size(); ++i) {
        if (i == resolve_pos) 
            result[i] = 0;
        else if (c1[i] + c2[i] != 3)
            result[i] = max(c1[i], c2[i]);
    }
    
    int code = 0;
    for (int bit : result) 
        code = code * 3 + bit;
    return code;
}

inline bool is_empty_clause(int code) {
    return code == 0;
}

bool contains_clause(const vector<int> &clauses, int code) {
    for (int c : clauses) {
        if (c == code) return true;
    }
    return false;
}

bool judge() {
    vector<int> clauses = s1;
    set<int> new_clauses;
    
    while (true) {
        for (int i = 0; i < clauses.size(); ++i) {
            for (int j = i + 1; j < clauses.size(); ++j) {
                int resolve_pos;
                if (can_resolve(clauses[i], clauses[j], resolve_pos)) {
                    int resolvent = get_resolvent(clauses[i], clauses[j], 
                        resolve_pos);
                    
                    if (is_empty_clause(resolvent)) 
                        return false;
                    
                    if (!contains_clause(clauses, resolvent)) 
                        new_clauses.insert(resolvent);
                }
            }
        }
        
        if (new_clauses.empty()) 
            break;
        for (int code : new_clauses) 
            clauses.push_back(code);

        new_clauses.clear();
    }
    
    return true;
}

void preprocess() {
    // 收集所有变量，题目保证字母第一次出现的顺序符合字典序
    for (const auto &ch : line) {
        if (isalpha(ch)) {
            bool flag = true;
            for (const auto &val : vals) {
                if (ch == val) {
                    flag = false;
                    break;
                }
            }
            if (flag) vals.push_back(ch);
        }
    }
    
    int i = 0;
    while (i < line.size()) {
        if (line[i] == '(') {
            int j = i + 1;
            while (line[j] != ')') 
                j++;
            string tmp = line.substr(i + 1, j - i - 1);
            int code = encode(tmp);
            s1.push_back(code);
            i = j + 1;
        } else 
            i++;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    getline(cin, line);
    preprocess();
    
    if (judge()) 
        cout << "yes" << '\n';
    else
        cout << "no" << '\n';
}