#include <bits/stdc++.h>
using namespace std;

struct Garbage {
    int t, h, f;
};

int D, G, max_h = 0;
vector<Garbage> garbages;
vector<vector<int>> dp; // dp[i][h]表示前i件物品在高度为h时最大剩余生命值

pair<bool, int> solve() {
    dp.resize(G + 1, vector<int>(max_h + 1, -1)); // -1代表不可达
    dp[0][0] = 10;
    int idx = 0;
    for (int i = 1; i <= G; ++i) {
        int ti = garbages[i - 1].t, hi = garbages[i - 1].h,
            fi = garbages[i - 1].f;
        int pass_t = (i == 1) ? ti : ti - garbages[i - 2].t;
        bool flg = false;
        for (int h = 0; h <= max_h; ++h) {
            if (h - hi >= 0 && dp[i - 1][h - hi] >= pass_t) 
                dp[i][h] = max(dp[i][h], dp[i - 1][h - hi] - pass_t);
            if (dp[i - 1][h] >= pass_t) 
                dp[i][h] = max(dp[i][h], dp[i - 1][h] - pass_t + fi);
            if (dp[i][h] >= 0) 
                flg = true;
        }
        if (!flg) {
            idx = i - 1;
            break;
        }
        for (int h = D; h <= max_h; ++h) {
            if (dp[i][h] >= 0) 
                return {true, ti};
        }
        // 如果直到最后一个仍然出不去但是仍然存活
        if (i == G) {
            int max_left = 0;
            for (int h = 0; h <= max_h; ++h) 
                max_left = max(dp[G][h], max_left);
            return {false, ti + max_left};
        }
    }
    int time = idx == 0 ? 0 : garbages[idx - 1].t;
    int max_left = 0;
    for (int h = 0; h <= max_h; ++h) 
        max_left = max(max_left, dp[idx][h]);
    return {false, time + max_left};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> D >> G;
    garbages.resize(G);
    for (int i = 0; i < G; ++i) {
        cin >> garbages[i].t >> garbages[i].f >> garbages[i].h;
        max_h += garbages[i].h;
    }

    sort(garbages.begin(), garbages.end(), [](const Garbage &a, 
        const Garbage &b) {
        return a.t < b.t;
    });

    auto ans = solve();
    int time = ans.second;
    cout << time << '\n';
}