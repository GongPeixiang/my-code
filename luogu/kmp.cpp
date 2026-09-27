#include <bits/stdc++.h>
using namespace std;

const int N = 1000500;

int n, m, nxt[N];
char txt[N], pat[N];
vector<int> pos;

void get_nxt() {
    memset(nxt, 0, sizeof(nxt));
    int j = 0;
    for (int i = 1; i < m; i++) {
        while (j > 0 && pat[i] != pat[j]) j = nxt[j-1];
        if (pat[i] == pat[j]) j++;
        nxt[i] = j;
    }
}

void kmp() {
    get_nxt();
    int j = 0;
    for (int i = 0; i < n; i++) {
        while (j > 0 && txt[i] != pat[j]) j = nxt[j-1];
        if (txt[i] == pat[j]) j++;
        if (j == m) {
            pos.push_back(i - m + 1);
            j = nxt[j-1];
        }
    }
}

int main() {
    scanf("%s %s", txt, pat);
    n = strlen(txt); m = strlen(pat);
    kmp();
    for (int i = 0; i < pos.size(); i++) printf("%d\n", pos[i]);
    for (int i = 0; i < m; i++) printf("%d%c", nxt[i], " \n"[i==m-1]);
    return 0;
}