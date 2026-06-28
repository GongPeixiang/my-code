#include <bits/stdc++.h>
using namespace std;

// N进制
int N, steps = 0;
string result;

bool judge(const string &num_str) {
    for (int i = 0; i < num_str.size() / 2; i++) {
        if (num_str[i] != num_str[num_str.size() - 1 - i]) 
            return false;
    }
    return true;
}

string add(const string &a, const string &b) {
    string result;
    int len = a.size();
    result.resize();
    int carry = 0;
    for (int i = len - 1; i >= 0; i--) {
        int x = (isdigit(a[i])) ? a[i] - '0' : a[i] - 'A' + 10;
        int y = (isdigit(b[i])) ? b[i] - '0' : b[i] - 'A' + 10;
        int tmp = x + y + carry;
        result[i] = (tmp % N < 10) ? tmp % N + '0' : tmp % N - 10 + 'A';
        carry = tmp / N;
    }
    if (carry) 
        result = '1' + result;
    return result;
}

int main() {
    string num_str;
    cin >> N >> num_str;

    while (steps <= 30 && !judge(num_str)) {
        string rev = num_str;
        reverse(rev.begin(), rev.end());
        num_str = add(num_str, rev);
        steps++;
    }
    
    if (judge(num_str)) 
        cout << "STEP=" << steps << '\n';
    else 
        cout << "Impossible!" << '\n';

    return 0;
}