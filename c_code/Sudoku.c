#include <stdio.h>
#include <stdbool.h>

int board[9][9];
bool row[9][9], col[9][9], unit[9][9], found = false;

int partition(int r, int c)
{
	return (r / 3) * 3 + (c / 3);
}

void solve_sudo(int idx)
{
	if (found)
		return;
	if (idx == 81) {
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) 
				printf("%d ", board[i][j] + 1);
			printf("\n");
		}
		found = true;
		return;
	}
	int r = idx / 9, c = idx % 9;
	if (board[r][c] != -1) {
		solve_sudo(idx + 1);
		return;
	}
	int section = partition(r, c);
	for (int i = 0; i < 9; i++) {
		if (row[r][i] && col[c][i] && unit[section][i]) {
			board[r][c] = i;
			row[r][i] = col[c][i] = unit[section][i] = false;
			solve_sudo(idx + 1);
			row[r][i] = col[c][i] = unit[section][i] = true;
			board[r][c] = -1;
		}
	}
}

int main()
{
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			row[i][j] = col[i][j] = unit[i][j] = true;
		}
	}
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			scanf("%1d", &board[i][j]);
			int num = --board[i][j];
			if (num == -1)
				continue;
			row[i][num] = false;
			col[j][num] = false;
			unit[partition(i, j)][num] = false;
		}
	}
	solve_sudo(0);
	return 0;
}