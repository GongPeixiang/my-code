#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 105;
constexpr int MAXM = 15;

int n, m, K, f[MAXN][MAXM], tab[MAXN];
bool isflg[MAXN], reach[MAXN];
vector<int> flg;
vector<vector<int>> grp;

void preprocess() {
    queue<int> q;
    q.push(0);
    reach[0] = true;
    while (!q.empty()) {
        int cur = q.front(); 
        q.pop();
        for (int i = 0; i < m; ++i) {
            int nxt = f[cur][i];
            if (!reach[nxt]) {
                reach[nxt] = true;
                q.push(nxt);
            }
        }
    }
}

void part() {
    int blk[MAXN];
    memset(blk, -1, sizeof(blk));
    vector<vector<int>> blocks;
    vector<int> mrk_blk, unmrk_blk;
    for (int i = 0; i < n; ++i) {
        if (!reach[i]) continue;
        if (isflg[i]) mrk_blk.push_back(i);
        else unmrk_blk.push_back(i);
    }
    if (!mrk_blk.empty()) blocks.push_back(mrk_blk);
    if (!unmrk_blk.empty()) blocks.push_back(unmrk_blk);

    for (int i = 0; i < blocks.size(); ++i) {
        for (int u : blocks[i]) blk[u] = i;
    }
    
    // Moore 细化
    bool chg = true;
    while (chg) {
        chg = false;
        int new_blk[MAXN];
        memset(new_blk, -1, sizeof(new_blk));
        vector<vector<int>> tmp_blks;
        
        for (auto &b: blocks) {
            map<vector<int>, vector<int>> gp;
            for (int u: b) {
                vector<int> sig(m);
                for (int j = 0; j < m; ++j) {
                    int v = f[u][j];
                    sig[j] = reach[v] ? blk[v] : -1;
                }
                gp[sig].push_back(u);
            }
            if (gp.size() == 1) {
                int id = tmp_blks.size();
                tmp_blks.push_back(b);
                for (int u: b) new_blk[u] = id;
            } else {
                chg = true;
                for (auto &[_, vec]: gp) { // 忽略键
                    int id = tmp_blks.size();
                    tmp_blks.push_back(vec);
                    for (int u: vec) new_blk[u] = id;
                }
            }
        }
        
        blocks = move(tmp_blks);
        memcpy(blk, new_blk, sizeof(blk));
    }

    grp = move(blocks);
    memset(tab, -1, sizeof(tab));
    for (int i = 0; i < grp.size(); ++i) {
        for (int u : grp[i]) tab[u] = i;
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> K;
    if (K) {
        flg.resize(K);
        for (int i = 0; i < K; ++i) cin >> flg[i], isflg[flg[i]] = true;
    } else { int tmp; cin >> tmp; }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> f[i][j];
        }
    }
    preprocess();
    part();

    int n2 = grp.size();
    int new_id[MAXN], rev[MAXN];
    memset(new_id, -1, sizeof(new_id));
    queue<int> q;
    
    int st = tab[0];
    new_id[st] = 0;
    rev[0] = st;
    q.push(st);
    
    int cnt = 1;
    while (!q.empty()) {
        int cur = q.front(); q.pop();
        int rep = grp[cur][0];
        for (int i = 0; i < m; ++i) {
            int nxt = tab[f[rep][i]];
            if (new_id[nxt] == -1) {
                new_id[nxt] = cnt;
                rev[cnt++] = nxt;
                q.push(nxt);
            }
        }
    }
    
    cout << n2 << ' ' << m << '\n';
    vector<int> new_flg;
    for (int i = 0; i < n2; ++i) {
        int orig = rev[i];
        for (int u : grp[orig]) {
            if (isflg[u]) {
                new_flg.push_back(i);
                break;
            }
        }
    }
    cout << new_flg.size();
    for (int x : new_flg) 
        cout << ' ' << x;
    cout << '\n';
    for (int i = 0; i < n2; ++i) {
        int orig = rev[i];
        int rep = grp[orig][0];
        for (int j = 0; j < m; ++j) {
            int nxt = tab[f[rep][j]];
            cout << new_id[nxt] << " \n"[j == m-1];
        }
    }
    return 0;
}