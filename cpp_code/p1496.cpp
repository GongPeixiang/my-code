#include <bits/stdc++.h>
using namespace std;

struct Segment {
    int _left, _right;
};
vector<Segment> segs;
int n, ans = 0;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    segs.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> segs[i]._left >> segs[i]._right;
    }

    sort(segs.begin(), segs.end(), [](const Segment &a, const Segment &b) {
        return a._left < b._left;
    });

    ans += segs[0]._right - segs[0]._left;
    int right_boundary = segs[0]._right; // 注意，一定是右边界，而不是segs[i - 1]._right
    for (int i = 1; i < n; i++) {
        if (segs[i]._left >= right_boundary) {
            ans += segs[i]._right - segs[i]._left;
            right_boundary = segs[i]._right;
        }
        else {
            if (segs[i]._right <= right_boundary) 
                continue;
            else {
                ans += segs[i]._right - right_boundary;
                right_boundary = segs[i]._right;
            }
        }
    }

    cout << ans << '\n';

    return 0;
}