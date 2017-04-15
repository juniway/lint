/*
You have sorted rotatable array, i. e. the array contains elements which are sorted and it can be rotated circularly,
like if the elements in array are [5,6,10,19,20,29]
then rotating first time array becomes [29,5,6,10,19,20]
and on second time it becomes [20,29,5,6,10,19] and so on.
*/

/*
Analysis:
**Method 1**
Time: O(logN)

Use a `modified binary search` to find the point of rotation which is an index i such that `arr[i] > arr[i+1]`.

**Example:**

    [6, 7, 8, 9, 1, 2, 3, 4, 5]
              ^
              i
The two sub-arrays `(arr[0], arr[2], .., arr[i])` and `(arr[i+1], arr[i+2], ..., arr[n - 1])` are sorted.

The answer is: min(arr[0], arr[i+1])

Reduced to the problem of finding the largest number position, which can be done by checking the first and last and middle
number of the area, recursively reduce the area, divide and conquer. O(log n) complexity.

EDIT: For example, you have

    6 7 8 1 2 3 4 5
    ^       ^     ^

By looking at the 3 numbers you know the location of the smallest/largest
numbers (will be called mark later on) is in the area of 6 7 8 1 2,
so 3 4 5 is out of consideration (usually done by moving your area
start/end index(int) pointing to the number 6 and 2 ).

Next step,

    6 7 8 1 2
    ^   ^   ^

Once again you will get enough information to tell which side (left or right) the mark is, then the area is reduced to half again (to 6 7 8).

**Method 2**

When we split the array into two halves (arr[1],..,arr[mid]) and (arr[mid+1],..,arr[n]), one of them is always sorted and the other always
has the min. We can directly use a `modified binary search` to keep searching in the unsorted half.

low, high = 0, n - 1

while (nums[low] > nums[high]) { // always restrict the search to the unsorted sub-array. The min is always there.
    mid = low + (low + high)/2
    if (nums[mid] > nums[high]) {
        low = mid + 1
    } else {
        high = mid
    }
}
return nums[low]

#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>

int binarySearch(int numbers[], int k, int startIndex, int endIndex){
    if(!numbers) return -1;
    int middleIndex = startIndex + (endIndex - startIndex)/2;

    while(numbers[middleIndex] != k && startIndex <= endIndex){
        if(k < numbers[middleIndex])
    		endIndex = middleIndex -1;
    	else
    		startIndex = middleIndex + 1;
        middleIndex = startIndex + (endIndex - startIndex)/2;
    }

    if(startIndex <= endIndex)
        return middleIndex;
    else
        return -1;
}

/* Recursive Method
int binarySearch(int numbers[], int k, int startIndex, int endIndex){
    if(!numbers) return -1;
    int middleIndex = startIndex + (endIndex - startIndex)/2;
	if(middleIndex > endIndex || middleIndex < startIndex)
        return -1;

    if(k == numbers[middleIndex])
		return middleIndex;

	else if(k < numbers[middleIndex])
		return binarySearch(numbers, k, startIndex, middleIndex-1);
	else
		return binarySearch(numbers, k, middleIndex+1, endIndex);

}

*/

int searchInRotationArray(int numbers[], int k, int startIndex, int endIndex){
    if(startIndex > endIndex)
		return -1;
	int middleIndex = startIndex + (endIndex - startIndex) / 2;
	if(numbers [middleIndex] == k)
		return middleIndex;

	// if the middle number is in the first increasing sub-array
	if(numbers[middleIndex] >= numbers[startIndex]){
		if (k >= numbers[startIndex] && k < numbers[endIndex])
				return binarySearch(numbers, k, startIndex, middleIndex-1);
		return searchInRotationArray(numbers, k, middleIndex+1, endIndex);
	}
	// if the middle number is in the second increasing sub-array
	else if(numbers[middleIndex] <= numbers[endIndex]){
		if(k > numbers[middleIndex] && k <= numbers[endIndex])
			return binarySearch(numbers, k, middleIndex, endIndex);
		return searchInRotationArray(numbers, k, startIndex, middleIndex - 1);
	}

	// it should never reach here if the input is valid
	assert(false);
}

int searchInRotationArray(int numbers[], int length, int k){
	if(numbers == nullptr || length <0)
		return -1;
    return searchInRotationArray(numbers, k, 0, length -1);
}


int main(){
	int numArr[6] = {20, 29, 5, 6, 10, 19};


	int index = searchInRotationArray(numArr, 29, 0, 5);
	if(index != -1)
		std::cout<<"The index of the searched item is: "<<index<<std::endl;
}

