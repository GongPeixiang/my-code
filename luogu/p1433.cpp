#include <bits/stdc++.h>
using namespace std;

constexpr double INF = 1e9;
int n;

int main() {
    cin >> n;
    // 注意：题目通常是 n 个点，加上原点 0，总共 n+1 个点
    int total_n = n + 1; 
    vector<pair<double, double>> points(total_n);
    points[0] = {0.0, 0.0};
    for (int i = 1; i <= n; ++i) 
        cin >> points[i].first >> points[i].second;

    vector<vector<double>> dist(total_n, vector<double>(total_n));
    for (int i = 0; i < total_n; ++i) {
        for (int j = 0; j < total_n; ++j) {
            double dx = points[i].first - points[j].first, 
                dy = points[i].second - points[j].second;
            dist[i][j] = sqrt(dx * dx + dy * dy);
        }
    }

    int limit = 1 << total_n;
    vector<vector<double>> dp(limit, vector<double>(total_n, INF));
    dp[1][0] = 0.0;

    for (int mask = 1; mask < limit; ++mask) {
        if (!(mask & 1)) continue;

        for (int last = 0; last < total_n; ++last) {
            if (!((mask >> last) & 1)) continue;
            if (dp[mask][last] == INF) continue;

            for (int next_node = 0; next_node < total_n; ++next_node) {
                if ((mask >> next_node) & 1) continue;

                int new_mask = mask | (1 << next_node);
                double new_dist = dp[mask][last] + dist[last][next_node];
                if (new_dist < dp[new_mask][next_node]) 
                    dp[new_mask][next_node] = new_dist;
            }
        }
    }

    // 寻找答案：所有点都访问过 (mask = limit - 1)，停在任意点的最小值
    double ans = INF;
    int full_mask = limit - 1;
    for (int i = 0; i < total_n; ++i) {
        ans = min(ans, dp[full_mask][i]);
    }

    cout << fixed << setprecision(2) << ans << '\n';
}