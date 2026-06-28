#include <bits/stdc++.h>
using namespace std;

const array<array<int, 2>, 4> dir = {{ {-1, 0}, {0, -1}, {1, 0}, {0, 1} }};
int R, C;
vector<vector<int>> height, memo;

struct Node {
    int r, c;
    int dir_record;
    Node(int r, int c, int d): r(r), c(c), dir_record(d) {}
};

inline bool is_valid(int r, int c) {
    return r >= 0 && r < R && c >= 0 && c < C;
}

int max_len(int row, int col) {
    if (memo[row][col] != -1) 
        return memo[row][col];
    
    stack<Node> stk;
    stk.push(Node(row, col, 0));
    
    while (!stk.empty()) {
        Node &cur = stk.top();
        int r = cur.r, c = cur.c;
        int &i = cur.dir_record;
        
        if (i < 4) {
            for (; i < 4; i++) {
                int nr = r + dir[i][0], nc = c + dir[i][1];
                if (!is_valid(nr, nc) || height[nr][nc] >= height[r][c]) 
                    continue;
                if (memo[nr][nc] == -1) {
                    stk.push(Node(nr, nc, 0));
                    break;
                }
            }
        } 
        else {
            int max_len = 1;
            for (int k = 0; k < 4; k++) {
                int nr = r + dir[k][0], nc = c + dir[k][1];
                if (!is_valid(nr, nc) || height[nr][nc] >= height[r][c]) 
                    continue;
                max_len = max(max_len, 1 + memo[nr][nc]);
            }
            memo[r][c] = max_len;
            stk.pop();  // 当前栈帧操作结束
        }
    }
    
    return memo[row][col];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> R >> C;
    height.resize(R, vector<int>(C));
    memo.resize(R, vector<int>(C, -1));
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            cin >> height[i][j];
        }
    }

    int ans = 0;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            ans = max(ans, max_len(i, j));
        }
    }

    cout << ans << '\n';
}