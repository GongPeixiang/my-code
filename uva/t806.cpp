#include <bits/stdc++.h>
using namespace std;

constexpr int N = 70;

int n;
char img[N][N];
vector<int> seq, path;

bool is2color(int r, int c, int len) {
	for (int i = r; i < r + len; ++i) 
		for (int j = c; j < c + len; ++j) 
			if (img[i][j] != img[r][c]) return true;
	return false;
}

void img2seq(int r, int c, int len) {
	if (!is2color(r, c, len)) {
		if (img[r][c] == '0') return;
		int num = 0;
		for (int i = path.size() - 1; i >= 0; --i) 
			num = num * 5 + path[i];
		seq.push_back(num);
		return; 
	}
	len >>= 1;
	path.push_back(1); img2seq(r, c, len);
	path.back() = 2; img2seq(r, c + len, len);
	path.back() = 3; img2seq(r + len, c, len);
	path.back() = 4; img2seq(r + len, c + len, len);
	path.pop_back();
}

void seq2img(int r, int c, int len, int dep) {
	if (dep == path.size() || len == 1) {
		for (int i = r; i < r + len; ++i) 
			for (int j = c; j < c + len; ++j) 
				img[i][j] = '*';
		return;
	}
	len >>= 1;
    int t = path[dep];
    if(t == 1) seq2img(r, c, len, dep + 1);
    else if(t == 2) seq2img(r, c + len, len, dep + 1);
    else if(t == 3) seq2img(r + len, c, len, dep + 1);
    else if(t == 4) seq2img(r + len, c + len, len, dep + 1);
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	int kase = 0;
	while (cin >> n) {
		if (!n) break;
		if (kase) cout << '\n';
		cout << "Image " << ++kase << '\n';
		seq.clear(); path.clear();
		if (n > 0) {
			for (int i = 0; i < n; ++i) 
				for (int j = 0; j < n; ++j) 
					cin >> img[i][j];
			img2seq(0, 0, n);
			sort(seq.begin(), seq.end());
			for (int i = 0; i < seq.size();) {
                for (int j = 0; j < 12 && i < seq.size(); ++j) {
                    if (j > 0) cout << ' ';
                    cout << seq[i++];
                }
                cout << '\n';
            }		
			cout << "Total number of black nodes = " << seq.size() << '\n';
		} else {
			n *= -1;
    		memset(img, '.', sizeof(img));
    		int t;
    		while (cin >> t && t != -1) {
        		if (t == 0) 
            		memset(img, '*', sizeof(img));
        		else {
            		path.clear();
            		while (t) path.push_back(t % 5), t /= 5;
            		seq2img(0, 0, n, 0);
        		}
    		}
    		for (int i = 0; i < n; ++i) {
        		for (int j = 0; j < n; ++j) cout << img[i][j];
        		cout << '\n';
    		}
		}
	}
	return 0;
}