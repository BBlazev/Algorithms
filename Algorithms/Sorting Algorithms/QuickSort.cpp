/*
Quick Sort is a highly efficient, divide-and-conquer sorting algorithm.
It works by selecting a pivot element and partitioning the array around it.

Steps:
1. Pick a pivot (commonly middle, first, last, or random element) -> in this code its middle one
2. Partition: Move elements smaller than pivot to the left, larger to the right.
3. Recursively apply QuickSort to left and right subarrays.

Time Complexity:
- Best case 	=> O(n log n)
- Worst case 	=> O(n²)
- Average case	=> O(n log n)

Quick Sort is **in-place** (no extra memory required, except recursion stack).
It is widely used due to its efficiency on large datasets.
Can be optimized with **randomized pivot selection** to avoid worst-case behavior.
*/



#include <iostream>
#include <cstdlib>  
#include <ctime>  
#define MAX 1001

int n;
int arr[MAX];


void QuickSort(int start, int end) {

	if (start < end)
	{
		int i = start;
		int j = end;

		int pivot = arr[(i + j) / 2];


		while (i <= j)
		{
			while (arr[i] < pivot) i++;
			while (arr[j] > pivot) j--;

			if (i<=j)
			{
				std::swap(arr[i], arr[j]);
				i++;
				j--;
			}

		}
		QuickSort(i, end);
		QuickSort(start,j);
	}
}

void QS(int* arr, int start = 0, int end = n - 1) {

	if (start >= end) return; 

	int i = start,
	int	j = end;
	int pivot = arr[(i + j) / 2];

	while (i <= j) {
		while (arr[i] < pivot) i++;
		while (arr[j] > pivot) j--;

		if (i <= j) {
			std::swap(arr[i], arr[j]);
			i++;
			j--;
		}
	}
	QS(arr, start, j);
	QS(arr, i, end);
}

int main() {

	n = 10;
	std::srand(std::time(0));

	for (int i = 0; i < n; i++) arr[i] = std::rand() % 100; 
	//QuickSort(n, n - 1);
	QS(arr);

	for (int i = 0; i < n; i++) std::cout << arr[i] << " ";

	return 0;
}