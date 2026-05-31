#include<bits/stdc++.h>
using namespace std;

int main() {
    int n = 0, cnt = 1;
    cin >> n;
    vector<vector<int>> arr(n + 1, vector<int>(n + 1));
    for(int i = 1; i <= n; i++) {
        if(i % 2 != 0) {
            for(int j = 1; j < i; j++) 
                arr[i][j] = cnt++;
            for(int j = i; j >= 1; j--) 
                arr[j][i] = cnt++;
        }
        else {
            for(int j = 1; j < i; j++) 
                arr[j][i] = cnt++;
            for(int j = i; j >= 1; j--) 
                arr[i][j] = cnt++;
        }
    }
    for(int i = 1;i <= n; i++) {
        for(int j = 1; j <= n; j++) 
            cout << arr[i][j] << ' ';
        cout << '\n';
    }
    return 0;
}