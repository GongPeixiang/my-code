#include <bits/stdc++.h>
using namespace std;

deque<int> pile[7];
queue<int> q;
bool ok[7], tgt[7] ={0,0,0,0,0,0,0};

// 只有这种并不优雅的方法判重
struct State {
    deque<int> _p[7];
    queue<int> _q;
    bool operator<(const State& other) const {
        for (int i = 0; i < 7; i++) 
            if (_p[i] != other._p[i]) return _p[i] < other._p[i];
        return _q < other._q;
    }
};
set<State> s;

int solve(int& ans) { // -1:loss; 0:draw; 1:win
    ans = 0;
    for (int i = 0; i < 7; i++) {
        int num = q.front(); q.pop();
        ans++;
        pile[i].push_back(num);
    }
    memset(ok, 1, sizeof(ok));
    int id = -1;
    State stat;
    while (!q.empty()) {
        if (memcmp(ok, tgt, sizeof(tgt))==0) return 1;
        // if (q.size() == 52) return 0;
        for (int i = 0; i < 7; i++) stat._p[i] = pile[i];
        stat._q = q;
        if (s.count(stat)) return 0;
        s.insert(stat);
        ans++;
        int num = q.front(); q.pop();
        id = (id + 1) % 7;
        while (!ok[id]) id = (id + 1) % 7;
        pile[id].push_back(num);
        int sz = pile[id].size();
        while (sz >= 3) {
            int s1 = pile[id][0] + pile[id][1] + pile[id].back();
            int s2 = pile[id][0] + pile[id][sz-2] + pile[id].back();
            int s3 = pile[id][sz-3] + pile[id][sz-2] + pile[id].back();
            if (s1 % 10 == 0) {
                q.push(pile[id][0]); 
                q.push(pile[id][1]);
                q.push(pile[id].back());
                pile[id].pop_front();
                pile[id].pop_front();
                pile[id].pop_back();
                if (pile[id].empty()) ok[id] = false;
            } else if (s2 % 10 == 0) {
                q.push(pile[id][0]); 
                q.push(pile[id][sz-2]);
                q.push(pile[id].back());
                pile[id].pop_front();
                pile[id].pop_back();
                pile[id].pop_back();
                if (pile[id].empty()) ok[id] = false;
            } else if (s3 % 10 == 0) {
                q.push(pile[id][sz-3]);
                q.push(pile[id][sz-2]);
                q.push(pile[id][sz-1]);
                pile[id].pop_back();
                pile[id].pop_back();
                pile[id].pop_back();
                if (pile[id].empty()) ok[id] = false;
            } else break;
            sz = pile[id].size();
        }

    }
    return -1;
}

int main() {
    int num;
    while (1) {
        for (int i = 0; i < 7; i++) pile[i].clear();
        // queue<int>().swap(q);
        while (q.size()) q.pop();
        s.clear();
        for (int i = 0; i < 52; i++) {
            scanf("%d", &num);
            if (!num) return 0;
            q.push(num);
        }
        int ans = 0;
        int flg = solve(ans);
        if (flg == -1)     printf("Loss: %d\n", ans);
        else if (flg == 0) printf("Draw: %d\n", ans);
        else if (flg == 1) printf("Win : %d\n", ans);
    }
    return 0;
}