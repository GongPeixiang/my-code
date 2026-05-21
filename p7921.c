#include <stdio.h>

#define MAXN 200005

struct Block {
    int type;
    int len;
} blocks[MAXN];

int n, type[MAXN];