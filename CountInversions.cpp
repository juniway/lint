Count Inversions
Given an integer array, count the number of inversions.

Inversion Count for an array indicates – how far (or close) the array is from being sorted. 
If array is already sorted then inversion count is 0. 
If array is sorted in reverse order that inversion count is the maximum.
Formally speaking, two elements a[i] and a[j] form an inversion if a[i] > a[j] and i < j

For example, given [22, 48, 12, 35, 57], return 3 since there are three inversions, (22, 12), (48, 12), (48, 35).

这个题很巧妙地运用了merge sort的理念，还有在merge的时候计算count也非常巧妙。
public class CountInversions {



/*int countInversions(int[] A) {
int count = 0;
for (int i = 0; i < A.length-1; i++) {
for (int j = i; j < A.length; j++) {
if (A[i] > A[j])
count++;
}
}
return count;
}
*/

int countInversions(int[] A, int start, int end) {
	int count = 0;
	if (start == end) return count;
	int mid = start + (end – start) / 2;
	count += countInversions(A, start, mid);
	count += countInversions(A, mid+1, end);
	count += merge(A, start, mid, end);
	return count;
}

int merge(int[] A, int start, int mid, int end) {
	int count = 0;
	int r1 = start;
	int r2 = mid + 1;
	int[] B = Arrays.copyOf(A, A.length);
	for (int i = start; i <= end; i++) {
		if (r1 > mid || (r2 <= end && B[r1] > B[r2])) {
			count += r2 – i;
			A[i] = B[r2++];
		} else
			A[i] = B[r1++];
		}
		return count;
	}
}

void main(String[] args) {
	vector<int> A = {22, 48, 12, 35, 57};
	cout << countInversions(A, 0, A.length-1) << endl;
}