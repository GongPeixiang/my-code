#include <stdio.h>
#define MAXSIZE 500

int n, arr[MAXSIZE];

void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int left = low, right = high - 1;

    while (left <= right) {
        while (left <= right && arr[left] <= pivot)
            left++;
        while (left <= right && arr[right] >= pivot)
            right--;
        if (left < right) {
            swap(&arr[left], &arr[right]);
            left++;
            right--;
        }
    }

    swap(&arr[left], &arr[high]);
    return left;
}

/*
*另一种分区函数
int partition(int *arr, int left, int right)
{
	int pivot = arr[right];
	int j = left - 1
	for (int i = left; i < right; i++) {
		if (arr[i] <= pivot) {
			j++;
			swap(&arr[j], &arr[i]);
		}
	}
	swap(&arr[j+1], &arr[right]);
	return j+1;
}
*/

void quicksort(int arr[], int left, int right)
{
	if (left >= right) return;
	int guard = partition(arr, left, right);
	quicksort(arr, left, guard-1);
	quicksort(arr, guard+1, right);
}

int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
        scanf("%d", arr + i);
	quicksort(arr, 0, n - 1);
    for (int i = 0; i < n; i++)
        printf("%d ",*(arr + i));
    printf("\n");
    return 0;
}
