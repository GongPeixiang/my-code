#include <bits/stdc++.h>
using namespace std;

int V, N;
vector<int> cur;
vector<long long> dp;

int main() {
    cin >> V >> N;
    cur.resize(V);
    dp.resize(N + 1, 0);
    for (int i = 0; i < V; ++i) 
        cin >> cur[i];
    dp[0] = 1;
    for (int i = 1; i <= V; ++i) {
        for (int j = cur[i - 1]; j <= N; ++j) {
            dp[j] += dp[j - cur[i - 1]];
        }
    }
    cout << dp[N] << '\n';
}