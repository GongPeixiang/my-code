#include <bits/stdc++.h>
using namespace std;

vector<int> v, w;
int n, W;

int zero_one_pack_simple() {
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));
    dp[0][0] = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= W; ++j) {
            if (j >= w[i - 1]) 
                dp[i][j] = max(dp[i - 1][j], 
                    dp[i - 1][j - w[i - 1]] + v[i - 1]);
            else 
                dp[i][j] = dp[i - 1][j];
        }
    }
    return dp[n][W];
}

int zero_one_pack_optimized() {
    vector<int> dp(W + 1, 0);
    dp[0] = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = W; j >= w[i - 1]; --j) {
            dp[j] = max(dp[j], dp[j - w[i - 1]] + v[i - 1]);
        }
    }
    return dp[W];
}

int unbounded_simple() {
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));
    dp[0][0] = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= W; ++j) {
            for (int k = 0; k * w[i - 1] <= j; ++k) {
                dp[i][j] = max(dp[i][j], 
                    dp[i - 1][j - k * w[i - 1]] + k * v[i - 1]);
            }
        }
    }
    return dp[n][W];
}

int unbounded_optimized() {
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));
    dp[0][0] = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= W; ++j) {
            if (j >= w[i - 1]) 
                dp[i][j] = max(dp[i - 1][j], dp[i][j - w[i - 1]] + v[i - 1]);
            else
                dp[i][j] = dp[i - 1][j];
        }
    }
    return dp[n][W];
}

int unbounded_final() {
    vector<int> dp(W + 1, 0);
    dp[0] = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = w[i - 1]; j <= W; ++j) {
            dp[j] = max(dp[j], dp[j - w[i - 1]] + v[i - 1]);
        }
    }
    return dp[W];
}

int main() {
    cin >> n >> W;
    v.resize(n);
    w.resize(n);
    for (int i = 0; i < n; ++i) 
        cin >> v[i] >> w[i];

    cout << zero_one_pack_simple() << '\n';
    cout << zero_one_pack_optimized() << '\n';

    cout << unbounded_simple() << '\n';
    cout << unbounded_optimized() << '\n';
    cout << unbounded_final() << '\n';
}