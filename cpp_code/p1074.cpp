#include <bits/stdc++.h>
using namespace std;

constexpr array<array<int, 9>, 9> score = {{
    {6, 6, 6, 6, 6, 6, 6, 6, 6},
    {6, 7, 7, 7, 7, 7, 7, 7, 6},
    {6, 7, 8, 8, 8, 8, 8, 7, 6},
    {6, 7, 8, 9, 9, 9, 8, 7, 6},
    {6, 7, 8, 9, 10, 9, 8, 7, 6},
    {6, 7, 8, 9, 9, 9, 8, 7, 6},
    {6, 7, 8, 8, 8, 8, 8, 7, 6},
    {6, 7, 7, 7, 7, 7, 7, 7, 6},
    {6, 6, 6, 6, 6, 6, 6, 6, 6}
}};
array<array<int, 9>, 9> board;
array<array<bool, 9>, 9> rowContain, colContain, unitContain;
int max_sum = -1;

inline int get_unit(int r, int c) {
    return (r / 3) * 3 + (c / 3);
}

void dfs(int idx, int sum) {
    if (idx == 81) {
        max_sum = max(max_sum, sum);
        return;
    }

    int r = idx / 9, c = idx % 9;
    int u = get_unit(r, c);

    if (board[r][c] != -1) {
        dfs(idx + 1, sum + (board[r][c] + 1) * score[r][c]);
        return;
    }

    for (int i = 0; i < 9; ++i) {
        if ( rowContain[r][i] || colContain[c][i] || unitContain[u][i] ) 
            continue;
        board[r][c] = i;
        rowContain[r][i] = colContain[c][i] = unitContain[u][i] = true;
        dfs(idx + 1, sum + (i + 1) * score[r][c]);
        rowContain[r][i] = colContain[c][i] = unitContain[u][i] = false;
        board[r][c] = -1;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    for (int i = 0; i < 9; ++i) {
        rowContain[i].fill(false);
        colContain[i].fill(false);
        unitContain[i].fill(false);
    }
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            cin >> board[i][j];
            int tmp = --board[i][j]; // 0-based index
            if (tmp != -1) {
                int u = get_unit(i, j);
                rowContain[i][tmp] = colContain[j][tmp] = unitContain[u][tmp] = true;
            }
        }
    }
    dfs(0, 0);
    cout << max_sum << '\n';
}