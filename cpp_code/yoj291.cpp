#include <bits/stdc++.h>
using namespace std;

string a, b, result;

// 正数相加
void add(string &a, string &b) {
    int len = max(a.size(), b.size());
    result.resize(len);
    if (a.size() < len) 
        a.insert(a.begin(), len - a.size(), '0');
    if (b.size() < len) 
        b.insert(b.begin(), len - b.size(), '0');
    int carry = 0;
    for (int i = len - 1; i >= 0; i--) {
        int x = a[i] - '0', y = b[i] - '0';
        int tmp = x + y + carry;
        result[i] = (tmp % 10) + '0';
        carry = tmp / 10;
    }
    if (carry) 
        result = '1' + result;
}

// 正数相减， 但是minus是C++的一个库函数
void substract(string &a, string &b) {
    bool is_minus = false;
    int len = max(a.size(), b.size());
    result.resize(len);
    if (a.size() < len || (a.size() == b.size() && a < b)) {
        swap(a, b);
        is_minus = true;
    }
    b.insert(b.begin(), len - b.size(), '0');
    int borrow = 0;
    for (int i = len - 1; i >= 0; i--) {
        int x = a[i] - '0' - borrow, y = b[i] - '0';
        borrow = x >= y ? 0 : 1;
        int tmp = x + borrow * 10 - y;
        result[i] = tmp + '0';
    }
    while (result[0] == '0') 
        result.erase(0, 1);
    if (is_minus) 
        result = '-' + result;
}

int main() {
    char sign;
    cin >> sign >> a >> b;
    if (sign == '+') {
        if (a[0] != '-' && b[0] != '-') {
            add(a, b);
        }
        else if (a[0] != '0' && b[0] == '-') {
            b.erase(0, 1);
            substract(a, b);
        }
        else if (a[0] == '-' && b[0] != '-') {
            a.erase(0, 1);
            substract(b, a);
        }
        else {
            a.erase(0, 1); 
            b.erase(0, 1);
            add(a, b);
            result = '-' + result;
        }
    }
    else {
        if (a[0] != '-' && b[0] != '-') {
            substract(a, b);
        }
        else if (a[0] != '-' && b[0] == '-') {
            b.erase(0, 1);
            add(a, b);
        }
        else if (a[0] == '-' && b[0] != '-') {
            a.erase(0, 1);
            add(a, b);
            result = '-' + result;
        }
        else {
            a.erase(0, 1); 
            b.erase(0, 1);
            substract(b, a);
        }
    }
    cout << result << '\n';
    return 0;
}