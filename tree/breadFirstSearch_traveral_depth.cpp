/*
 * breadFirstSearch_traveral_depth.cpp
 */

 /*
refer:http://leetcode.com/2010/04/maximum-height-of-binary-tree.html

As we traverse the tree, we would keep track of the current depth 
and record each node’s depth, so that we know which depth we are in 
when we return to the node at a later time. 
(In pre-order or in-order traversals, it might return several levels 
above the current level when a node is popped off the stack).

On the other hand, post-order traversal guarantees to return exactly 
one level above a node that is popped off the stack. Therefore, 
we could devise a solution utilizing post-order traversal without 
modifying the existing tree structure. We keep track of the current 
depth and update the maximum depth as we traverse the tree.

Another solution is to utilize Breadth-first Search (BFS). Unlike DFS, 
we traverse the tree level by level, thus we are able to obtain the max 
depth in a direct manner. Read my post: Printing a Binary Tree in Level 
Order for more information.
 */




/*
DFS uses a data structure called Stack and is commonly implemented using 
recursion (since function calls are pushed and popped off the memory stack). 
If recursion is not allowed, we can simulate the recursion by using iterative 
method with the help of stack. See my older post: Binary Search Tree In-Order 
Traversal Iterative Solution on how to do a DFS iteratively using a stack.

The most natural solution for level-order traversal is Breadth First Search
 (BFS), since it visits the nodes level by level. BFS requires the use of a
  data structure called Queue, which is a First In First Out (FIFO) structure. 
  If you are curious, level-order traversal can be implemented using DFS too. 
  See my next post: Binary Tree Level-Order Traversal Using Depth First Search
   (DFS) for the challenge.

In order to print the binary tree in level order with newline in the end of 
each level, we can utilize two queues. The first queue stores the current 
level’s nodes, while the second queue stores the next level’s nodes (the 
current level nodes’ children).

When the first queue is emptied, we know that it must have reached the end 
of the current level, therefore we print a newline. Then, we switch the 
emptied first queue with the second queue (which is populated with the next 
level’s nodes). Then we repeat the process over again.

*/
    
// http://leetcode.com/2010/09/printing-binary-tree-in-level-order.html


void printLevelOrder_twoQueues(Node *root){
	if(!root) return;
	queue<Node*> currentLevel, nextLevel;
	currentLevel.push(root);
	while(!currentLevel.empty()){
		Node *currNode = currentLevel.front();
		currentLevel.pop();
		if(currNode){
			printf("%d ", currNode->data);
			nextLevel.push(currNode->left);
			nextLevel.push( currNode->right);
		}
		if(currentLevel.empty()){
			cout<<endl;
			std::swap(currentLevel, nextLevel);
		}
	}
}

/*
Is it possible that a solution exists using only one single queue? 
Yes, you bet. 
The single queue solution requires two extra counting variables 
which keep tracks of the number of nodes in the current level 
(nodesInCurrentLevel) and the next level (nodesInNextLevel). 
When we pop a node off the queue, we decrement nodesInCurrentLevel 
by one. When we push its child nodes to the queue, we increment 
nodesInNextLevel by two. When nodesInCurrentLevel reaches 0, 
we know that the current level has ended, therefore we print 
an endline here.
*/

void printLevelOrder_oneQueue(Node *root) {
	if (!root) return;
	queue<Node*> nodesQueue;
	int nodesInCurrentLevel = 0, nodesInNextLevel = 0;
	nodesQueue.push(root);
	++nodesInCurrentLevel;

	while (!nodesQueue.empty()) {
		Node *currNode = nodesQueue.front();
		nodesQueue.pop();
		nodesInCurrentLevel--;
		if (currNode) {
			cout << currNode->data << " ";
			nodesQueue.push(currNode->left);
			nodesQueue.push(currNode->right);
			nodesInNextLevel += 2;
		}
		if (nodesInCurrentLevel == 0) {
			cout << endl;
			nodesInCurrentLevel = nodesInNextLevel;
			nodesInNextLevel = 0;
		}
	}
}
/*
Given a binary tree, print out the tree in level order 
(ie, from left to right, level by level). Output a newline 
after the end of each level. Breadth First Search (BFS) is not allowed.

given:
  	3
   /  \
  9   20    
     /  \
    15    7

output:
3 
9 20 
15 7

*/
/*
http://leetcode.com/2010/09/binary-tree-level-order-traversal-using_17.html

In my last post: Printing Binary Tree in Level Order, we discuss how to 
print a tree using Breadth First Search (BFS). The challenge now is, 
can you do it using Depth First Search (DFS) this time?

Hint:
Write a function call printLevel(BinaryTree *p, int level) which will print 
all nodes of a given level. Assume you know the height of the tree, then 
you can print the entire tree level by level utilizing printLevel.

Solution:
printLevel function can be solved using DFS. Decrement level by one as you 
advance to the next level. When level equals 1, you’ve reached the given 
level. To find the maximum height (or the max depth) of a tree, you can 
read my post: Maximum Height of a Binary Tree.
*/





/*
Further Thoughts: 
If you look carefully, you will notice that the DFS solution traverses the 
same node multiple times. Since BFS traverses each node exactly one time, 
BFS is much more efficient than DFS.

Could you find the run time complexity for the DFS level-order traversal 
solution? Try to estimate as best as you can, and then find the correct 
answer by proving it using Math. Does your estimate fares well with the 
correct answer? Why?

Answer:
Although the DFS solution traverse the same node multiple times, it is 
not another order slower than the BFS solution. Here is the proof that 
the DFS solution above runs in O(N) time, where N is the number of nodes 
in the binary tree and we assume that the binary tree is balanced.

We first compute the complexity of printLevel for the kth level:

T(k) = 2T(k-1) + c
     = 2k-1 T(1) + c
     = 2k-1 + c
Assuming it’s a balanced binary tree, then it would have a total of 
lg N levels.

Therefore, the complexity of printing all levels is:

T(1) + T(2) + ... + T(lg N)
= 1 + 2 + 22 + ... + 2lg N-1 + c
= O(N)
Finding the maximum height of the tree also takes O(N) time, therefore 
the overall complexity is still O(N).
*/

*/