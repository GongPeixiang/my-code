#include <bits/stdc++.h>
using namespace std;

int X1, Y1, X2, Y2, N;

struct Point {
    int d1, d2;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> X1 >> Y1 >> X2 >> Y2;
    cin >> N;
    vector<Point> point;
    for (int i = 0; i < N; i++) {
        int x, y;
        cin >> x >> y;
        int d1 = (x - X1) * (x - X1) + (y - Y1) * (y - Y1);
        int d2 = (x - X2) * (x - X2) + (y - Y2) * (y - Y2);
        point.push_back({d1, d2});
    }
    sort(point.begin(), point.end(), [](const Point &a, const Point &b) {
        return a.d1 < b.d1;
    });
    int ans = point[N - 1].d1;
    int max_d2 = 0;
    for (int i = N - 1; i >= 0; i--) {
        max_d2 = max(max_d2, point[i].d2);
        int r1 = (i > 0) ? point[i - 1].d1 : 0;
        int total = r1 + max_d2;
        ans = min(ans, total);
    }
    cout << ans << '\n';
    return 0;
}