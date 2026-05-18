#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAXSIZE 300

typedef struct {
    int parent[MAXSIZE];
    int size[MAXSIZE];
    int cnt;
} Unionfind;

#define SWAP(a, b) do {\
    int tmp = a;\
    a = b;\
    b = tmp;\
} while (0)

Unionfind *uf_create(int n) 
{
    Unionfind *uf = malloc(sizeof(Unionfind));
    uf->cnt = n;
    for (int i = 0; i < n; i++) {
	uf->parent[i] = i;
	uf->size[i] = 1;
    }
    return uf;
}

bool uf_destroy(Unionfind *uf) 
{
    if (uf) {
	free(uf);
	return true;
    }
    else 
    	return false;
}

int uf_find(Unionfind *uf, int x) 
{
    while (uf->parent[x] != x) 
        x = uf->parent[uf->parent[x]];
    return x;
}

bool uf_unite(Unionfind *uf, int a, int b) 
{
    int rootA = uf_find(uf, a);
    int rootB = uf_find(uf, b);
    if (rootA == rootB) 
    	return false;
    if (uf->size[rootA] < uf->size[rootB]) 
    	SWAP(rootA, rootB);
    uf->parent[rootB] = rootA;
    uf->size[rootA] += uf->size[rootB];
    uf->cnt--;
    return true;
}

bool uf_connected(Unionfind *uf, int a, int b) 
{
    return uf_find(uf, a) == uf_find(uf, b);
}

int uf_count(Unionfind *uf) { return uf->cnt; }

int main(void)
{
    int n = 10;
    Unionfind *uf = uf_create(n);

    printf("%d\n", uf_count(uf));

    uf_unite(uf, 1, 2);
    uf_unite(uf, 2, 5);
    uf_unite(uf, 5, 6);
    uf_unite(uf, 3, 4);
    uf_unite(uf, 4, 9);

    printf("%d\n", uf_count(uf));

    printf("is 1 and 6 connected? %s\n",
           uf_connected(uf, 1, 6) ? "yes" : "no");
    printf("1 and 3? %s\n",
           uf_connected(uf, 1, 3) ? "yes" : "no");
    printf("3 and 9? %s\n",
           uf_connected(uf, 3, 9) ? "yes" : "no");

    printf("\nshow the parent:\n");
    for (int i = 0; i < n; i++) 
        printf("parent[%d] = %d\n", i, uf->parent[i]);

    uf_destroy(uf);
    return 0;
}
