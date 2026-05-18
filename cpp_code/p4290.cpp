#include <bits/stdc++.h>
using namespace std;

int L;
string name;
array<char, 4> ch = { 'W', 'I', 'N', 'G' };
array<array<array<bool, 4>, 4>, 4> ok;

inline int convert(char c) {
    switch (c) {
        case 'W': return 0;
        case 'I': return 1;
        case 'N': return 2;
        case 'G': return 3;
        default: return -1;
    }
}

void preprocess(const array<vector<string>, 4> &dict) {
    for (int k = 0; k < 4; ++k) {
        for (auto &group : dict[k]) {
            int idx1 = convert(group[0]), idx2 = convert(group[1]);
            ok[k][idx1][idx2] = true;
        }
    }
}

vector<char> solve() {
    vector<vector<array<bool, 4>>> dp(L, vector<array<bool, 4>>(L));
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
                            if (dp[i][k][y] && dp[k + 1][j][z] && ok[x][y][z]) 
                                dp[i][j][x] = true;
                        }
                    }
                }
            }
        }
    }
    vector<char> res;
    for (int i = 0; i < 4; ++i) {
        if (dp[0][L - 1][i]) 
            res.push_back(ch[i]);
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    array<int, 4> cnt;
    array<vector<string>, 4> dict;
    cin >> cnt[0] >> cnt[1] >> cnt[2] >> cnt[3];
    string tmp;
    for (int k = 0; k < 4; ++k) {
        for (int i = 0; i < cnt[k]; ++i) {
            cin >> tmp;
            dict[k].push_back(tmp);
        }
    }
    cin >> name;
    L = name.size();
    preprocess(dict);
    auto ans = solve();
    if (ans.size()) 
        for (char c : ans) cout << c;
    else
        cout << "The name is wrong!";
    cout << '\n';
}