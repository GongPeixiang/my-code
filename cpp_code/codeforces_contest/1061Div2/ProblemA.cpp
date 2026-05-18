#include<bits/stdc++.h>
using namespace std;

int main()
{
	int t = 0;
	cin >> t;
	for (int i = 0; i < t; i++){
		int n = 0;
		cin >> n;
		int sum = 0;
		while (n > 2){
			int k = n / 3;
			sum += k;
			n -= 2 * k;
		}
		cout << sum << endl;
	}
	return 0;
}