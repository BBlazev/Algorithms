#include <iostream>

using namespace std;

int ternarysearch(int left, int right, int value, int arr[]) {

	if (right >= left) {


		int mid_1 = left + (right - left) / 3;
		int mid_2 = right - (right - left) / 3;
	
		if (arr[mid_1] == value) return mid_1;
		if (arr[mid_2] == value) return mid_2;
		
		if (value < arr[mid_1]) return ternarysearch(left, mid_1 - 1, value, arr);
		else if (value > arr[mid_2]) return ternarysearch(mid_2 + 1, right, value, arr);
		else return ternarysearch(mid_2 + 1, mid_1 - 1, value, arr);


	}
	return -1;
}



int main() {

	int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	int left = 0;
	int right = 9;
	int value = 7;

	int target = ternarysearch(left, right, value, arr);

	cout << "Value: " << value << " is at -> " << target;

	return 0;
}

