#include <bits/stdc++.h>
using namespace std;

typedef unsigned char uc;

const int N = 300;

char buf[N], part[N][N], args[256][N];
bool seen[256], par[256], vis[256];

void scan() {
    char* tok = strtok(buf, " ");
    int n = 0;
    while (tok) {
        memcpy(part[n], tok, sizeof(part[n]));
        tok = strtok(nullptr, " ");
        n++;
    }
    for (int i = 1; i < n;) {
        char c = part[i][1];
        if (part[i][0] != '-') return;
        if (strlen(part[i]) != 2) return;
        if (!seen[(uc)c]) return;
        if (par[(uc)c]) {
            if (i < n-1) {
                vis[(uc)c] = 1;
                memcpy(args[(uc)c], part[i+1], sizeof(args[(uc)c]));
                i += 2;
            } else return;
        } else {
            vis[(uc)c] = 1;
            i++;
        }
    }
}

int main() {
    scanf("%s", buf);
    for (char* p = buf; *p;) {
        char c = *p;
        seen[(uc)c] = 1;
        char* np = p + 1;
        if (*np && *np == ':') {
            par[(uc)c] = 1;
            p++;
        } else if (*np == '\0') break;
        p++;
    }
    int T;
    scanf("%d", &T);
    while (getchar() != '\n') ;
    for (int kase = 1; kase <= T; kase++) {
        memset(vis, 0, sizeof(vis));
        fgets(buf, sizeof(buf), stdin);
        buf[strcspn(buf,"\r\n")] = '\0';
        scan();
        printf("Case %d:", kase);
        for (unsigned i = 0; i < 256; i++) {
            if (!seen[i] || !vis[i]) continue;
            printf(" -%c", i);
            if (par[i]) printf(" %s", args[i]);
        }
        putchar('\n');
    }
    return 0;
}