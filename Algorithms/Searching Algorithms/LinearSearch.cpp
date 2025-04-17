//linear search - iterating through a collection, one elem at the time
//runtime complexity -> O(n)
//slow for large datasets
//good for small and medium data sets



#include <iostream>
#include <vector>

template <typename T>
int linearsearch(const T* vec, const T& key, int size) {
    for (int i = 0; i < size; i++)
    {
        if (vec[i] == key) return i;
    }
    return -1;
}



int main() {

    std::vector<int> data = { 5, 3, 8, 4, 2, 9, 1 };
    std::size_t size = data.size();
    int target;

    std::cout << "Enter value to search for: ";
    std::cin >> target;

    int index = linearsearch(data.data(), target, size);
    if (index != -1) {
        std::cout << "Value " << target << " found at index " << index << ".\n";
    }
    else {
        std::cout << "Value " << target << " not found in the array.\n";
    }


	return 0;
}