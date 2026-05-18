#include <bits/stdc++.h>
using namespace std;

int N;
vector<array<array<bool, 4>, 4>> sched;
constexpr array<int, 9> dx = { 0, 0, 0, 0, 0, 1, 2, -1, -2 };
constexpr array<int, 9> dy = { 0, 1, 2, -1, -2, 0, 0, 0, 0 };
vector<int> memo;

auto idx_memo = [](int d, int cx, int cy, int tl, int tr, int bl, int br) {
    return ((((((d * 4 + cx) * 4 + cy) * 8 + tl) * 8 + tr) 
    * 8 + bl) * 8 + br);
};

inline bool check(int day, int cx, int cy) {
    for (int i = cx; i <= cx + 1; ++i) {
        for (int j = cy; j <= cy + 1; ++j) {
            if (sched[day][i][j]) 
                return false;
        }
    }
    return true;
}

bool dfs(int day, int cx, int cy, int tl, int tr, int bl, int br) {
    int idx = idx_memo(day, cx, cy, tl, tr, bl, br);
    if (memo[idx] != -1) 
        return memo[idx];
    if (!check(day, cx, cy)) 
        return false;
    if (tl >= 7 || tr >= 7 || bl >= 7 || br >= 7) 
        return false;
    if (day == N - 1)
        return true;
    bool res = false;
    for (int i = 0; i < 9; ++i) {
        int ncx = cx + dx[i], ncy = cy + dy[i];
        if (ncx < 0 || ncx > 2 || ncy < 0 || ncy > 2) 
            continue;
        int ntl = (ncx == 0 && ncy == 0) ? 0 : tl + 1;
        int ntr = (ncx == 0 && ncy == 2) ? 0 : tr + 1;
        int nbl = (ncx == 2 && ncy == 0) ? 0 : bl + 1;
        int nbr = (ncx == 2 && ncy == 2) ? 0 : br + 1;
        res |= dfs(day + 1, ncx, ncy, ntl, ntr, nbl, nbr);
    }
    memo[idx] = res;
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (1) {
        cin >> N;
        if (!N) break;
        sched.resize(N);
        for (int d = 0; d < N; ++d) {
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j) {
                    cin >> sched[d][i][j];
                }
            }
        }
        // std::array和vector用memset初始化需要arr.data()
        memo.resize(N * 4 * 4 * 8 * 8 * 8 * 8);
        memset(memo.data(), 0xff, memo.size() * sizeof(int));
        bool ans = dfs(0, 1, 1, 1, 1, 1, 1);
        cout << ans << '\n';
    }
}