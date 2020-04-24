http://www.geeksforgeeks.org/quicksort-on-singly-linked-list/
[GeeksforGeeks] QuickSort on Singly Linked List

QuickSort on Singly Linked List
QuickSort on Doubly Linked List is discussed here. QuickSort on Singly linked list was given as an exercise. Following is C++ implementation for same. The important things about implementation are, it changes pointers rather swapping data and time complexity is same as the implementation for Doubly Linked List.
In partition(), we consider last element as pivot. We traverse through the current list and if a node has value greater than pivot, we move it after tail. If the node has smaller value, we keep it at its current position.
In QuickSortRecur(), we first call partition() which places pivot at correct position and returns pivot. After pivot is placed at correct position, we find tail node of left side (list before pivot) and recur for left list. Finally, we recur for right list.

// C++ program for Quick Sort on Singly Linled List
#include <iostream>
#include <cstdio>
using namespace std;

/* a node of the singly linked list */
struct node
{
    int data;
    struct node *next;
};

/* A utility function to insert a node at the beginning of linked list */
void push(struct node** head_ref, int new_data)
{
    /* allocate node */
    struct node* new_node = new node;

    /* put in the data  */
    new_node->data  = new_data;

    /* link the old list off the new node */
    new_node->next = (*head_ref);

    /* move the head to point to the new node */
    (*head_ref)    = new_node;
}

/* A utility function to print linked list */
void printList(struct node *node)
{
    while (node != NULL)
    {
        printf("%d  ", node->data);
        node = node->next;
    }
    printf("\n");
}

// Returns the last node of the list
struct node *getTail(struct node *cur)
{
    while (cur != NULL && cur->next != NULL)
        cur = cur->next;
    return cur;
}

// Partitions the list taking the last element as the pivot
struct node *partition(struct node *head, struct node *end,
                       struct node **newHead, struct node **newEnd)
{
    struct node *pivot = end;
    struct node *prev = NULL, *cur = head, *tail = pivot;

    // During partition, both the head and end of the list might change
    // which is updated in the newHead and newEnd variables
    while (cur != pivot)
    {
        if (cur->data < pivot->data)
        {
            // First node that has a value less than the pivot - becomes
            // the new head
            if ((*newHead) == NULL)
                (*newHead) = cur;

            prev = cur;
            cur = cur->next;
        }
        else // If cur node is greater than pivot
        {
            // Move cur node to next of tail, and change tail
            if (prev)
                prev->next = cur->next;
            struct node *tmp = cur->next;
            cur->next = NULL;
            tail->next = cur;
            tail = cur;
            cur = tmp;
        }
    }

    // If the pivot data is the smallest element in the current list,
    // pivot becomes the head
    if ((*newHead) == NULL)
        (*newHead) = pivot;

    // Update newEnd to the current last node
    (*newEnd) = tail;

    // Return the pivot node
    return pivot;
}


//here the sorting happens exclusive of the end node
struct node *quickSortRecur(struct node *head, struct node *end)
{
    // base condition
    if (!head || head == end)
        return head;

    node *newHead = NULL, *newEnd = NULL;

    // Partition the list, newHead and newEnd will be updated
    // by the partition function
    struct node *pivot = partition(head, end, &newHead, &newEnd);

    // If pivot is the smallest element - no need to recur for
    // the left part.
    if (newHead != pivot)
    {
        // Set the node before the pivot node as NULL
        struct node *tmp = newHead;
        while (tmp->next != pivot)
            tmp = tmp->next;
        tmp->next = NULL;

        // Recur for the list before pivot
        newHead = quickSortRecur(newHead, tmp);

        // Change next of last node of the left half to pivot
        tmp = getTail(newHead);
        tmp->next =  pivot;
    }

    // Recur for the list after the pivot element
    pivot->next = quickSortRecur(pivot->next, newEnd);

    return newHead;
}

// The main function for quick sort. This is a wrapper over recursive
// function quickSortRecur()
void quickSort(struct node **headRef)
{
    (*headRef) = quickSortRecur(*headRef, getTail(*headRef));
    return;
}

// Driver program to test above functions
int main()
{
    struct node *a = NULL;
    push(&a, 5);
    push(&a, 20);
    push(&a, 4);
    push(&a, 3);
    push(&a, 30);

    cout << "Linked List before sorting \n";
    printList(a);

    quickSort(&a);

    cout << "Linked List after sorting \n";
    printList(a);

    return 0;
}


Output:

Linked List before sorting
30  3  4  20  5
Linked List after sorting
3  4  5  20  30


I have simpler and each to understand code

Node* Partition(Node* lowEnd, Node* highEnd, Node*& partitionIndexPrevNode)
{
Node* partitionIndexNode = lowEnd;
partitionIndexPrevNode = NULL;
int Pivot = highEnd->data;
for (Node* i = lowEnd; i != highEnd && i != NULL; i = i->next)
{
if (i->data <= Pivot)
{
if (i != partitionIndexNode)
{
swap(i->data, partitionIndexNode->data);
}
partitionIndexPrevNode = partitionIndexNode;
partitionIndexNode = partitionIndexNode->next;
}
}
if (partitionIndexNode != highEnd) {
swap(partitionIndexNode->data, highEnd->data);
}
return partitionIndexNode;
}
/*
1.Partition to place elements < pivot to left of partitionIndexNode
and elements > pivot to right of partitionIndexNode

2. QuickSort sub array left of partitionIndexNode i.e
QuickSort(lowEnd, partitionIndexPrevNode, the_head);

3. QuickSort sub array right of partitionIndexNode i.e
QuickSort(partitionIndexNode->next, highEnd, the_head);

*/
void QuickSort(Node* lowEnd, Node* highEnd)
{
if (lowEnd == NULL || highEnd == NULL) return;
if (lowEnd == highEnd) return; //Single Node exiting.

Node* partitionIndexPrevNode = NULL;
Node* partitionIndexNode = Partition(lowEnd, highEnd, partitionIndexPrevNode);

QuickSort(lowEnd, partitionIndexPrevNode);

if (partitionIndexNode != highEnd) //exclude Penultimate node
{
QuickSort(partitionIndexNode->next, highEnd);
}
}
void QuickSortLL(Node* head)
{
if (head == NULL) return;
Node* end = head;
while (end->next != NULL)
{
end = end->next;
}
QuickSort(head, end);
}

We are only doing this in case pivot was the smallest element. Eg if your linked list was 30->40->20->10->5->NULL.

Then initially, inside the partition function,

prev=NULL, pivot points to 5

curr points to 30, tail points to 5

now in while loop as we never get a node which is less than pivot node(in terms of data values) , therefore, it never goes in the 'if' block and hence *newhead=NULL. It always goes in the 'else' condition. So after this loop, the linked list becomes

5->30->40->20->10->NULL

and here *newhead was still pointing to NULL

therefore it should now point to pivot node as it is the smallest node in the linked list.

after this function

5 -> 30-> 40-> 20-> 10 ->NULL
newhead and pivot point to 5 and newend points to 10



// no need of quickSortRecur, quickSort(struct node **head_ref) is enough:
void quickSort(struct node **head_ref)
{
    struct node *head1,*head2,*pivot,*tail;

    if(*head_ref == NULL || (*head_ref)->next == NULL)
    	return;

    pivot = partition(*head_ref,&head1,&head2);
    quickSort(&head1);
    quickSort(&head2);

    if(head1 != NULL)
    {
	    tail = getTail(head1);
	    tail->next = pivot;
    }
    pivot->next = head2;

    *head_ref = head1 == NULL ? pivot : head1;
}

struct node *partition(struct node *head, struct node **head1_ref,struct node **head2_ref)
{
    struct node *temp1 = head;
    struct node *temp2 = head;
    struct node *pivot = head;
    struct node *t;

    while(temp2->next != NULL)
    {
    	if(temp2->next->data < pivot->data)
    	{
    		if(temp1 == temp2)
    		{
    			temp1 = temp1->next;
    			temp2 = temp2->next;
    		}
    		else
    		{
	    		t = temp1->next;
	    		temp1->next = temp2->next;
	    		temp2->next = temp2->next->next;
	    		temp1 = temp1->next;
	    		temp1->next = t;
	    	}
    	}
    	else
    		temp2 = temp2->next;
    }

    *head2_ref = temp1->next;
    temp1->next = NULL;
    *head1_ref = head->next;

    return pivot;
}


There is no need to move the elements which are greater than pivot element.

You can just move when the elements are small.
For eg.
C( CURRENT)
N( NEXT) ;

during the first partition call .
4->8->7->21->3->16->11-6
N P
C
here we select the pivot element as 6 .

4<6 swap 4 with curr and move , next element is 8.

4->8->7->21->3->16->11-6
C=4 , N=4.

8>6, don't swap the elements move to next.
4->8->7->21->3->16->11-6
C=4 , N=7

21>6 don't swap the elements move to next
4->8->7->21->3->16->11-6
C=4 N=21

3<6, swap the element with next of current;
4->3->7->21->8->16->11-6
C=3 N=8
16>6 don't do anything.
4->3->7->21->8->16->11-6
C=4 N=16

after the first call the elements will be

4->3->7->21->8->16->11-6
swap pivot with next of current i.e with 7 .

4->3->6->21->8->16->11-7

Now 6 is at its position, recur for left and right .



#include <iostream>
#include<cstdio>
#include<stdlib.h>
using namespace std;
struct node{
	int data;
	struct node* next;
};
void printList(struct node *node);
void push(struct node** head_ref, int new_data);
void quickSort(struct node**h);
struct node* quick_util(struct node** h,struct node** e);
struct node* partition(struct node** h,struct node** e);
void push(struct node** head_ref, int new_data)
{
    /* allocate node */
    struct node* new_node = new node;

    /* put in the data  */
    new_node->data  = new_data;

    /* link the old list off the new node */
    new_node->next = (*head_ref);

    /* move the head to point to the new node */
    (*head_ref)    = new_node;
}

/* A utility function to print linked list */
void printList(struct node *node)
{
    while (node != NULL)
    {
        printf("%d  ", node->data);
        node = node->next;
    }
    printf("\n");
}
void quickSort(struct node**h)
{
	struct node* c=*h;
	struct node* e;
	while(c->next)
	c=c->next;

	e=c;
	quick_util(h,&e);
}
struct node* quick_util(struct node** h,struct node** e)
{
	struct nde* nh;
	struct node* ne;
	struct node* t;
	struct node* pivot;
	if(*h==*e)
	return *h;
	if(*h==NULL)
	return NULL;
	pivot=partition(h,e);
	if((*h)!=pivot)
	{
		t=*h;
		while(t->next!=pivot)
		t=t->next;
		t->next=NULL;

		quick_util(h,&t);

		t->next=pivot;
	}
	ne=pivot->next;
	quick_util(&ne,e);
	pivot->next=ne;
	return *h;
}
struct node* partition(struct node** h,struct node** e)
{
	struct node* n;
	struct node* m=*e;
	struct node* p;
	struct node* prev=NULL;
	p=*e;
	n=*h;
	while(n!=p)
	{
		if(n->data>p->data)
		{
			if(prev==NULL)
			{
				*h=n->next;
				prev=*h;
				m->next=n;
				n=n->next;
				m=m->next;
				m->next=NULL;
			}
			else
			{
				prev->next=n->next;
				m->next=n;
				n=n->next;
				m=m->next;
				m->next=NULL;

			}
		}
		else
		{
			if(prev==NULL)
			{
				*h=n;
			}
			prev=n;
			n=n->next;
		}
	}
	*e=m;
	return p;
}
int main()
{
    struct node *a = NULL;
    push(&a, 5);
    push(&a, 20);
    push(&a, 4);
    push(&a, 60);
    push(&a, 30);
    push(&a, 12);
    push(&a, 45);
    push(&a, 2);

    cout << "Linked List before sorting \n";
    printList(a);

    quickSort(&a);

    cout << "Linked List after sorting \n";
    printList(a);

    return 0;
}


// dman
// quicksort on Singly linked_list;
// Enter -1 to end input
#include<iostream>
#include<bits/stdc++.h>
using namespace std;

struct node1
{
	int data;
	struct node1 *next;
};
typedef struct node1 node;


node * create_node(int data)
{

			node * head=(node *)malloc(sizeof(node));
			head->data=data;
			head->next=NULL;
			return head;
}

node *quick_sort(node *head)
{
	node *pivot=head;
	if(head->next==NULL)
		return head;
	node *head1=NULL, *head2=NULL,*temp1=NULL,*temp2=NULL;
	head=head->next;
	while(head!=NULL)
	{
		if(head->data<=pivot->data)
		{
			if(head1==NULL)
			{
				head1=head;
				temp1=head1;
			}
			else
			{
				temp1->next=head;
				temp1=temp1->next;
			}
		}
		else
		{
			if(head2==NULL)
			{
				head2=head;
				temp2=head2;
			}
			else
			{
				temp2->next=head;
				temp2=temp2->next;
			}
		}
		head=head->next;
	}
	if(temp1)
		temp1->next=NULL;
	if(temp2)
		temp2->next=NULL;
	if(head1)
		head1=quick_sort(head1);
	if(head2)
		head2=quick_sort(head2);
	if(head1)
	{
		head=head1;
		while(head1->next!=NULL)
			head1=head1->next;
		head1->next=pivot;
	}
	else
		head=pivot;
	pivot->next=head2;
	return head;
}

void print_ll(node *head)
{
	while(head!=NULL)
	{
		cout<<head->data<<" ";
		head=head->next;
	}
	cout<<endl;
}


int main()
{
	node *temp,*head;
	head=NULL;
	temp=head;
	int counter=0;
		int data;

	do
	{
		counter++;
		cin>>data;
		if(data!=-1)
		{
		if(head==NULL)
		{
			head=create_node(data);
			temp=head;
		}
		else
		{
			temp->next=create_node(data);
			temp=temp->next;
		}
		}
	}while(data!=-1);
	print_ll(head);
	head=quick_sort(head);
	print_ll(head);

return 0;
}