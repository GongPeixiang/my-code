#include <bits/stdc++.h>
using namespace std;

constexpr int MAXM = 10005;

struct Mouse {
    int x, y, t;
} mouse[MAXM];
int n, m, dp[MAXM]; // n就是一个多余的废话

inline int dist(int x, int y, int xx, int yy) { return abs(x - xx) + abs(y - yy); }

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 0; i < m; ++i) 
        cin >> mouse[i].t >> mouse[i].x >> mouse[i].y;
    for (int i = 0; i < m; ++i) {
        dp[i] = 1;
        for (int j = 0; j < i; ++j) {
            if (dist(mouse[i].x, mouse[i].y, mouse[j].x, mouse[j].y) 
            <= mouse[i].t - mouse[j].t) 
                dp[i] = max(dp[i], dp[j] + 1);
        }
    }
    int ans = 0;
    for (int i = 0; i < m; ++i) 
        ans = max(ans, dp[i]);
    cout << ans << '\n';
    return 0;
}