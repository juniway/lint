int partition(int A[ ], int left, int right);
// sort A[left..right]
void quicksort(int A[ ], int left, int right){
	int q ;
	if (right > left ){
		q = partition(A, left, right);
		// after ??partition??
		//? A[left..q-1] ??A[q] ??A[q+1..right]
		quicksort(A, left, q-1);
		quicksort(A, q+1, right);
	}
}

// select A[left] be the pivot element)
int partition(int A[], int left, int right){
	P = A[left];
	i = left;
	j = right + 1;
	for(;;){ //infinite for-loop, break to exit
		while (A[++i] < P)
			if (i >= right) break;

		// Now, A[i] ??P
		while (A[--j] > P)
			if (j <= left) break;

		// Now, A[j] ??P
		if (i >= j )
			break; // break the for-loop
		else
			swap(A[i], A[j]);
	}
	if (j == left) return j ;
	swap(A[left], A[j]);
	return j;
}
