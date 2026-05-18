#include <bits/stdc++.h>
using namespace std;

struct Garbage {
    int t, h, f;
};

int D, G, max_health = 10;
vector<Garbage> g;
vector<vector<int>> dp; // dp[i][j]表示前i件物品在生命值为j时能达到的最大高度

pair<bool, int> solve() {
    dp.resize(G + 1, vector<int>(max_health + 1, -1)); // -1代表不可达
    dp[0][10] = 0;
    int idx = G;
    for (int i = 1; i <= G; ++i) {
        int ti = g[i - 1].t, hi = g[i - 1].h, fi = g[i - 1].f;
        int pass_t = (i == 1) ? ti : ti - g[i - 2].t;
        bool flg = false;
        for (int j = 0; j <= max_health; ++j) {
            if (j - fi + pass_t >= 0 && j - fi + pass_t <= max_health && 
                dp[i - 1][j - fi + pass_t] >= 0) 
                dp[i][j] = max(dp[i][j], dp[i - 1][j - fi + pass_t]);
            if (j + pass_t <= max_health && dp[i - 1][j + pass_t] >= 0) 
                dp[i][j] = max(dp[i][j], dp[i - 1][j + pass_t] + hi);
            if (dp[i][j] >= D) 
                return {true, ti};
        }
    }
    int max_life = 0;
    for (int i = 0; i <= G; ++i) {
        for (int j = 0; j <= max_health; ++j) {
            if (dp[i][j] >= 0) {
                int time = (i == 0) ? 0 : g[i - 1].t;
                max_life = max(max_life, time + j);
            }
        }
    }
    return {false, max_life};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> D >> G;
    g.resize(G);
    for (int i = 0; i < G; ++i) {
        cin >> g[i].t >> g[i].f >> g[i].h;
        max_health += g[i].f;
    }
    
    sort(g.begin(), g.end(), [](const Garbage &a, const Garbage &b) {
        return a.t < b.t;
    });
    max_health += g[G - 1].t;

    auto ans = solve();
    cout << ans.second << '\n';
}