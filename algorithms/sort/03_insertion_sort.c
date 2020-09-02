
void insertion_sort(int* a, int n){
	for(int i = 0; i < n; ++i){
		int j = i;
		while(j > 0 && a[j - 1] < a[j]){
			swap(a[j-1], a[j]);
			--j;
		}
	}
}

void insertion_sort(int a[], int n){
    int i, j, index;

    for (i = 1; i < n; i++){
        index = a[i];
        j = i;
        while ((j>0)&&(a[j-1] > index)){
            a[j]=a[j-1];
            j=j-1;
        }
        a[j]=index;
    }
}

void insertionsort(vector<int>& A){
    int n = A.size();
    for(int i = 0; i < n; ++i){
        int j = i;
        while(j > 0 && A[j] < A[j - 1]){
            swap(A[j], A[j - 1]);
            --j;
        }
    }
    print(A);
}


// std::rotate
// std::upper_bound

