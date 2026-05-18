#include <bits/stdc++.h> 
using namespace std;

const array<array<int, 2>, 4> mov_dir = {{ {-1, 0}, {0, -1}, {0, 1}, {1, 0} }};

array<array<int, 4>, 2> rowCnt, colCnt; // 0 for white, 1 for black
array<int, 2> leftCnt, rightCnt;
array<array<char, 4>, 4> board;

void find_zero(array<pair<int, int>, 2> &zero) 
{
    int cnt = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (board[i][j] == 'O') 
                zero[cnt++] = make_pair(i, j);
        }
    }
}

bool judge() 
{
    for (int i = 0; i < 4; i++) {
        if (rowCnt[0][i] == 4 || rowCnt[1][i] == 4 ) 
            return true;
        if (colCnt[0][i] == 4 || colCnt[1][i] == 4) 
            return true;        
    }
    return (leftCnt[0] == 4 || leftCnt[1] == 4 || rightCnt[0] == 4 || rightCnt[1] == 4);
}

int heuristic() 
{
    auto w_it_r = max_element(rowCnt[0].begin(), rowCnt[0].end());
    auto w_it_c = max_element(colCnt[0].begin(), colCnt[0].end());
    // 行和列取出最大，左右对角线取出最大 => 白子总的最大值
    int white_max = max(max(*w_it_r, *w_it_c), max(leftCnt[0], rightCnt[0]));

    auto b_it_r = max_element(rowCnt[1].begin(), rowCnt[1].end());
    auto b_it_c = max_element(colCnt[1].begin(), colCnt[1].end());
    int black_max = max(max(*b_it_r, *b_it_c), max(leftCnt[1], rightCnt[1]));

    return 4 - max(white_max, black_max);
}

bool dfs(int depth, const int max_depth, int prev_color) 
{
    if (depth == max_depth) 
        return judge();

    int h = heuristic();
    if (depth + h > max_depth) 
        return false;

    array<pair<int, int>, 2> zero;
    find_zero(zero);
    
    for (int i = 0; i < 2; i++) {
        int zr = zero[i].first, zc = zero[i].second;
        for (int d = 0; d < 4; d++) {
            int nr = zr + mov_dir[d][0], nc = zc + mov_dir[d][1];

            if (nr < 0 || nr >= 4 || nc < 0 || nc >= 4) 
                continue;
            if (board[nr][nc] == 'O') 
                continue;
            
            int color = board[nr][nc] == 'W' ? 0 : 1;
            if (color == prev_color) 
                continue;

            rowCnt[color][nr]--, colCnt[color][nc]--, rowCnt[color][zr]++, colCnt[color][zc]++; 
            if (nr == nc) 
                leftCnt[color]--;
            if (nr == 3 - nc) 
                rightCnt[color]--;

            swap(board[zr][zc], board[nr][nc]);

            if (dfs(depth + 1, max_depth, color)) 
                return true;

            swap(board[zr][zc], board[nr][nc]);

            rowCnt[color][nr]++, colCnt[color][nc]++, rowCnt[color][zr]--, colCnt[color][zc]--; 
            if (nr == nc) 
                leftCnt[color]++;
            if (nr == 3 - nc) 
                rightCnt[color]++;            
        }
    }
    return false;
}

int ida_star() 
{
    if (judge()) 
        return 0;
    for (int max_depth = 1; ; max_depth++) {
        if (dfs(0, max_depth, -1)) 
            return max_depth;
    }
}

int main() 
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cin >> board[i][j];
            switch (board[i][j]) {
            case 'W': {
                rowCnt[0][i]++;
                colCnt[0][j]++;
                if (i == j) 
                    leftCnt[0]++;
                if (i == 3 - j) 
                    rightCnt[0]++;
                break;
            }
            case 'B': {
                rowCnt[1][i]++;
                colCnt[1][j]++;
                if (i == j) 
                    leftCnt[1]++;
                if (i == 3 - j) 
                    rightCnt[1]++;
                break;
            }
            default: break;
            }
        }
    }

    int ans = ida_star();
    cout << ans << '\n';

    return 0;
}