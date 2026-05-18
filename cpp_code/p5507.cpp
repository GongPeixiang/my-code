#include <bits/stdc++.h>
using namespace std;

const int INF = numeric_limits<int>::max();
array<array<int, 4>, 12> chain;
array<int, 12> target = {{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }}, board;
vector<int> path;

int heuristic() {
	int h = 0;
	for (int i = 0; i < 12; i++) {
		if (board[i] != 0) 
			h += (4 - board[i]) % 4;
	}
	return h / 2;
}

bool ida_star(int depth, int max_depth, int &min_exceed) {
	int h = heuristic();
	if (h == 0)
		return true;
	if (depth + h > max_depth) {
		min_exceed = min(min_exceed, h + depth);
		return false;
	}
	for (int i = 0; i < 12; i++) {
		int j = chain[i][board[i]];
		board[i] = (board[i] + 1) % 4;
		board[j] = (board[j] + 1) % 4;
		path.push_back(i);
		if (ida_star(depth + 1, max_depth, min_exceed))
			return true;
		path.pop_back();
		board[i] = (board[i] + 3) % 4;
		board[j] = (board[j] + 3) % 4;
	}
	return false;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	for (int i = 0; i < 12; i++) {
		cin >> board[i];
		board[i]--;
		for (int j = 0; j < 4; j++) {
			cin >> chain[i][j];
			chain[i][j]--;
		}
	}
	if (board == target) {
		cout << '0' << '\n';
		return 0;
	}

	int max_depth = heuristic();
	while (1) {
		int min_exceed = INF;
		if (ida_star(0, max_depth, min_exceed)) {
			cout << max_depth << '\n';
			for (int i = 0; i < max_depth; i++)
				cout << path[i] + 1 << ' ';
			cout << '\n';
			break;
		}
		max_depth = min_exceed;
	}

	return 0;
}