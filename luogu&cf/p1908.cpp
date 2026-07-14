#include <bits/stdc++.h>
using namespace std;
// 归并排序求逆序数, 经典

using ll = long long;
int n;
ll cnt = 0;
vector<int> arr;

void merge(int l, int mid, int r) {
    vector<int> tmp(r - l + 1);
    int i = l, j = mid + 1, k = 0;
    while (i <= mid && j <= r) {
        if (arr[i] <= arr[j]) 
            tmp[k++] = arr[i++];
        else {
            tmp[k++] = arr[j++];
            cnt += mid - i + 1;
        }
    }
    while (i <= mid) 
        tmp[k++] = arr[i++];
    while (j <= r) 
        tmp[k++] = arr[j++];
    k = 0;
    for (int i = l; i <= r; ++i) 
        arr[i] = tmp[k++];
}

void merge_sort(int l, int r) {
    if (l >= r) 
        return;
    int mid = (l + r) / 2;
    merge_sort(l, mid);
    merge_sort(mid + 1, r);
    merge(l, mid, r);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    arr.resize(n);
    for (int i = 0; i < n; ++i) 
        cin >> arr[i];
    merge_sort(0, n - 1);
    cout << cnt << '\n';
}