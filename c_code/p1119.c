#include <stdio.h>
#include <string.h>

#define MAXN 200
#define MAXM 20000

// 链式前向星
struct Edge {
    int to, w, nxt;
} edge[MAXM * 2];
int head[MAXN], tp = 0;

void init_head() 
{
    tp = 0;
    memset(head, 0xff, sizeof(head));
}

void add_edge(int u, int v, int w) 
{
    edge[tp].to = v;
    edge[tp].w = w;
    edge[tp].nxt = head[u];
    head[u] = tp++;
}

void traverse(int u) 
{
    for (int i = head[u]; i != -1; i = edge[i].nxt) {
        int v = edge[i].to;
        int w = edge[i].w;
    }
}

int N, M, t[MAXN];