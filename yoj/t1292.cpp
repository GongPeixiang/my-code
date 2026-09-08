#include <bits/stdc++.h>
using namespace std;

bool solve() {
    for (int a = 0; a < 2; a++) {
        for (int b = 0; b < 2; b++) {
            for (int c = 0; c < 2; c++) {
                for (int d = 0; d < 2; d++) {
                    for (int e = 0; e < 2; e++) {
                        int ans1 = ((a || b) || c) && (d < e);
                        int ans2 = (a && d) || (b && e) || (c && d);
                        if (ans1 != ans2) 
                            return false;
                    }
                }
            }
        }
    }
    return true;
}

int main() {
    if (solve()) 
        cout << "等价" << '\n';
    else 
        cout << "不等价" << '\n';
}