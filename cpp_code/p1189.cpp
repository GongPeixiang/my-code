#include <bits/stdc++.h>
using namespace std;

int R, C, N;
vector<vector<char>> road;
vector<string> dirSeq;

const array<array<int, 2>, 4> dir = {{ {-1, 0}, {1, 0}, {0, -1}, {0, 1} }};
enum class direction : int {
    NORTH = 0,
    SOUTH,
    WEST,
    EAST
};

void dfs(int r, int c, int depth) 
{
    if (depth == N) {
        road[r][c] = '*';
        return;
    }

    int idx;
    if (dirSeq[depth] == "NORTH") 
        idx = static_cast<int>(direction::NORTH);
    else if (dirSeq[depth] == "SOUTH") 
        idx = static_cast<int>(direction::SOUTH);
    else if (dirSeq[depth] == "WEST") 
        idx = static_cast<int>(direction::WEST);
    else if (dirSeq[depth] == "EAST") 
        idx = static_cast<int>(direction::EAST);

    int nr = r + dir[idx][0], nc = c + dir[idx][1];
    for (; nr >= 0 && nr < R && nc >= 0 && nc < C; nr += dir[idx][0], nc += dir[idx][1]) {
        if (road[nr][nc] == 'X') 
            break;
        dfs(nr, nc, depth + 1);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int startR, startC;
    cin >> R >> C;
    road.resize(R, vector<char>(C)); 
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            cin >> road[i][j];
            if (road[i][j] == '*') 
                startR= i, startC = j;
        }
    }
    cin >> N;
    dirSeq.resize(N);
    for (int i = 0; i < N; i++) {
        cin >> dirSeq[i];
    }

    dfs(startR, startC, 0);
    road[startR][startC] = '.';

    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            cout << road[i][j];
        }
        cout << '\n';
    }

    return 0;
}