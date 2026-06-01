#include <bits/stdc++.h>
using namespace std;

constexpr int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};
const string dirs = "NESW", turns = "LFR";

int sr, sc, dr, dc, sdir;
bool vis[10][10][4], ok[10][10][4][3]; // (i+3)%4, i%4, (i+1)%4
struct Node {
    int r, c, dir;
} pre[10][10][4];
vector<Node> path;

inline int get_dir(char d) { return dirs.find(d); }

inline int get_turn(char d) { return turns.find(d); }

void solve() {
    memset(vis, 0, sizeof(vis));
    memset(pre, 0xff, sizeof(pre));
    queue<Node> q;
    int nr = sr + dx[sdir], nc = sc + dy[sdir];
    vis[nr][nc][sdir] = true;
    pre[nr][nc][sdir] = Node{sr, sc, sdir};
    q.push(Node{nr, nc, sdir});
    while (!q.empty()) {
        Node cur = q.front();
        int r = cur.r, c = cur.c, dir = cur.dir;
        q.pop();
        if (r == dr && c == dc) {
            Node trk = cur;
            while (1) {
                if (trk.r == -1) break;
                path.push_back(trk);
                trk = pre[trk.r][trk.c][trk.dir];
            }
            reverse(path.begin(), path.end());
            return;
        }
        for (int i = 0; i < 3; ++i) {
            if (!ok[r][c][dir][i]) continue;
            int ndir = (dir - 1 + i + 4) % 4;
            int nr = r + dx[ndir], nc = c + dy[ndir];
            if (nr < 1 || nr > 9 || nc < 1 || nc > 9) continue;
            if (!vis[nr][nc][ndir]) {
                vis[nr][nc][ndir] = true;
                pre[nr][nc][ndir] = cur;
                q.push(Node{nr, nc, ndir});
            }
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    string name;
    while (cin >> name, name != "END") {
        path.clear();
        memset(ok, 0, sizeof(ok));
        char ds;
        cin >> sr >> sc >> ds >> dr >> dc;
        cin.ignore();
        sdir = get_dir(ds);
        string line, tok;
        int r, c;
        while (1) {
            getline(cin, line);
            stringstream ss(line);
            ss >> r;
            if (!r) break;
            ss >> c;
            while (ss >> tok) {
                if (tok == "*") break;
                int di = get_dir(tok[0]);
                for (int j = 1; j < tok.size(); ++j) {
                    int t = get_turn(tok[j]);
                    ok[r][c][di][t] = true;
                }
            }
        }
        solve();
        cout << name << "\n";
        int cnt = 0;
        if (path.empty()) 
            cout << "  No Solution Possible\n";
        else {
            for (int i = 0; i < path.size(); ++i) {
                if (i % 10 == 0) cout << ' ';
                cout << " (" << path[i].r << ',' << path[i].c << ')';
                if ((i + 1) % 10 == 0 || i == path.size() - 1) 
                    cout << '\n';
            }
        }
    }
    return 0;
}