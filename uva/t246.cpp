#include <bits/stdc++.h>
using namespace std;

constexpr int P = 7;

vector<int> pile[P]; bool del[P];
queue<int> hand;
int flg = -1;

string stat_hash() {
    string state;
    queue<int> tmp = hand;
    while (!tmp.empty()) {
        state += char('0' + tmp.front());
        tmp.pop();
    }
    state += "|";
    for (int i = 0; i < P; ++i) {
        if (del[i]) state += "E";
        else for(int card : pile[i]) state += char('0' + card);
        state += ",";
    }
    return state;
}

bool fix(int id) {
    while (true) {
        auto& p = pile[id];
        int n = p.size();
        if (n < 3) break;
        int a = p[n-1] + p[1] + p[0];
        int b = p[n-1] + p[n-2] + p[0];
        int c = p[n-1] + p[n-2] + p[n-3];
        if (a == 10 || a == 20 || a == 30) {
            int v1 = p[0], v2 = p[1], v3 = p[n-1];
            p.erase(p.begin()); p.erase(p.begin()); p.pop_back();
            hand.push(v1); hand.push(v2); hand.push(v3);
        } else if (b == 10 || b == 20 || b == 30) {
            int v1 = p[0], v2 = p[n-2], v3 = p[n-1];
            p.pop_back(); p.pop_back(); p.erase(p.begin());
            hand.push(v1); hand.push(v2); hand.push(v3);
        } else if (c == 10 || c == 20 || c == 30) {
            int v1 = p[n-3], v2 = p[n-2], v3 = p[n-1];
            p.pop_back(); p.pop_back(); p.pop_back();
            hand.push(v1); hand.push(v2); hand.push(v3);
        } else break;
    }
    return pile[id].empty();
}

int solve() {
    flg = -1;
    int step = 0;
    memset(del, 0, sizeof(del));
    unordered_set<string> vis;
    while (!hand.empty()) {
        bool all_del = true;
        for (int i = 0; i < P && !hand.empty(); ++i) {
            if (del[i]) continue;
            all_del = false;
            ++step;
            pile[i].push_back(hand.front());
            hand.pop();
            if (fix(i)) del[i] = true;
            string cur = stat_hash();
            if (vis.count(cur)) { flg = -1; return step; }
            vis.insert(cur);
        }
        if (all_del) { flg = 1; break; }
    }
    for (int i = 0; i < P; ++i)
        if (!del[i]) { flg = 0; break; }
    return step;
}

int main() {
    int a;
    while (1) {
        for (int i = 0; i < P; ++i) pile[i].clear();
        while (!hand.empty()) hand.pop();
        memset(del, 0, sizeof(del));
        for (int i = 0; i < 52 && scanf("%d", &a) == 1 && a; ++i)
            hand.push(a);
        if (hand.empty()) break;
        int step = solve();
        char state[10];
        switch(flg) {
            case -1: strcpy(state, "Draw"); break;
            case 0: strcpy(state, "Loss"); break;
            case 1: strcpy(state, "Win "); break;
        }
        printf("%s: %d\n", state, step);
    }
    return 0;
}
