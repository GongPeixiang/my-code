#include <bits/stdc++.h>
using namespace std;

array<char, 3> ops;
vector<int> nums(4);
array<pair<int, int>, 3> path = {};

bool dfs(int dep) {
    if (dep == 3) 
        return nums[0] == 24;

    vector<int> cpy = nums;
    for (int i = 0; i < nums.size(); ++i) {
        for (int j = i + 1; j < nums.size(); ++j) {
            int a = nums[i], b = nums[j];
            nums.erase(nums.begin() + j);
            nums.erase(nums.begin() + i);

            if (b > a) 
                swap(a, b);
            path[dep] = {a, b};

            nums.push_back(a + b);
            ops[dep] = '+';
            if (dfs(dep + 1)) 
                return true;
            nums.pop_back();

            nums.push_back(a - b);
            ops[dep] = '-';
            if (dfs(dep + 1)) 
                return true;
            nums.pop_back();
            
            nums.push_back(a * b);
            ops[dep] = '*';
            if (dfs(dep + 1)) 
                return true;
            nums.pop_back();

            if (b && a % b == 0) {
                nums.push_back(a / b);
                ops[dep] = '/';
                if (dfs(dep + 1)) 
                    return true;
                nums.pop_back();
            }
            
            nums = cpy;
        }
    }
    return false;
}

int main() {
    for (int i = 0; i < 4; ++i) 
        cin >> nums[i];

    if (dfs(0)) {
        for (int i = 0; i < 2; ++i) {
            const auto &[a, b] = path[i];
            cout << a << ops[i] << b << '=';
            switch (ops[i]) {
                case '+': cout << a + b; break;
                case '-': cout << a - b; break;
                case '*': cout << a * b; break;
                case '/': cout << a / b; break;
                default: break;
            }
            cout << '\n';
        } 
        cout << path[2].first << ops[2] << path[2].second << '=' << 24;
    }
    else 
        cout << "No answer!";

    cout << '\n';
}