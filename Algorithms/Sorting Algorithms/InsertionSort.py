'''Worst/average O(n2) when the array is in descending order, or generally when many shifts are needed
O(n) if the array is already sorted, because very few shifts are needed
'''

def insertionSort(arr):
    n = len(arr)
    
    # Start from the second element (index = 1),
    # because the first element (index = 0) is trivially sorted by itself.
    for i in range(1, n):
        # The current value to be inserted into the "already sorted" portion.
        val = arr[i]
        
        # Start comparing from the previous element.
        j = i - 1
        
        # Move elements of arr[0..i-1], that are greater than val,
        # one position ahead to make space for val.
        while j >= 0 and arr[j] > val:
            arr[j + 1] = arr[j]
            j -= 1
        
        # Insert the value at the correct position once we've found it.
        arr[j + 1] = val
    
    return arr

arr = [2, 3, 4, 1, 65, 2, 9, 6, 5, 3]
sorted_arr = insertionSort(arr)
print("Sorted:", sorted_arr)
