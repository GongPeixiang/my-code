#include <bits/stdc++.h>
using namespace std;

const int N = 10005;

int n, m, nxt[N][26], tot = 0;
bool exist[N], vis[N];

void insert(char* s) {
    int l = strlen(s), p = 0;
    for (int i = 0; i < l; i++) {
        int c = s[i] - 'a';
        if (!nxt[p][c]) nxt[p][c] = ++tot;
        p = nxt[p][c];
    }
    exist[p] = 1;
}

int find(char* s) {
    int l = strlen(s), p = 0;
    for (int i = 0; i < l; i++) {
        int c = s[i] - 'a';
        if (!nxt[p][c]) return -1;
        p = nxt[p][c];
    }
    return exist[p] ? p : -1;
}

int main() {
    char buf[55];
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf(" %s", buf);
        insert(buf);
    }
    scanf("%d", &m);
    while (m--) {
        scanf(" %s", buf);
        int p = find(buf);
        if (~p) {
            if (vis[p]) printf("REPEAT\n");
            else {
                vis[p] = 1;
                printf("OK\n");
            }
        } else printf("WRONG\n");
    }
    return 0;
}