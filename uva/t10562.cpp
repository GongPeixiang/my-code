#include <bits/stdc++.h>
using namespace std;

const int N = 550;

char g[N][N], str[N];
int n = 0, p = 0;

void sft(int dep, int l, int r) {
    for (int i = l; i <= r; i++) {
        if (g[dep][i] != ' ' && g[dep][i] != '\0') {
            str[p++] = g[dep][i];
            str[p++] = '(';
            if (g[dep+1][i] == '|') {
                int nl = i, nr = i;
                while (g[dep+2][nl] == '-') nl--;
                while (g[dep+2][nr] == '-') nr++;
                nl++; nr--;
                if (nl < 0) nl = 0;
                if (dep + 3 < n) sft(dep + 3, nl, nr);
            }
            str[p++] = ')';
        }
    }
}

int main() {
    int T;
    scanf("%d", &T);
    while (getchar() != '\n');
    while (T--) {
        memset(g, '\0', sizeof(g));
        n = 0;
        while (1) {
            fgets(g[n], sizeof(g[n]), stdin);
            g[n][strcspn(g[n], "\r\n")] = '\0';
            if (strcmp(g[n], "#")==0) break;
            n++;
        }
        p = 0;
        str[p++] = '(';
        if (n) {
            int l = 0, r = strlen(g[0]) - 1;
            sft(0, l, r);
        }
        str[p++] = ')';
        str[p++] = '\0';
        printf("%s\n", str);
    }
    return 0;
}