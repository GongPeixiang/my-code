#include <bits/stdc++.h>
using namespace std;

vector<int> height, lds, lis;
int max_len = 0, need = 0;

int main() {
    int tmp;
    while (cin >> tmp) 
        height.push_back(tmp);
    int n = height.size();
    lds.resize(n, 1);
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (height[j] >= height[i]) {
                lds[i] = max(lds[i], lds[j] + 1);
            }
        }
    }
    for (int i = 0; i < n; i++) 
        max_len = max(max_len, lds[i]);
    // Dilworth 定理: 最少的不上升子序列覆盖数 = 最长上升子序列的长度
    lis.resize(n, 1);
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (height[j] < height[i]) {
                lis[i] = max(lis[i], lis[j] + 1);
            }
        }
    }
    for (int i = 0; i < n; i++) 
        need = max(need, lis[i]);    
    cout << max_len << '\n' << need << '\n';
    return 0;
}