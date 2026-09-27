#include <bits/stdc++.h>
using namespace std;

constexpr int dx[8] = {-1, -1, -1, 0, 1, 1, 1, 0}, dy[8] = {1, 0, -1, -1, -1, 0, 1, 1};
constexpr int MAXN = 105;
const string word = "yizhong";

int n;
char mat[MAXN][MAXN];
bool inword[MAXN][MAXN];

void dfs(int r, int c, const int d, int tp) {
    if (tp == 6) {
        int R = r, C = c;
        for (int i = 0; i < word.size(); i++) {
            inword[R][C] = true;
            R -=  dx[d];
            C -=  dy[d];
        }
        return;
    }
    int nr = r + dx[d], nc = c + dy[d];
    if (nr < 0 && nr >= n && nc < 0 && nc >= n) return;
    if (mat[nr][nc] == word[tp+1]) 
        dfs(nr, nc, d, tp + 1);
}

int main() {
    memset(inword, 0, sizeof(inword));
    cin >> n;
    for (int i = 0; i < n; i++) 
        for (int j = 0; j < n; j++) 
            cin >> mat[i][j];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (mat[i][j] == 'y') {
                for (int d = 0; d < 8; ++d) 
                    dfs(i, j, d, 0);
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (inword[i][j]) cout << mat[i][j];
            else cout << '*';
        }
        cout << '\n';
    }
    return 0;
}