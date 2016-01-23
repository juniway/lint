/*
* Write a ¡°C¡± function to convert an array to a doubly-linked list.
*/

#include<stdio.h>
#include<stdlib.h>

typedef struct dlistNode{
    int data; 
	struct dlistNode *prev , *next; 
	
}dlistNode;

dlistNode *array_to_dll(int *arr, int n){ //array<int, n>
    dlistNode *dll = NULL;
    dlistNode *tail = NULL;
    if(!arr) 
        return NULL; // assert(arr);
    else {
        for(int i=0; i<n; i++){
            if(dll==NULL){ // for the first new node in double_linked_list
                dll= (dlistNode *) malloc(sizeof(dlistNode));
                dll->data = arr[i];
            	 dll->next = dll->prev = NULL;  // initialize head
                tail = dll;
            }
            else{
        	 dlistNode *newNode = (dlistNode *)malloc(sizeof(dlistNode));
        		
        	 tail->next= newNode;
        	 newNode->data = arr[i];
        	 newNode->prev = tail;
        	 newNode->next = NULL;
        	 tail = newNode;
            }
        }
        return dll;
    }
}
void print_dll(dlistNode* dll){
    while(dll!=NULL){
        printf("%d ", dll->data);
        dll = dll->next;
    }
}
// Driver Program
int main(){
    int array[]={6, 9, 11, 0, 18, 22, 7, 4, 1};
    int len = sizeof array/sizeof array[0];
    dlistNode *d = array_to_dll(array, len);
    print_dll(d);

    return 0;
}
