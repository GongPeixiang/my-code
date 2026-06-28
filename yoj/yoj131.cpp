#include <bits/stdc++.h>
using namespace std;

int singlecnt[10] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};

int stickcnt(int num) {
    if (num == 0) 
        return 6;   //num == 0需要特判！
    int sum = 0;
    while (num > 0) {
        int tmp = num % 10;
        sum += singlecnt[tmp];
        num /= 10;
    }
    return sum;
}

int main() {
    int n, ans = 0;
    cin >> n;
    n -= 4;
    for (int i = 0; i <= 1000; i++) {
        for (int j = 0; j <= 1000; j++) {
            int c = i + j;
            if (stickcnt(i) + stickcnt(j) + stickcnt(c) == n) {
                ans++;
            }
        }
    }
    cout << ans << '\n';
    return 0;
}