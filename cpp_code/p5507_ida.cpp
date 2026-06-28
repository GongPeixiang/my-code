#include <bits/stdc++.h>
using namespace std;

int chain[12][4], stat[12], tgt[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
vector<int> path;

int heuristic() {
	int cnt = 0;
	for (int i = 0; i < 12; i++) {
		if (stat[i] != 0) 
			cnt += (4 - stat[i]) % 4;
	}
	return cnt / 2;
}

bool ida_star(int dep, const int max_dep, int &min_excd) {
	int h = heuristic();
	if (h == 0)
		return true;
	if (dep + h > max_dep) {
		min_excd = min(min_excd, h + dep);
		return false;
	}
	for (int i = 0; i < 12; i++) {
		int j = chain[i][stat[i]];
		stat[i] = (stat[i] + 1) % 4;
		stat[j] = (stat[j] + 1) % 4;
		path.push_back(i);
		if (ida_star(dep + 1, max_dep, min_excd))
			return true;
		path.pop_back();
		stat[i] = (stat[i] + 3) % 4;
		stat[j] = (stat[j] + 3) % 4;
	}
	return false;
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	for (int i = 0; i < 12; i++) {
		cin >> stat[i];
		--stat[i];
		for (int j = 0; j < 4; j++) {
			cin >> chain[i][j];
			--chain[i][j];
		}
	}

	if (memcmp(stat, tgt, sizeof(tgt)) == 0) {
		cout << 0 << '\n';
		return 0;
	}

	int max_dep = heuristic();
	while (1) {
		int min_exc = 0x3f3f3f3f;
		if (ida_star(0, max_dep, min_exc)) {
			cout << max_dep << '\n';
			for (int i = 0; i < max_dep; i++)
				cout << path[i] + 1 << ' ';
			cout << '\n';
			break;
		}
		max_dep = min_exc;
	}

	return 0;
}