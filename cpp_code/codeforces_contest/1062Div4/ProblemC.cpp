#include<bits/stdc++.h>
using namespace std;

int main()
{
    int t = 0;
    cin >> t;
    while (t--) {
        int n = 0;
        vector <int> a;
        cin >> n;
        a.resize(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }

        bool odd = false;
        bool even = false;
        for (int i = 0; i < n; i++) {
            if (a[i] % 2 == 0) {
                even = true;
                break;
            }
        }
        for (int i = 0; i < n; i++) {
            if (a[i] % 2 == 1) {
                odd = true;
                break;
            }
        }

        if (even == true && odd == true) {
            sort(a.begin(),a.end());
            for (int i = 0; i < n; i++) {
                cout << a[i] << " ";
            }
            cout << endl;
        }
        else {
            for (int i = 0; i < n; i++) {
                cout << a[i] << " ";
            }
            cout << endl;
        }
    }
    return 0;
}