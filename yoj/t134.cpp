#include <bits/stdc++.h>
using namespace std;

int n;
struct Guess {
	array<int, 4> digit;
	int b, c;
};

bool judge(array<int, 4> cmp, const vector<Guess> &guess) {
	for (int i = 0; i < n; i++) {
		int d = 0, e = 0;
		array<int, 4> tmp = guess[i].digit;
		for (int j = 0; j < 4; j++) {
			if (cmp[j] == tmp[j]) 
				e++;
		}
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++) {
				if (tmp[k] == cmp[j]) {
					d++;
					tmp[k] = 11;
					break;   // 这个break很重要
				}
			}
		}
		if (d != guess[i].b || e != guess[i].c) 
			return false;
	}
	return true;
}

int main() {
	cin >> n;
	vector<Guess> guess(n);
	vector<int> ans;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 4; j++) 
			scanf("%1d", &guess[i].digit[j]);
		cin >> guess[i].b >> guess[i].c;
	}
	for (int num = 1000; num < 10000; num++) {
		int tmp = num;
		array<int, 4> cmp;
		for (int i = 0; i < 4; i++) {
			cmp[3 - i] = tmp % 10;
			tmp /= 10;
		}
		if (judge(cmp, guess)) 
			ans.push_back(num);
	}
	if (ans.size() == 1) 
		cout << ans[0] << '\n';
	else 
		cout << "Not sure\n";
	return 0;
}