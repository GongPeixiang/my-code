#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 16;

int N, a[MAXN], cpy[MAXN];

int heuristic() {
    int cnt = 0;
    for (int i = 0; i < N - 1; ++i) {
        if (abs(a[i] - a[i + 1]) != 1) 
            ++cnt;
    }
    if (a[N - 1] != N - 1) 
        ++cnt;
    return cnt;
}

bool dfs(int dep, const int max_dep, int prev) {// prev是上次反转的末位
    int h = heuristic();
    if (!h) 
        return true;
    if (dep + h > max_dep) 
        return false;
    for (int i = 1; i < N; ++i) {
        if (i == prev) continue;
        reverse(a, a + i + 1);
        if (dfs(dep + 1, max_dep, i)) 
            return true;
        reverse(a, a + i + 1);
    }
    return false;
}

int solve() {
    for (int max_dep = 0; ; ++max_dep) {
        if (dfs(0, max_dep, -1)) 
            return max_dep;
    }
    return -1;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> N;
    for (int i = 0; i < N; ++i) {
        cin >> a[i];
        cpy[i] = a[i];
    }
    sort(cpy, cpy + N);
    int tmp;
    for (int i = 0; i < N; ++i) {
        tmp = a[i];
        a[i] = lower_bound(cpy, cpy + N, tmp) - cpy;
    }
    int min_step = solve();
    cout << min_step << '\n';
    return 0;
}