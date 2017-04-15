
// std::binary_search(vi.begin(),vi.end(),7)

template <class ForwardIterator, class T>
bool binary_search (ForwardIterator first, ForwardIterator last, const T& val)
{
  first = std::lower_bound(first,last,val);
  return (first!=last && !(val<*first));
}

void binarySearch(apvector <int> &array, int lowerbound, int upperbound, int key){
	int position;
	int comparisonCount = 1;    //count the number of comparisons (optional)

	// To start, find the subscript of the middle position.
	position = ( lowerbound + upperbound) / 2;

	while((array[position] != key) && (lowerbound <= upperbound)){
		comparisonCount++;
		if(array[position] > key)
		    upperbound = position - 1;    
		else
		    lowerbound = position + 1;     
		position = (lowerbound + upperbound) / 2;
	}
	if (lowerbound < = upperbound){
		cout<< "The number was found in array subscript "<< position << endl; 
		cout<< "Total number of comparisons are: " << comparisonCount << endl;              
		// printing the number of comparisons is optional
	}      
	else
	cout<< "Not Found!  The binary search made " <<comparisonCount << " comparisons.";
	return;  // you may also consider returning the subscript
} 

// 1. iterative
bool binary_search(int A[], int n){
	first = 0;
	last = n - 1;
	middle = (first+last)/2;
	while (first <= last) {
		if (A[middle] == search)
			return true;
		else if(A[middle] < search)
			first = middle + 1;    
		else
			last = middle - 1;

		middle = (first + last)/2;
	}
	if (first > last)
		return false;
}

// 1. recursive
int binary_search(int a[], int low, int high, int target) {
    if (high < low)
        return -1;

    // Defacts: The computation (low + high)/2 may 
    // return incorrect results for very large arrays due to overflow
    // so it is better to write: middle = low + (high - low)/2;
    int middle = (low + high)/2; 

	if (target == a[middle])
        return middle;
    else if (target < a[middle])
        return binary_search(a, low, middle-1, target);
    else
        return binary_search(a, middle+1, high, target);

}

// 2. iterative
int binary_search(int a[], int low, int high, int target) {
    while (low <= high) {
        int middle = low + (high - low)/2;
        if (target < a[middle])
            high = middle - 1;
        else if (target > a[middle])
            low = middle + 1;
        else
            return middle;
    }
    return -1;
}