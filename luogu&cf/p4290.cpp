#include <bits/stdc++.h>
using namespace std;

constexpr char word[4] = { 'W', 'I', 'N', 'G' };
constexpr int MAXL = 205, MAXN = 20;

int L;
char name[MAXL], dict[4][MAXN][3];
bool ok[4][4][4], dp[MAXL][MAXL][4];

inline int convert(char c) { return strchr(word, c) - word; }

vector<char> solve() {
    for (int i = 0; i < L; ++i) {
        int idx = convert(name[i]);
        dp[i][i][idx] = true;
    }
    for (int len = 2; len <= L; ++len) {
        for (int i = 0; i + len - 1 < L; ++i) {
            int j = i + len - 1;
            for (int k = i; k < j; ++k) {
                for (int x = 0; x < 4; ++x) {
                    for (int y = 0; y < 4; ++y) {
                        for (int z = 0; z < 4; ++z) {
                            if (dp[i][k][y] && dp[k+1][j][z] && ok[x][y][z]) 
                                dp[i][j][x] = true;
                        }
                    }
                }
            }
        }
    }
    vector<char> res;
    for (int i = 0; i < 4; ++i) 
        if (dp[0][L-1][i]) res.push_back(word[i]);
    return res;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    memset(ok, 0, sizeof(ok));
    memset(dp, 0, sizeof(dp));
    int cnt[4];
    cin >> cnt[0] >> cnt[1] >> cnt[2] >> cnt[3];
    for (int k = 0; k < 4; ++k) 
        for (int i = 0; i < cnt[k]; ++i) 
            cin >> dict[k][i];     
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < cnt[i]; ++j) {
            int id1 = convert(dict[i][j][0]), id2 = convert(dict[i][j][1]);
            ok[i][id1][id2] = true;
        }
    }
    cin >> name; L = strlen(name);
    auto ans = solve();
    if (ans.size()) for (char c: ans) cout << c;
    else cout << "The name is wrong!";
    cout << '\n';
    return 0;
}