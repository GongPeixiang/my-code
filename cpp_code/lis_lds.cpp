#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> nums;
vector<int> lis, lnds;

int main() {
    cin >> n;
    nums.resize(n);
    for (int i = 0; i < n; ++i) 
        cin >> nums[i];
    for (int num : nums) {
        auto it = lower_bound(lis.begin(), lis.end(), num);
        if (it == lis.end()) 
            lis.push_back(num);
        else 
            *it = num;
        it = upper_bound(lnds.begin(), lnds.end(), num);
        if (it == lnds.end()) 
            lnds.push_back(num);
        else 
            *it = num;
    }
    int max_lis = lis.size(), max_lnds = lnds.size();
    cout << max_lis << ' ' << max_lnds << '\n';
}