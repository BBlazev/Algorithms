//searching algo that finds position of target value within sorted arr
//complexity O(log n)


#include <iostream>
#include <vector>
#include <algorithm>

template <typename T>
int binarysearch(const T* arr, const T& value, std::size_t size) {

	std::size_t left = 0;
	std::size_t right = (size == 0 ? 0 : size - 1);

	while (left <= right)
	{
		std::size_t mid = left + (right - left) / 2;


		if (arr[mid] == value)
			return static_cast<int>(mid);

		else if (arr[mid] < value)
			left = mid + 1;
		else {

			if (mid == 0) break;
			right = mid - 1;
		}
	}

	return -1;
}



int main() {

	std::vector<int> data = { 5, 3, 8, 4, 2, 9, 1 };
	std::sort(data.begin(), data.end());           // → {1,2,3,4,5,8,9}
	std::size_t size = data.size();
	int target_val;

	std::cout << "Enter value to search for: ";
	std::cin >> target_val;

	int index = binarysearch(data.data(), target_val, size);

	if (index != -1)
		std::cout << "Value " << target_val << " found at index " << index << std::endl;
	else
		std::cout << "Value " << target_val << " not found." << std::endl;

	return 0;
}