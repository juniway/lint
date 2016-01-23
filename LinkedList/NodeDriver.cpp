#include <cstdio>
#include <cstdlib>
#include <stack>

struct BstNode{
    int data;
    struct BstNode *left, *right;
};

void InOrder(BstNode* parent, BstNode*& first, BstNode*& last){
    if(parent->left != nullptr){
        BstNode* tmpLast;
        InOrder(parent->left, first, tmpLast);
        parent->left = tmpLast;
        tmpLast->right = parent;
    }
    else // if the node does not have left sub-tree
        first = parent;
    
    if (parent->right != nullptr){
        BstNode* tmpFirst;
        InOrder(parent->right, tmpFirst, last);
        parent->right = tmpFirst;
        tmpFirst->left = parent;
    }
    else
        last = parent; // if the node does not have left sub-tree
}

BstNode* TreeToList(BstNode* root){
    if(nullptr == root) return nullptr;
    
    BstNode* first;
    BstNode* last;
    InOrder(root, first, last);
    first->left = last;
    last->right = first;
    
    return first;
}

BstNode *createNewNode(int val) {
    BstNode *newnode = (BstNode*)malloc(sizeof(BstNode));
    if( newnode == nullptr) {
        return nullptr;
    }
    newnode->data = val;
    newnode->right = newnode->left = nullptr;
    return newnode;
}

BstNode *insert(BstNode *root, int data){
    if(!root) 
        return createNewNode(data);
    else{
        if(data<=root->data)
            root->left = insert(root->left, data);
        else
            root->right = insert(root->right, data);
    }
    
    return root;
}

void print_dll_inorder(BstNode* node){
    BstNode* root = node;
    while(node!=nullptr){
        printf("%d ", node->data);
        node=node->right;
        if(node==root) break;
    }
    printf("\n");
}

void visit(BstNode* node){
	printf("%d ", node->data);
}

void visit_preorder(BstNode *node){
	std::stack<BstNode*> st;
	while(!st.empty() || node != nullptr){
		if(node != nullptr){
			visit(node);
			if(node->right != nullptr){
				st.push(node->right);
			}
			node = node->left;
		}
		else{
			node = st.top();
			st.pop();
		}
	}
	printf("\n");
}


int main(){
    BstNode* bst =nullptr;
    
    bst = insert(bst, 10);
    bst = insert(bst, 6);
    bst = insert(bst, 4);
    bst = insert(bst, 8);
    bst = insert(bst, 14);
    bst = insert(bst, 12);
    bst = insert(bst, 16);
   
    // BstNode* dll = TreeToList(bst);
    // print_dll(dll);
    
    visit_preorder(bst);

    return 0;
}