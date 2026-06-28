#include <bits/stdc++.h>
using namespace std;

void recursion(int cur, int &steps, char src, char med, char dst) { 
    //s for start, d for destination
    if (cur == 1) {
        steps++;
        cout << "[step " << steps << "] " << "move plate " << 1 
        << "# from " << src << " to " << dst << '\n';
        return;
    }
    recursion(cur - 1, steps, src , dst, med);
    steps++;
    cout << "[step " << steps << "] " << "move plate " << cur <<
     "# from " << src << " to " << dst << '\n'; 
    recursion(cur - 1, steps, med, src, dst);
}

int main() {
    int n, steps = 0;
    cin >> n;
    recursion(n, steps, 'a', 'b', 'c');
    cout << steps << '\n';
    return 0;
}