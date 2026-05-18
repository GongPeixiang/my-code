#include<bits/stdc++.h>
using namespace std;

const array<array<int, 2>, 4> dir = {{ {-1, 0}, {0, -1}, {1, 0}, {0, 1} }};

int r, c;
vector<vector<int>> height, memo;

int maxlength(int row, int col) {
    if (memo[row][col] != 0) 
        return memo[row][col];
    int max_length = 1;
    for (int i = 0; i < 4; i++) {
        int _row = row + dir[i][0];
        int _col = col + dir[i][1];
        if (_row >= 0 && _row < r && _col >= 0 && _col < c 
            && height[_row][_col] < height[row][col]) {
            max_length = max(max_length, 1 + maxlength(_row, _col));
        }
    }
    memo[row][col] = max_length;
    return max_length;
}

int main() {
    cin >> r >> c;
    height.resize(r, vector<int>(c));
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            cin >> height[i][j];
        }
    }
    memo.resize(r, vector<int>(c,0));
    int ans = 0;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            ans = max(ans, maxlength(i, j));
        }
    }
    cout << ans << '\n';
    return 0;
}