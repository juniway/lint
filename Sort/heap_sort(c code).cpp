/*
 
function heapSort(a, count) is
     input:  an unordered array a of length count
  
     (first place a in max-heap order)
     heapify(a, count)
  
     end := count-1 
    //In languages with zero-based arrays the children are 2*i+1 and 2*i+2
     while end > 0 do
         (swap the root(maximum value) of the heap with the last element of the heap)
         swap(a[end], a[0])
         (decrease the size of the heap by one so that the previous max value will
         stay in its proper placement) 
         end := end - 1
         (put the heap back in max-heap order)
         siftDown(a, 0, end)
          
  
 function heapify(a, count) is
     (start is assigned the index in a of the last parent node)
     start := (count - 1) / 2 
      
     while start  0 do
         (sift down the node at index start to the proper place such that all nodes
          below the start index are in heap order)
         siftDown(a, start, count-1)
         start := start - 1
     (after sifting down the root all nodes/elements are in heap order)
  
 function siftDown(a, start, end) is
     input:  end represents the limit of how far down the heap
                   to sift.
     root := start
 
     while root * 2 + 1  end do          (While the root has at least one child)
         child := root * 2 + 1        (root*2 + 1 points to the left child)
         swap := root        (keeps track of child to swap with)
         (check if root is smaller than left child)
         if a[swap] < a[child]
             swap := child
         (check if right child exists, and if it's bigger than what we're 
          currently swapping with)
         if child+1  end and a[swap] < a[child+1]
             swap := child + 1
         (check if we need to swap at all)
         if swap != root
             swap(a[root], a[swap])
             root := swap          (repeat to continue sifting down the child now)
         else
             return

*/

#include<stdio.h>
#include<conio.h>

void heapsort(int[], int);
void heapify(int[], int);
void adjust(int[], int);

int main(){
	int array[50],n,i;
	clrscr();

	printf("Enter the no. of elements to be sorted: ");
	scanf("%d",&n);

	printf("\nEnter the elements: \n");
	for(i=0 ; i<n ; i++)
		scanf("%d",&array[i]);

	printf("\nBefore Heapsort:"); //Array Before Mergesort
	for(i = 0; i < n; i++){
		printf("%4d", array[i]);
	}
	printf("\n");

	heapsort(array,n);

	printf("\nAfter Heapsort:"); //Array After Mergesort
	for(i = 0; i < n; i++){
		printf("%4d", array[i]);
	}
	printf("\n");
	getch();
	return 0;
}

void heapsort(int array[], int n){
	int i,t;
	heapify(array,n);

	for(i=n-1 ; i>0 ; i--){
		t = array[0];
		array[0] = array[i];
		array[i] = t;
		adjust(array,i);
	}
}


void heapify(int array[], int n){
	int item,i,j,k;

	for(k=1 ; k<n ; k++){
		item = array[k];
		i = k;
		j = (i-1)/2;

		while( (i>0) && (item>array[j]) ){
			array[i] = array[j];
			i = j;
			j = (i-1)/2;
		}
		array[i] = item;
	}
}

void adjust(int array[], int n){
	int item,i,j;

	j = 0;
	item = array[j];
	i = 2*j+1;

	while(i<=n-1){
		if(i+1<= n-1)
			if(array[i] < array[i+1])
				i++;
		if(item < array[i]){
			array[j] = array[i];
			j = i;
			i = 2*j+1;
		}
		else
			break;
	}
	array[j] = item;
}