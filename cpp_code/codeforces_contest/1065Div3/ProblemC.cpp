#include<bits/stdc++.h>
using namespace std;

vector<vector<int>> result;
vector<int> path;
//0代表不进行操作, 1代表交换
void dfs(int depth, const int &n, const vector<int> &a, const vector<int> &b) {
    if (depth == n) {
        int xor_a = 0, xor_b = 0;
        for (int i = 0; i < path.size(); i++) {
            if (path[i] == 1) {
                xor_a ^= b[i];
                xor_b ^= a[i];
            }
            else {
                xor_a ^= a[i];
                xor_b ^= b[i];
            }
        }
        vector<int> temp = {xor_a, xor_b};
        result.push_back(temp);
        return;
    }
    for (int i = 0; i < 2; i++) {
        path.push_back(i);
        dfs(depth + 1, n, a, b);
        path.pop_back();
    }
}

void solve(const int &n, vector<int> a, vector<int> b) {
    dfs(0, n, a, b);
    int a_max = -1, b_max = -1;
    for (int i = 0; i < result.size(); i++) {
        a_max = max(a_max, result[i][0]);
        b_max = max(b_max, result[i][1]);
    }
    if (a_max > b_max) cout << "Ajisai" << endl;
    else if (b_max > a_max) cout << "Mai" << endl;
    else cout << "Tie" << endl;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n), b(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        for (int i = 0; i < n; i++) {
            cin >> b[i];
        }
        result.clear();
        solve(n, a, b);
        result.clear();
    }
    return 0;
}