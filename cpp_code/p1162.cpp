#include <bits/stdc++.h>
using namespace std;

const array<array<int, 2>, 4> dir = {{ {-1, 0}, {0, -1}, {1, 0}, {0, 1} }};
int n;
vector<vector<int>> matrix;

bool inCircle(int row, int col, vector<vector<int>> &memo) {
    if (memo[row][col] != -1) {
        return memo[row][col] == 1 ? true : false;
    }
    if (row == 0 || row == n - 1 || col == 0 || col == n - 1) {
        memo[row][col] = 0;
        return false;
    }
    memo[row][col] = 2; // 正在访问中
    for (int i = 0; i < 4; i++) {
        int _row = row + dir[i][0];
        int _col = col + dir[i][1];
        if (_row < 0 || _row >= n || _col < 0 || _col >= n || matrix[_row][_col] == 1  || memo[_row][_col] == 2) continue;
        if (!inCircle(_row, _col, memo)) {
            memo[row][col] = 0;
            return false;
        }  
    }
    memo[row][col] = 1;
    return true;
}

int main() {
    cin >> n;
    matrix.resize(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> matrix[i][j];
        }
    }

    // 处理环会出问题，虽然确实有点巧妙……

    // 四色标记（已访问且在闭合圈内，已访问且在闭合圈外，正在访问中，未访问）
    vector<vector<int>> memo(n, vector<int>(n, -1));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == 0 && inCircle(i, j, memo)) {
                cout << 2 << ' ';
            }
            else cout << matrix[i][j] << ' ';
        }
        cout << '\n';
    }
    return 0;
}