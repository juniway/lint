#include <stdio.h>
#include <stdlib.h>

void HeapSort(int num[],int size);
void BuildHeap(int num[] ,int size);
void PercolateDown(int num[] , int index,int size);

void Print(const char* strMsg,int array[],int nLength);
void Swap(int num[] , int v, int u);

int main(int argc, char *argv[]){

    int data[] = {8, 5, 4, 6,7, 1, 9, 3, 2};
    HeapSort(data,);
    system("PAUSE"); 
    return 0;
}


void HeapSort(int num[] ,int size){

    int i;
    int iLength = size;
    // Print("Before Sort:",num,iLength);

    BuildHeap(num,size);
    for (i = iLength - 1; i >= 1; i--) {  
        Swap(num, 0, i);  
        size--;
        PercolateDown(num, 0,size);
        // Print("Sort Heap:",num,iLength); 
    }

}

//   
void BuildHeap(int num[] ,int size) {
    for (int i = size / 2 - 1; i >= 0; i--) {
        PercolateDown(num, i, size);
        Print("Build heap:", num, size);
    }
}

//   
void PercolateDown(int num[] , int index, int size) {
    int min;
    while (index * 2 + 1<size) {
        min = index * 2 + 1;
        if (index * 2 + 2<size) {
            if (num[min] > num[index * 2 + 2]) {
                min = index * 2 + 2;
            }
        }
        
        if (num[index] < num[min]) {
            break;
        } else {
            Swap(num, index, min);
            index = min;
        }
    }
}


