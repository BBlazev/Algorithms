def mergeSort(arr):
    if len(arr) <= 1:
        return arr
    
    mid = len(arr) //2

    left = arr[:mid]
    right = arr[mid:]

    sortedLeft = mergeSort(left)
    sortedRight = mergeSort(right)

    return merge(sortedLeft,sortedRight)

#goal of merge(l,r) is to take two already sorted lists and combine them into a single sorted list
def merge(left,right):
    result = []
    x = y = 0 #init pointers, x tracks pos of left list and y tracks pos of right list

    #comparing and appending to result
    while x < len(left) and y < len(right):
        if left[x] < right[y]:
            result.append(left[x])
            x+=1
        else:
            result.append(right[y])
            y+=1
    

    #when x or y is fully processed, x or y >= len(l or r), we append remaining elements
    result.extend(left[x:])
    result.extend(right[y:])

    return result


arr = [2,34,5,3,2,7,6,5,10,36,89,1,9]
sorted = mergeSort(arr)

print("Sorted: ", sorted)
