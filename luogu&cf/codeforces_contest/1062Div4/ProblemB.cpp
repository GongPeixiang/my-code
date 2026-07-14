#include<bits/stdc++.h>
using namespace std;

int main()
{
    int q = 0;
    cin >> q;
    while(q--) {
        int n = 0;
        string str1,str2;
        cin >> n;
        str1.resize(n);
        str2.resize(n);
        cin.ignore();
        cin >> str1 >> str2;

        int cnt = 0;

        for (int i = 0; i < str2.size(); i++) {
            int len = str1.size();
            for (int j = 0; j < len; j++) {
                if (str1[j] == str2[i]) {
                    cnt++;
                    str1.erase(j,1);
                    break;
                }
            }
        }

        if (cnt == n) {
            cout << "YES" << endl;
        }
        else {
            cout << "NO" << endl;
        }
    }
    return 0;
}