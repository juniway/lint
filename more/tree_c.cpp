
//iterative_inorder

#include<iostream>
#include<stack>
#include<vector>
#include<queue>
using namespace std;

struct Node{
    int data;
    struct Node *left, *right;
};

void insert(Node*&, int );
void search(Node*, int );
int postOrder_iterative(Node*);
int maxDepth(Node *);
void pre_order(Node *);
void in_order(Node *);
void post_order(Node *);
void morris_inorder(Node *root);
void morris_preorder(Node *node);

void printLevelOrder_oneQueue(Node *);
void visit(Node* node);


int height(Node* node){
	if(node == nullptr)
		return 0;
	return 1 + max(height(node->left), height(node->right));
}


int main(){
    Node* root = nullptr;
    /*
    insert(root, 11);
	insert(root, 8);
	insert(root, 16);
	insert(root, 6);
	insert(root, 9);
	insert(root, 12);
	insert(root, 17);
	insert(root, 3);
	insert(root, 7);
	*/
	insert(root, 5);
	insert(root, 7);
	insert(root, 10);
	insert(root, 3);
	insert(root, 6);
	// insert(root, 18);
	// insert(root, 55);
	// insert(root, 91);
	// insert(root, 83);
	
    
    printLevelOrder_oneQueue(root);
    // cout << endl;
	// inorder_iterative(root);
	// in_order(root);
	// morris_inorder(root);
    int ht = height(root);
    cout<<"height="<<ht<<endl;
    
	return 0;
}

void visit(Node* node){
	cout << node->data << " ";
}


void insert(Node*& root, int num){
    Node* newNode = (Node*)malloc(sizeof(struct Node)); // tree* root = new root
	newNode->data = num;
	newNode->left = newNode ->right = nullptr;
    
    Node* prev = root, * cur = root;

	while(cur!=nullptr){
		prev = cur;
		if(num <= cur->data)
			cur = cur->left;
		else
			cur = cur->right;
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

void search(Node* rootNode, int toFindNum){
    Node *current = rootNode;
//  Node *parent = rootNode;
    bool rootflag = false;
    if(current->data == toFindNum){
        rootflag = true;
        cout << "Found the element, it is root." << endl;
    }
    else{
        while(current && current->data != toFindNum){
            //parent = current;
            if(current->data >= toFindNum)
                current = current->left;
            else
                current = current->right;
        }
        if(current && !rootflag)
            cout<<"Found the element!"<<endl;
        else
            cout<<"Couldn't find the element"<<endl;
    }
}

void pre_order(Node *node){
    stack<Node*> stk;
    while(node != nullptr || !stk.empty()){
        if(node != nullptr){
            visit(node);
            if(node->right != nullptr)
                stk.push(node->right);
            node = node->left;
        }
        else{
            node = stk.top();
            stk.pop();
        }
    }
    cout << endl;
}

void in_order(Node *node) {
    stack<Node*> s; // Initially empty
		while(!s.empty() || node != nullptr) {
			if(node != nullptr){
				s.push(node);
				node = node->left;
			}
			else {
				Node *temp = s.top(); // visit(temp);
				cout << temp->data << " ";
	            s.pop();
				node = temp->right;
		}
	}
	cout << endl;
}

void post_order(Node *node){
	stack<Node*> stk;
	Node *lastvisitnode = nullptr;
	while(!stk.empty() || node != nullptr){
		if(node != nullptr){
			stk.push(node);
			node = node->left;
		}
		else{
			auto topnode = stk.top();
			if(topnode->right != nullptr && lastvisitnode != topnode->right)
				 /* if right child exists AND traversing node from left child, move right */
				node = topnode->right;
			else{
				visit(node);
				lastvisitnode = stk.top();
				stk.pop();
			}
		}	
	}
}


// MorrisInOrder()：
// while 没有结束
//    如果当前节点没有左后代
//      访问该节点
//      转向右节点
//    否则
//      找到左后代的最右节点，且使最右节点的右指针指向当前节点
//      转向左后代节点
void morris_inorder(Node *root){
   Node *p = root, *tmp;
   while(p){
       if (p->left == NULL){
           // printf("%d ", p->data);
           p = p->right;
       }
       else{
           tmp = p->left;
           while(tmp->right != NULL && tmp->right != p)
               tmp = tmp->right;
           if (tmp->right == NULL){
               tmp->right = p;
               p = p->left;
           }
           else{
               printf("%d ", p->data); 
               tmp->right = NULL;
               p = p->right;
           }
       }
   }
   cout << endl;
} 

// LeetCode, 
// Morris pre_order，时间复杂度O(n)，空间复杂度O(1)
// http://www.acmerblog.com/leetcode-solution-binary-tree-preorder-traversal-6351.html

// void morris_preorder(Node *node) {
//     Node *cur, *prev;
//     cur = node;
//     while (cur != nullptr) {
//         if (cur->left == nullptr) {
//             // result.push_back(cur->val);
//             prev = cur; // cur刚刚被访问过
//             cur = cur->right;
//         } else {
//             // 查找前驱
//             Node *node = cur->left;
//             while (node->right != nullptr && node->right != cur)
//                 node = node->right;
//             if (node->right == nullptr) { // 还没线索化，则建立线索
//                 // result.push_back(cur->val); // 仅这一行的位置与中序不同
//                 node->right = cur;
//                 prev = cur; // cur刚刚被访问过
//                 cur = cur->left;
//             } else {  // 已经线索化，则删除线索
//                 node->right = nullptr;
//                 // prev = cur; 不能有这句，cur已经被访问
//                 cur = cur->right;
//             }
//         }
//     }
// }


int postOrder_iterative(Node* root){
    cout<<"\n";
    if (root == nullptr)
        return 0;

    stack<Node*> st ;
    bool leftTraversed = false;
    
    int h = 0;
    while (true) {
        while (root != nullptr && leftTraversed == false) {
            st.push(root);
            root = root->left;
        }
        
        if (h < (int)st.size())
            h = st.size();
        
        if (st.empty())
            break;
        
        Node* temp = st.top();  

        if (temp->right && temp->right != root) {
            
            root = temp->right;
            leftTraversed = false;
        }
        else {
            root = st.top();
            st.pop();
            printf("%d, ", root->data);
            leftTraversed = true;
        }
    }
    
    return h;
}

int maxDepth(Node *node) {
	int height = 0;
	vector<Node*> v;
	Node* previous = nullptr;

	while (node != nullptr || v.size()){
		if (node){
			v.push_back(node);
			node = node->left;
			continue;
		}
		if (height < (int)v.size())
			height = v.size();

		if (v.back()->right == nullptr || previous == v.back()->right){
			previous = v.back();
			v.pop_back();
		}
		else
			node = v.back()->right;
	}

	return height;
}

void printLevelOrder_oneQueue(Node *root) {
	if (!root) return;
	queue<Node*> nodesQueue;
	int nodesInCurrentLevel = 0, nodesInNextLevel = 0;
	nodesQueue.push(root);
	++nodesInCurrentLevel;

	while (!nodesQueue.empty()){
		Node *currNode = nodesQueue.front();
		nodesQueue.pop();
		nodesInCurrentLevel--;
		if (currNode != nullptr){
			cout << currNode->data << " ";
			nodesQueue.push(currNode->left);
			nodesQueue.push(currNode->right);
			nodesInNextLevel += 2;
		}
		if (nodesInCurrentLevel == 0){
			cout << endl;
			nodesInCurrentLevel = nodesInNextLevel;
			nodesInNextLevel = 0;
		}
	}
}

