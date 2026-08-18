#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 50005;

int N, M, L, d[MAXN];

bool check(int len) {
    int cnt = 0;
    int cur = 0, i = 1;
    while (i <= N + 1) {
        if (d[i] - d[cur] < len) {
            cnt++;
            i++;
        } else {
            cur = i;
            i++;
        }
    }
    return cnt <= M;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> L >> N >> M;
    d[0] = 0, d[N+1] = L;
    for (int i = 1; i <= N; i++) cin >> d[i];
    int l = 1, r = L;
    while (l <= r) {
        int mid = l + (r-l)/2;
        if (check(mid)) l = mid + 1;
        else r = mid - 1;
    }
    int ans = l - 1;
    cout << ans << '\n';
    return 0;
}