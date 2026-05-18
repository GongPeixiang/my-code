#include<bits/stdc++.h>
using namespace std;

int main()
{
	int t = 0;
	cin >> t;
	for (int i = 0; i < t; i++){
		int n = 0, q = 0;
		string type;
		vector <int> arr;
		cin >> n >> q;
		type.resize(n);
		arr.resize(q);
		cin.ignore();
		getline(cin,type);
		bool allA = true;
		for (int j = 0; j < n; j++){
			if (type[j] == 'B'){
				allA = false;
				break;
			}
		}
		for (int j = 0; j < arr.size(); j++){
			cin >> arr[j];
		}

		for (int j = 0; j < arr.size(); j++){
			int num = arr[j];
			long long cnt = 0;

			if (allA == true){
				cout << arr[j] << endl;
				continue;
			}

			while (num > 0){
				int k = cnt % n;
				if (type[k] == 'A'){
					num--;
				}
				else if (type[k] == 'B'){
					num /= 2;
				}
				cnt++;
			}
			cout << cnt << endl;
		}
	}
}