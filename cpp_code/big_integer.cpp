#include <bits/stdc++.h>
using namespace std;

class BigInt {
private:
    string num_str;
public:
    BigInt(string s = "0"): num_str(s) {}
    // += 和 *= 一般都是成员函数
    // + 和 * 如果左操作数不是当前对象,使用友元全局函数
    BigInt operator+(const BigInt &other) const {
        string a = num_str, b = other.num_str;
        int len = max(a.size(), b.size());
        vector<int> res(len, 0);
        while (a.size() < len) 
            a = '0' + a;
        while (b.size() < len) 
            b = '0' + b;
        int carry = 0;
        for (int i = len - 1; i >= 0; --i) {
            int x = a[i] - '0', y = b[i] - '0';
            int tmp = x + y + carry;
            res[i] = tmp % 10;
            carry = tmp / 10;
        }
        if (carry) 
            res.insert(0, 1);
        string result= "";
        for (int num : res) 
            result += '0' + num;
        return BigInt(result);
    }

    BigInt operator*(const BigInt &other) const {
        string a = num_str, b = other.num_str;
        int len1 = a.size(), len2 = b.size();
        vector<int> res(len1 + len2, 0);
        for (int i = len1 - 1; i >= 0; --i) {
            int carry = 0;
            for (int j = len2 - 1; j >= 0; --j) {
                int x = a[i] - '0', y = b[j] - '0';
                int tmp = x * y + carry + res[i + j + 1];
                res[i + j + 1] = tmp % 10;
                carry =  tmp / 10;;
            }
            if (carry) 
                res[i] += carry;
        }
        int i = 0;
        while (res[i] == 0) 
            ++i;
        string result = "";
        for (; i < res.size(); ++i) 
            result += res[i] + '0';
        return BigInt(result);
    }

    bool operator==(const BigInt &other) const {
        return num_str == other.num_str;
    }

    bool operator<(const BigInt &other) const {
        if (num_str.size() < other.num_str.size()) 
            return true;
        else if (num_str.size() > other.num_str.size()) 
            return false;
        return num_str < other.num_str;
    }
};