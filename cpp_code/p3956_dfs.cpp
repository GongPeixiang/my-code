#include <bits/stdc++.h>
using namespace std;

const array<pair<int, int>, 4> directions = {{
    {-1, 0}, {0, -1}, {0, 1}, {1, 0}
}};

vector<vector<int>> board;
vector<vector<bool>> vis;
int min_cost = -1;

void dfs(int r, int c, int cost, int type, int mt) 
{
    if (r == board.size() - 1 && c == board.size() - 1) {
        if (min_cost == -1) 
            min_cost = cost;
        else
            min_cost = min(min_cost, cost);
        return;
    }

    vis[r][c] = true;

    for (int i = 0; i < 4; i++) {
        int nr = r + directions[i].first, nc = c + directions[i].second;

        if (nr < 0 || nr >= board.size() || nc < 0 || nc >= board.size()
            || vis[nr][nc]) 
            continue;

        int new_cost, new_mt = 1e5;
        if (type == -1) {
            if (board[nr][nc] == -1) 
                continue;
            else if (board[nr][nc] == mt) 
                new_cost = cost;
            else 
                new_cost = cost + 1;

            dfs(nr, nc, new_cost, board[nr][nc], new_mt);
        } else {
            if (board[nr][nc] == -1) {
                new_cost = cost + 2;
                new_mt = type;
            } else if (board[nr][nc] == type) 
                new_cost = cost;
            else 
                new_cost = cost + 1;
            
            dfs(nr, nc, new_cost, board[nr][nc], new_mt);
        }
    }

    vis[r][c] = false;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n;
    cin >> m >> n;
    board.resize(m, vector<int>(m, -1));
    vis.resize(m, vector<bool>(m, false));
    int r, c, t;
    for (int i = 0; i < n; i++) {
        cin >> r >> c >> t;
        r--, c--;
        board[r][c] = t;
    }

    dfs(0, 0, 0, board[0][0], 1e5);

    cout << min_cost << '\n';
}