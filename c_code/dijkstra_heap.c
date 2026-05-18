#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define MAXN 55
#define MAXSIZE 100000

#define SWAP(T, a, b) do {\
	T tmp = a;\
	a = b;\
	b = tmp;\
} while (0)

int n, src, dst;
int dist[MAXN][MAXN];
bool close_set[MAXN] = {false};
int path[MAXN], path_cnt = 0;

void reverse_path() 
{
	for (int i = 0; i < path_cnt / 2; ++i) {
		SWAP(int, path[i], path[path_cnt - 1 - i]);
	}
}

// node
typedef struct node {
	int v;
	int g;
	int prev_id;
} Node;

Node *node_pool[MAXSIZE];
int node_cnt = 0;

int create_node(int v, int g, int prev_id) 
{
	Node *new_node = malloc(sizeof(Node));
	if (!new_node) {
		printf("memory allocation failed\n");
		return INT_MAX;
	}
	new_node->v = v;
	new_node->g = g;
	new_node->prev_id = prev_id;
	node_pool[node_cnt] = new_node;
	return node_cnt++;
}

void clear_nodes()
{
	for (int i = 0; i < node_cnt; ++i) {
		if (node_pool[i]) {
			Node *tmp = node_pool[i];
			free(tmp);
		}
	}
}

// minheap & priority queue
typedef struct minheap {
	int heap_arr[MAXSIZE];
	int idx;
} Minheap;

Minheap open_set;

void init_heap(Minheap *pq) { pq->idx = 0; }

void heap_push(Minheap *pq, int node_id) 
{
	int cur = pq->idx;
	pq->heap_arr[pq->idx++] = node_id;
	while (cur > 0 && node_pool[pq->heap_arr[cur]]->g 
		< node_pool[pq->heap_arr[(cur - 1) / 2]]->g) {
		SWAP(int, pq->heap_arr[cur], pq->heap_arr[(cur - 1) / 2]);
		cur = (cur - 1) / 2;
	}
}

int heap_pop(Minheap *pq) 
{
	int ret = pq->heap_arr[0];
	pq->heap_arr[0] = pq->heap_arr[--pq->idx];
	int cur = 0;
	while (1) {
		int left = cur * 2 + 1, right = cur * 2 + 2;
		int smallest = cur;
		if (left < pq->idx && node_pool[pq->heap_arr[left]]->g 
			< node_pool[pq->heap_arr[smallest]]->g) 
			smallest = left;
		if (right < pq->idx && node_pool[pq->heap_arr[right]]->g 
			< node_pool[pq->heap_arr[smallest]]->g) 
			smallest = right;
		if (smallest == cur) 
			break;
		SWAP(int, pq->heap_arr[cur], pq->heap_arr[smallest]);
		cur = smallest;
	}
	return ret;
}

bool heap_empty(Minheap *pq) { return pq->idx == 0; }

int main() 
{
	scanf("%d %d %d", &n, &src, &dst);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			scanf(" %d", &dist[i][j]);
		}
	}

	init_heap(&open_set);
	int init_id = create_node(src, 0, -1);
	heap_push(&open_set, init_id);

	while (!heap_empty(&open_set)) {
		int cur_id = heap_pop(&open_set);
		Node *cur_node = node_pool[cur_id];

		int cur_v = cur_node->v;
		int cur_g = cur_node->g;

		if (close_set[cur_v]) 
			continue;

		if (cur_v == dst) {
			int track_id = cur_id;
			while (track_id != -1) {
				Node *node = node_pool[track_id];
				path[path_cnt++] = node->v;
				track_id = node->prev_id;
			}
			reverse_path();
			break;
		}

		for (int i = 0; i < n; ++i) {
			if (dist[cur_v][i] == -1) 
				continue;
			int new_g = cur_g + dist[cur_v][i];
			if (!close_set[i]) {
				int new_id = create_node(i, new_g, cur_id);
				heap_push(&open_set, new_id);
			}
		}

		close_set[cur_v] = true;
	}

	if (!path_cnt) 
		printf("Impossible.\n");
	else {
		bool is_first = true;
		for (int i = 0; i < path_cnt; ++i) {
			if (is_first) 
				is_first = false;
			else 
				printf("->");
			printf("%d", path[i]);
		}
		printf("\n");
	}

	clear_nodes();

	return 0;
}