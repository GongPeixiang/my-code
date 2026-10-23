#include <bits/stdc++.h>
using namespace std;

const int LEN = 10;

char in[LEN], post[LEN];
string pre;

void build(int il, int ir, int pl, int pr) {
    if (il > ir || pl > pr) return;
    char root = post[pr];
    pre += root;
    int k;
    for (k = il; k <= ir; k++) if (in[k] == root) break;
    int sz = k - il;
    build(il, k-1, pl, pl+sz-1);
    build(k+1, ir, pl+sz, pr-1);
}

int main() {
    scanf("%s%s", in, post);
    int n = strlen(in);
    build(0, n-1, 0, n-1);
    printf("%s\n", pre.c_str());
    return 0;
}