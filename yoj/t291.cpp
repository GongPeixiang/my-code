#include <bits/stdc++.h>
using namespace std;

const int N = 20005;

char s, a[N], b[N], ans[N], tmp[N];
int x[N], y[N], res[N];

void add(bool flg) { // flg for '-'
    int la = strlen(a), lb = strlen(b);
    for (int i = 0; i < la; i++) x[i] = a[la-1-i] - '0';
    for (int j = 0; j < lb; j++) y[j] = b[lb-1-j] - '0';
    int l = max(la, lb);
    for (int i = 0; i < l; i++) {
        res[i] += x[i] + y[i];
        res[i+1] += res[i] / 10;
        res[i] %= 10;
    }
    while (res[l] == 0 && l > 0) l--;
    int cnt = 0;
    if (flg) ans[cnt++] = '-';
    for (int i = l; i >= 0; i--) ans[cnt++] = (char)(res[i] + '0');
    ans[cnt++] = '\0';
}

void subs() {
    int la = strlen(a), lb = strlen(b);
    bool flg = 0;
    if (la < lb || la==lb && strcmp(a,b)<0) {
        strcpy(tmp, a);  strcpy(a, b);  strcpy(b, tmp);
        flg = 1;
    }
    la = strlen(a), lb = strlen(b);
    for (int i = 0; i < la; i++) x[i] = a[la-1-i] - '0';
    for (int j = 0; j < lb; j++) y[j] = b[lb-1-j] - '0';
    for (int i = 0; i < la; i++) {
        res[i] += x[i] - y[i];
        if (res[i] < 0) {
            res[i+1] -= 1;
            res[i] += 10;
        }
    }
    int l = la;
    while (res[l] == 0 && l > 0) l--;
    int cnt = 0;
    if (flg) ans[cnt++] = '-';
    for (int i = l; i >= 0; i--) ans[cnt++] = (char)(res[i] + '0');
    ans[cnt++] = '\0';
}

inline void rm_neg(char* str) {
    int l = strlen(str);
    memmove(str, str + 1, (l-1)*sizeof(char));
    str[l-1] = '\0';
}

int main() {
    scanf("%c%s%s", &s, a, b);
    if (s == '+') {
        if (a[0]!='-' && b[0]!='-') {
            add(0);
        } else if (a[0]!='-' && b[0]=='-') {
            rm_neg(b);
            subs();
        } else if (a[0]=='-' && b[0]!='-') {
            rm_neg(a);
            strcpy(tmp, a); strcpy(a, b); strcpy(b, tmp);
            subs();
        }
        else {
            rm_neg(a);  rm_neg(b);
            add(1);
        }
    }
    else {
        if (a[0]!='-' && b[0]!='-') {
            subs();
        } else if (a[0]!='-' && b[0]=='-') {
            rm_neg(b);
            add(0);
        } else if (a[0]=='-' && b[0]!='-') {
            rm_neg(a);
            add(1);
        } else {
            rm_neg(a); rm_neg(b);
            strcpy(tmp, a); strcpy(a, b); strcpy(b, tmp);
            subs();
        }
    }
    printf("%s\n", ans);
    return 0;
}