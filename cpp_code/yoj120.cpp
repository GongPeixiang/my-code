#include <bits/stdc++.h>
using namespace std;

int n, steps = 0;

void recursion(vector<int> &arr, int start) {
    if (is_sorted(arr.begin(), arr.end())) 
        return;
    auto min_it = min_element(arr.begin() + start, arr.end());
    int min_pos = distance(arr.begin(), min_it);
    if (min_pos == start) {
        recursion(arr, start + 1);
        return;
    }
    steps++;
    swap(arr[start], arr[min_pos]);
    vector<int> tmp = arr;
    recursion(arr, start + 1);
    cout << start + 1 << "<->" << min_pos + 1 << ':';
    for (auto num : tmp) 
        cout << num << ' ';
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) 
        cin >> arr[i];
    recursion(arr, 0);
    cout << "Total steps:" << steps << '\n';
    cout << "Right order:";
    for (auto num : arr) 
        cout << num << ' ';
    cout << '\n';
    return 0;
}