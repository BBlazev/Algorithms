//improvement over binary search, best used for uniformly distrubuted data
//avg case:		O(log(log(n)))
//worst case:	O(n) 
// 
// 
//we are guessing where value might be based on a probe, if we are incorrect, search area is narrowed
//and a new probe is calculated

#include <iostream>
#include <vector>
#include <algorithm>

template <typename T>
int interpolationsearch(const T* arr, const T& value, std::size_t size) {

	std::size_t low = 0;
	std::size_t high = (size == 0 ? 0 : size - 1);


	while (low <= high && value >= arr[low] && value <= arr[high]) {
		if (low == high)
			return (arr[low] == value) ? static_cast<int>(low) : -1;

		//estimate position by formula
		std::size_t pos = 
			low +((high - low) * (value - arr[low])) / (arr[high] - arr[low]);

		if (arr[pos] == value)
			return static_cast<int>(pos);
		else if (arr[pos] < value)
			low = pos + 1;
		else {
			if (pos == 0) break; // avoid underflow
			high = pos + 1;
		}

	}
	return -1;
}


int main() {
	std::vector<int> data = { 5, 3, 8, 4, 2, 9, 1 };
	std::sort(data.begin(), data.end());  // e.g. {1,2,3,4,5,8,9}

	std::size_t size = data.size();
	int target;

	std::cout << "Enter value to search for: ";
	std::cin >> target;

	int idx = interpolationsearch(data.data(), target,size);
	if (idx != -1)
		std::cout << "Found " << target << " at index " << idx << ".\n";
	else
		std::cout << target << " not found.\n";

	return 0;
}