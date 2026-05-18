#include<bits/stdc++.h>
using namespace std;

int main()
{
    int t = 0;
    cin >> t;
    while(t--) {
        vector<int> a(4);
        for (int i = 0; i < 4; i++) {
            cin >> a[i];
        }
        bool judge = true;
        for (int i = 0; i < 3; i++) {
            if (a[i] != a[i+1]) {
                judge = false;
                break;
            }
        }

        if (judge) {
            cout << "YES" << endl;
        }
        else {
            cout << "NO" <<endl;
        }
    }
    return 0;
}