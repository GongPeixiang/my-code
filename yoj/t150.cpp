#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1005;

int n;
struct Stu {
    int id, score;
    int rk;
    bool operator<(const Stu& other) const {
        if (score != other.score) return score > other.score;
        return id < other.id;
    }
} stu[N];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for (int i = 0; i < n; i++) cin >> stu[i].id >> stu[i].score;
    sort(stu, stu + n);
    int rk = 0, pre = INT_MAX;
    for (int i = 0; i < n; i++) {
        if (stu[i].score < pre) rk = i + 1;
        stu[i].rk = rk;
        pre = stu[i].score;
    }
    for (int i = 0; i < n; i++) 
        cout << stu[i].rk << ' ' << stu[i].id << ' ' << stu[i].score << '\n';
    return 0;
}