#include <bits/stdc++.h>
using namespace std;

int n;
vector<array<int, 2>> child;

int max_depth(int root)
{
    if (root == -1) 
        return 0;
    int left_dep = max_depth(child[root][0]);
    int right_dep = max_depth(child[root][1]);
    int depth = max(left_dep, right_dep) + 1;
    return depth;
}

int main()
{
    cin >> n;
    child.resize(n);
    for (int i = 0; i < n; i++) {
        int left, right;
        cin >> left >> right;
        left--;
        right--;
        child[i][0] = left, child[i][1] = right;
    }
    int ans = max_depth(0);
    cout << ans << '\n';
    return 0;
}