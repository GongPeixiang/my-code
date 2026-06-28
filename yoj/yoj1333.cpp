#include <bits/stdc++.h>
using namespace std;

int n, m, max_b = 0;
vector<int> b;
int cnt = 0;

void dfs(int dep, int sum) {
    // prunning
    if (sum > m || sum + (n - dep) * max_b < m) 
        return;
    if (dep == n && sum == m) {
        ++cnt;
        return;
    }
    for (int i = 0; i <= b[dep]; ++i) {
        dfs(dep + 1, sum + i);
    }
}

int main() {
    cin >> n >> m;
    b.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> b[i];
        max_b = max(max_b, b[i]);
    }
    dfs(0, 0);
    cout << cnt << '\n';    
}