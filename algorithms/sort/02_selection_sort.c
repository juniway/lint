void selectionSort(int a[], int n) {
    int i, j;
    int min, temp;

    for (i = 0; i < n-1; i++){
        min = i;
        for (j = i+1; j < n; j++){
            if (a[j] < a[min])
            min = j;
        }
        temp = a[i];
        a[i] = a[min];
        a[min] = temp;
    }
}

void selectsort(vector<int>& A){
    int n = A.size();
    for(int i = 0; i < n; ++i){
        for(int j = i; j < n; ++j){
            if(A[j] < A[i])
                swap(A[j], A[i]);
        }
    }
    print(A);
}