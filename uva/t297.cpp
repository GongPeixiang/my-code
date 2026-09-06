#include <bits/stdc++.h>
using namespace std;

const int N = 32, L = 1024;

char str[L];
int dep = 0, g[N][N], cnt = 0;

void draw(int r, int c, int len) {
    char ch = str[dep++];
    if (ch == 'f') {
        for (int i = r; i < r + len; i++) {
            for (int j = c; j < c + len; j++) {
                if (g[i][j]) continue;
                g[i][j] = 1;
                cnt++;
            }
        }
        return;
    } else if (ch == 'p') {
        len /= 2;
        draw(r + len, c, len);
        draw(r, c, len);
        draw(r, c + len, len);
        draw(r + len, c + len, len);
    }
    return;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        memset(g, 0, sizeof(g));  cnt = 0;
        dep = 0;
        scanf("%s", str);
        draw(0, 0, N);
        dep = 0;
        scanf("%s", str);
        draw(0, 0, N);
        printf("There are %d black pixels.\n", cnt);
    }
    return 0;
}