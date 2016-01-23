Merge Sort

/*
 The merge sort splits the list to be sorted into two equal halves, and places them in 
 separate arrays. Each array is recursively sorted, and then merged back together to 
 form the final sorted list. Like most recursive sorts, the merge sort has an algorithmic 
 has an complexity of O(n log n).
 Elementary implementations of the merge sort make use of three arrays - one for each half 
 of the data set and one to store the sorted list in. The below algorithm merges the arrays
 in-place, so only two arrays are required. There are non-recursive versions of the merge sort, 
 but they don't yield any significant performance enhancement over the recursive algorithm on 
 most machines.


Pros: Marginally faster than the heap sort for larger sets.

Cons: At least twice the memory requirements of the other sorts; recursive.
 */

#include <stdlib.h>
#include <stdio.h>




void mergeSort(int numbers[], int temp[], int array_size);
void m_sort(int numbers[], int temp[], int left, int right);
void merge(int numbers[], int temp[], int left, int mid, int right);

int numbers[10];
int temp[10];


int main()
{
  int i;

  
  printf("Enter the numbers you want to sort");
  for(i=0;i<10;i++)
   scanf("%d",&numbers[i]);
  
  //perform merge sort on array
  mergeSort(numbers, temp, NUM_ITEMS);

  printf("Done with sort.\n");

  for (i = 0; i < NUM_ITEMS; i++)
    printf("%i\n", numbers[i]);
}


void mergeSort(int numbers[], int temp[], int array_size)
{
  m_sort(numbers, temp, 0, array_size - 1);
}



void m_sort(int numbers[], int temp[], int left, int right)
{
  int mid;

  if (right > left)
  {
    mid = (right + left) / 2;
    m_sort(numbers, temp, left, mid);
    m_sort(numbers, temp, mid+1, right);

    merge(numbers, temp, left, mid+1, right);
  }
}


void merge(int numbers[], int temp[], int left, int mid, int right)
{
  int i, left_end, num_elements, tmp_pos;

  left_end = mid - 1;
  tmp_pos = left;
  num_elements = right - left + 1;

  while ((left <= left_end) && (mid <= right))
  {
    if (numbers[left] <= numbers[mid])
    {
      temp[tmp_pos] = numbers[left];
      tmp_pos = tmp_pos + 1;
      left = left +1;
    }
    else
    {
      temp[tmp_pos] = numbers[mid];
      tmp_pos = tmp_pos + 1;
      mid = mid + 1;
    }
  }

  while (left <= left_end)
  {
    temp[tmp_pos] = numbers[left];
    left = left + 1;
    tmp_pos = tmp_pos + 1;
  }
  while (mid <= right)
  {
    temp[tmp_pos] = numbers[mid];
    mid = mid + 1;
    tmp_pos = tmp_pos + 1;
  }

  for (i=0; i <= num_elements; i++)
  {
    numbers[right] = temp[right];
    right = right - 1;
  }
}