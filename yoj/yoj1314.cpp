#include <bits/stdc++.h>
using namespace std;

string line;
vector<string> vals;

int get_type() {
    int i = 0;
    vector<char> operators;
    while (i < line.size()) {
        if (line[i] == '(') {
            if (line[i + 1] == '(' || line[i + 1] == '!') 
                i++;
            else {
                int len = 1, j = i;
                while (line[i] != ')') {
                    i++;
                    len++;
                }
                string tmp = line.substr(j, len);
                bool flag = true;
                for (const auto &val : vals) {
                    if (val == tmp) {
                        flag = false;
                        break;
                    }
                }
                if (flag) {
                    vals.push_back(tmp);
                }
            }
        }
        else if (line[i] == ')') 
            i++;
        else {
            operators.push_back(line[i]);
            i++;
        }
    }
    array<int, 5> op_cnt = {0};
    for (const auto &op : operators) {
        switch (op) {
        case '!': op_cnt[0]++; break;
        case '&': op_cnt[1]++; break;
        case '|': op_cnt[2]++; break;
        case '>': op_cnt[3]++; break;
        case '-': op_cnt[4]++; break;
        }
    }
    if (op_cnt[0] == 2 && op_cnt[1] == 2 && op_cnt[2] == 1 && op_cnt[3] == 2) 
        return 8;
    if (op_cnt[1] == 2 && op_cnt[2] == 1 && op_cnt[3] == 2) 
        return 7;
    if (op_cnt[1] == 1 && op_cnt[4] == 2) 
        return 6;
    if (op_cnt[1] == 1 && op_cnt[3] == 2) 
        return 5;
    if (op_cnt[0] == 1 && op_cnt[1] == 1 && op_cnt[2] == 1) 
        return 4;
    if (op_cnt[0] == 1 && op_cnt[1] == 1 && op_cnt[3] == 1) 
        return 3;
    if (op_cnt[1] == 1 && op_cnt[3] == 1) 
        return 2;
    if (op_cnt[1] == 1) 
        return 1;
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    getline(cin, line);
    int type = get_type();
    switch (type) {
    case 1:
        cout << vals[0];
        break;
    case 2:
        cout << vals[1];
        break;
    case 3:
        cout << '!' << vals[0];
        break;
    case 4:
        cout << vals[0];
        break;
    case 5:
        cout << vals[0] << '>' << vals[2];
        break;
    case 6:
        cout << vals[0] << '-' << vals[2];
        break;
    case 7:
        cout << vals[1] << '|' << vals[3];
        break;
    case 8:
        cout << '!' << vals[0] << '|' << '!' << vals[2];
        break;
    default: break;
    }
    cout << '\n';
}