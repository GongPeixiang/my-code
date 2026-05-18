#include<bits/stdc++.h>
using namespace std;

void merge(int low, int mid, int high, vector<int> &arr) {
    vector<int> temp(high - low + 1);

    int i = low, j = mid+1, m = 0;

    while (i <= mid && j <= high) {
        if (arr[i] < arr[j]) temp[m++] = arr[i++];
        else temp[m++] = arr[j++];
    }
    while (i <= mid) temp[m++] = arr[i++];
    while (j <= high) temp[m++] = arr[j++];

    for (int i = low,m = 0; i <= high; i++,m++)  arr[i] = temp[m];
}

void mergesort(int low, int high, vector<int> &arr) {
    if (low < high) {
        int mid = (low + high) / 2;
        mergesort(low, mid, arr);
        mergesort(mid+1, high, arr);
        merge(low, mid, high, arr);
    }
}

int main() {
    int n = 0;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) cin >> arr[i];

    mergesort(0, n-1, arr);
    
    for (auto num : arr) cout << num << ' ';
    cout << '\n';

    return 0;
}