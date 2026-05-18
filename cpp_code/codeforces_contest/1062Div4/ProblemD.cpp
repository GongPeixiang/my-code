#include<bits/stdc++.h>
using namespace std;

int gcd(int m, int n)
{
    if (m % n == 0) {
        return n;
    }
    else {
        return gcd(n, m % n);
    }
}

int main()
{
    int t = 0;
    cin >> t;
    while(t--) {
        int n;
        vector <long long> arr;
        cin >> n;
        arr.resize(n);
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
        }
        long long x = 2;
        int judge = false;
        while (x <= pow(10,18)) {
            judge = false;
            for (int i = 0; i < n; i++) {
                if (gcd(x,arr[i]) == 1) {
                    judge = true;
                    break;
                }
            }
            if (judge) {
                cout << x << endl;
                break;
            }
            x++;
        }
        if (!judge) {
            cout << -1 << endl;
        }
    }
    return 0;
}