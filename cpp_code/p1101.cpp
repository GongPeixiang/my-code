#include <bits/stdc++.h>
using namespace std;

const array<array<int, 2>, 8> dir = {{ {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1} }};
const string word = "yizhong";

int n;
vector<vector<char>> matrix;

void dfs(int row, int col, const int &d, int word_ptr, vector<vector<bool>> &inword) {
    if (word_ptr == 6) {
        int r = row, c = col;
        for (int i = 0; i <= 6; i++) {
            inword[r][c] = true;
            r -=  dir[d][0];
            c -=  dir[d][1];
        }
        return;
    }
    int _row = row + dir[d][0];
    int _col = col + dir[d][1];
    if (!(_row >= 0 && _row < n && _col >= 0 && _col < n)) return;
    if (matrix[_row][_col] == word[word_ptr + 1]) {
        dfs(_row, _col, d, word_ptr + 1, inword);
    }
}

int main() {
    cin >> n;
    matrix.resize(n, vector<char>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> matrix[i][j];
        }
    }

    vector<vector<bool>> inword(n, vector<bool>(n, false));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == 'y') {
                for (int d = 0; d < 8; d++) {
                    dfs(i, j, d, 0, inword);
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (inword[i][j]) cout << matrix[i][j];
            else cout << '*';
        }
        cout << '\n';
    }

    return 0;
}