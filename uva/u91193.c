#include <stdio.h>

#define N 1024 // 2^10 = 1024

int n, board[N][N], cnt = 1;

void draw(int tr, int tc, int dr, int dc, int sz) 
{
    if (sz == 1) return;
    int t = cnt++, s = sz / 2;

    if (dr < tr + s && dc < tc + s) draw(tr, tc, dr, dc, s);
    else {
        board[tr+s-1][tc+s-1] = t;
        draw(tr, tc, tr + s - 1, tc + s - 1, s);
    }

    if (dr < tr + s && dc >= tc + s) draw(tr, tc + s, dr, dc, s);
    else {
        board[tr+s-1][tc+s] = t;
        draw(tr, tc + s, tr + s - 1, tc + s, s);
    }

    if (dr >= tr + s && dc < tc + s) draw(tr + s, tc, dr, dc, s);
    else {
        board[tr+s][tc+s-1] = t;
        draw(tr + s, tc, tr + s, tc + s - 1, s);
    }

    if (dr >= tr + s && dc >= tc + s) draw(tr + s, tc + s, dr, dc, s);
    else {
        board[tr+s][tc+s] = t;
        draw(tr + s, tc + s, tr + s, tc + s, s);
    }
}

int main() 
{
    int k, cx, cy;
    scanf("%d %d %d", &k, &cx, &cy);
    n = k ? (1 << k) : 1;
    --cx; --cy;
    draw(0, 0, cx, cy, n);
    for (int i = 0; i < n; ++i) 
        for (int j = 0; j < n; ++j) 
            printf("%d%c", board[i][j], " \n"[j == n-1]);
    return 0;
}