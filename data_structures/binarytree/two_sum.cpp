/*
09.
Problem: Given a binary search Node, please check whether there are 
         two nodes in it whose sum equals a given value.
*/

#include <iostream>
#include <stack>
#include "tree.hpp"

using namespace std;

bool twoNumberHasSumInSortedArray(int data[], int length, int sum, int *num1, int *num2);
bool TwoNodeHasSum(Node* root, int sum);

void insert(Node*& root, int num){
	Node* newNode = (Node*)malloc(sizeof(struct Node)); // Node* root = new root
	newNode -> data = num;
	newNode -> left = newNode ->right = nullptr;
    
    Node* prev = root, * cur = root;

	while(cur!=nullptr){
		prev = cur;
		if(num <= root -> data)
			cur = cur -> left;
		else
			cur = cur -> right;
	}
    if(root==nullptr)
		root=newNode;
    else{
    	if(num <= prev->data)
    		prev->left = newNode;
    	else
    		prev->right = newNode;
    }
}

bool sumNums(Node* root1, int sum, int *v1, int *v2){
	Node* root2 = root1;
	stack<Node*> s1, s2; // push parent nood in to the stack

	do{
		while(root1){
			s1.push(root1);
			root1 = root1->left;
		}
		while(root2){
			s2.push(root2);
			root2 = root2->right;
		}

		int val1 = s1.top()->data;
		int val2 = s2.top()->data;

		if(s1.top()!= s2.top() && val1 + val2 == sum){
			*v1 = val1;
			*v2 = val2;
			return true;
		}
		else if(val1 + val2 > sum){
			root2 = s2.top()->left;
			s2.pop();
			root1 = nullptr; 
		}
		else{
			root1 = s1.top()->right;
			s1.pop();
			root2 = nullptr;
		}
	} while((root1 || !s1.empty()) && (root2 || !s2.empty()));
	return false;
}


int main(){
	Node* root = nullptr;
	insert(root, 2);
	insert(root, 1);
	insert(root, 3);
	insert(root, 7);
	insert(root, 6);
	insert(root, 21);
/*
	int v1, v2;
	if(sumNums(root, 10, &v1, &v2)){
		printf("%d %d", v1, v2);
	}
	else
		printf("Sum not found!");
	printf("\n");
*/
	//if(TwoNodeHasSum(root, 10))
		//printf("two nodes has sum\n");

/*
	int numarr[10] = {2, 8, 13, 22, 23, 29, 30, 31, 33, 37};
	int a1, a2;
    if(numberHasSumInArray(numarr, 10, 46, &a1, &a2))
        cout<<a1<<" "<<a2<<endl;
*/
	return 0;
}

bool twoNumberHasSumInSortedArray(int data[], int length, int sum, int *num1, int *num2){
    //bool found = false;
	if(length <1 || num1 == nullptr || num2 == nullptr)
		return false;

	int end = length -1;
	int start = 0;

	while(end > start){
		long long curSum = data[end] + data[start];

		if(curSum == sum){
			*num1 = data[start];
			*num2 = data[end];
			break;
		}
		else if(curSum < sum)
			start ++;
		else
			end--;
	}
    return end<=start?false:true;
}

/*
Inspired by the solution, we may find two nodes with a given sum
in a binary search Node with similar strategy. Firstly we initialize 
a pointer P1 to the smallest node in the Node, and another pointer 
P2 to the greatest node. When the sum of two values in the nodes 
pointed by P1 and P2 is same as the given value, two required nodes 
have been found. If their sum is greater than the given value, 
we move P2 to the previous node (containing less value). Moreover, 
we move P1 to the next node (containing greater value) if their sum 
is less than the given value.

It is not difficult to get the least and greatest value of a binary 
search Node. If we move along the links to left children, and the leaf 
node we arrive at finally contains the least value. For instance, if 
we move along the links to left children in Figure 1, the nodes on the 
path contain value 32, 24, 21 and 14, and 14 is the least value in the 
binary search Node.

Similarly, if we move along links to right children, and the leaf node 
we arrive at finally contains the greatest value.
*/

/**************************************************************************
The key to solve this problem is how to get the next nodes (with greater 
values) and the previous nodes (with less values) in a binary search Node. 
Let’s utilize stacks.

In order to get next nodes, we scan the Node along the links to leaf children, 
and push the scanned nodes into a stack. 

The steps to get the next node:
If the node on the top does not have a right child, the node is popped off, 
and the next node is on the top again. If the node on the top has a right 
child, after the node is popped off and then the right child is pushed, 
and all nodes along the links to left children are pushed into the stack. 
The last pushed node on the top is the next node. We continue the steps to
pop and push until the stack is empty.

The steps to get previous nodes:
At first we push the root node, and nodes along the links to right children.
The node with least is on the top of stack. In order to get the previous 
nodes with less values, the top is popped off. If the top does not have a 
left child, the previous node is the new top node in the stack. If the top 
has the left child, we push its left child, as well as nodes along links 
to right children. The last pushed node is the previous node of the node 
popped

*************************************************************************/

bool TwoNodeHasSum(Node* root, int sum){
	stack<Node*> biggerNodeStack, smallerNodeStack;

	//push all nodes in the path to the left-most(smallest) node into stack1
	//push all nodes in the path to the right-most(biggest) node into stack2
	Node *tmpLeft = root, *tmpRight = root;
	while(tmpLeft){
		biggerNodeStack.push(tmpLeft);
		tmpLeft = tmpLeft -> left;
	}
	
	while(tmpRight){
		smallerNodeStack.push(tmpRight);
		tmpRight = tmpRight -> right;
	}
	int nodeSum=biggerNodeStack.top()->data + smallerNodeStack.top()->data;

	while( nodeSum!= sum && !biggerNodeStack.empty() &&!smallerNodeStack.empty()){
		if(nodeSum < sum){
			tmpLeft  = biggerNodeStack.top();
			biggerNodeStack.pop();
			tmpLeft = tmpLeft -> right;
			while(tmpLeft){
				biggerNodeStack.push(tmpLeft);
				tmpLeft = tmpLeft -> right;
			}
		}
		else{
			tmpRight = smallerNodeStack.top();
			smallerNodeStack.pop();
			tmpRight = tmpRight -> left;
			while(tmpRight){
				smallerNodeStack.push(tmpRight);
				tmpRight = tmpRight -> left;
			}
		}
		nodeSum=biggerNodeStack.top()->data + smallerNodeStack.top()->data;
	}

	if(nodeSum == sum)
		return true;
	else
		return false;
	
}


/*
Problem 2: Given an array, please determine whether it contains three numbers 
whose sum equals to 0.

Analysis: This problem is also required to find some numbers with a given array 
and sum, it is similar to the first problem. We may get some hints from the 
solution above.

Since the input of the previous problem is an increasingly sorted array, we can 
also firstly sort the input array increasingly. Secondly we scan the array. 
When we reach the i-th number with value n, we try to find whether there are two 
numbers whose sum is –n in the array excluding the i-th number.

*/

bool twoNumbersHasSumInArray(int numbers[], int length, int sum, int excludeIndex){
	bool found = false;
	int startIndex = 0, endIndex = length -1;
	while(startIndex < endIndex){
		if(startIndex == excludeIndex)
			startIndex++;
		if(endIndex == excludeIndex)
			endIndex--;

		long long currSum = numbers[startIndex]+numbers[endIndex];
		if(currSum==sum){
			found = true;
			break;
		}
		else if(currSum < sum)
			startIndex++;
		else
			endIndex--;
	}
	return found;
}

bool threeNumbersHasSumZero(int numbers[], int length){
	bool found = false;
	if(!numbers || length < 3)
		return false;

	std::sort(number, number + length -1);
	for(int i=0; i<length, ++i){
		int sum = -data[i];
		found = twoNumbersHasSumZero(numbers, length, sum, i);
		if(found)
			break;
	}

	return found;

}