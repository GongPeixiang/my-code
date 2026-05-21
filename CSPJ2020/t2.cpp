#include <bits/stdc++.h>
using namespace std;

// 桶排序

constexpr int MAXS = 610;
int n, w, cnt[MAXS];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> w;
    memset(cnt, 0, sizeof(cnt));
    int maxs = -1, score;
    for (int i = 1; i <= n; ++i) {
        cin >> score;
        maxs = max(maxs, score);
        ++cnt[score];
        int p = max(1, i * w / 100);
        int k = 0, s = maxs;
        while (k < p) {
            k += cnt[s];
            --s;
        }
        cout << (s + 1) << ' ';
    }
    return 0;
}