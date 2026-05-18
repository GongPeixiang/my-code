#include <stdio.h>
#include <stdbool.h>
#define MAXSIZE 10

int path[MAXSIZE], n, cnt = 0;
bool used[MAXSIZE];

void dfs(int depth)
{
	if (depth == n) {
		cnt++;
		for (int i = 0; i < n; i++) 
			printf("%d ", path[i] + 1);
		printf("\n");
		return;
	}
	for (int i = 0; i < n; i++) {
		if (!used[i]) {
			used[i] = true;
			path[depth] = i;
			dfs(depth + 1);
			path[depth] = -1;
			used[i] = false;
		}
	}
}

int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		path[i] = -1;
		used[i] = false;
	}
	dfs(0);
	printf("total: %d\n", cnt);
	return 0;
}