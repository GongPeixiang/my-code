#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct _dsu {
    int cc_cnt; // cc for connection component
    int *parent, *size;
} DSU;

#define swap(T, a, b) do { \
    T tmp = a; \
    a = b, b = tmp; \
} while (0)

void init_dsu(DSU *uf, int n) 
{
    uf->cc_cnt = n;
    uf->parent = (int *)malloc(n * sizeof(int));
    uf->size = (int *)malloc(n * sizeof(int));
    if (!uf->parent || !uf->size) exit(1);
    for (int i = 0; i < n; ++i) {
        uf->parent[i] = i;
        uf->size[i] = 1;
    }
}

int find(DSU *uf, int x) // 递归压缩路径更彻底
{
    if (x != uf->parent[x]) 
        uf->parent[x] = find(uf, uf->parent[x]);
    return x;
}

bool unite(DSU *uf, int a, int b) 
{
    int ra = find(uf, a), rb = find(uf, b);
    if (ra == rb) 
        return false;
    if (uf->size[ra] < uf->size[rb]) 
        swap(int, ra, rb);
    uf->size[ra] += uf->size[rb];
    uf->parent[rb] = ra;
    --uf->cc_cnt;
    return true;
}

bool connected(DSU *uf, int a, int b) 
{
    return find(uf, a) == find(uf, b);
}

DSU uf;

int main() 
{
    int n = 5;
    init_dsu(&uf, n);
    printf("Initial components: %d\n", uf.cc_cnt);

    unite(&uf, 0, 1);
    unite(&uf, 2, 3);
    unite(&uf, 1, 2);

    printf("connected(0,3): %d\n", connected(&uf, 0, 3));
    printf("connected(0,4): %d\n", connected(&uf, 0, 4));
    printf("After unions, components: %d\n", uf.cc_cnt);

    free(uf.parent);
    free(uf.size);

    return 0;
}