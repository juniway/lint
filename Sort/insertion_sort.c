
void insertion_sort(int* a, int n){
	for(int i = 0; i < n; ++i){
		int j = i;
		while(j > 0 && a[j - 1] < a[j]){
			swap(a[j-1], a[j]);
			--j;
		}
	}
}