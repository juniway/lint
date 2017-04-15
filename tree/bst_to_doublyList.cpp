#include<stdio.h>
#include<stdlib.h>

struct BST_NodeT{
    int data;
    struct BST_Node *left, *right;
};

typedef struct BST_NodeT BST_Node;

void InOrder(BST_Node* parent, BST_Node*& first, BST_Node*& last){
    if(parent->left != nullptr){
        BST_Node* tmpLast;
        InOrder(parent->left, first, tmpLast);
        parent->left = tmpLast;
        tmpLast->right = parent;
    }
	else // if the node does not have left sub-tree
		first = parent;
	
    if (parent->right != nullptr){
        BST_Node* tmpFirst;
        InOrder(parent->right, tmpFirst, last);
        parent->right = tmpFirst;
        tmpFirst->left = parent;
    }
    else
		last = parent; // if the node does not have left sub-tree
}
 
BST_Node* TreeToList(BST_Node* root){
    if(nullptr == root) return nullptr;
    
    BST_Node* first;
    BST_Node* last;
    InOrder(root, first, last);
    first->left = last;
    last->right = first;
    
    return first;
}

//a function that creates, initializes, and returns a new BST_node
BST_Node *createNewNode(int val) {
    BST_Node *newnode = (BST_Node*)malloc(sizeof(BST_Node));
    if( newnode == nullptr) {
        return nullptr;
    }
    newnode->data = val;
    newnode->right = newnode->left = nullptr;
    return newnode;
}

//insert a node to the tree
BST_Node *insert(BST_Node *root, int data){
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

void print_dll(BST_Node* node){
    BST_Node* root = node;
    while(node!=nullptr){
        printf("%d ", node->data);
        node=node->right;
        if(node==root) break;
    }
}

void PreOrderTraversal(BST_Node *root){
    if(root!=nullptr){
        printf("%d ", root->data);
        PreOrderTraversal(root->left);
        PreOrderTraversal(root->right);
    }
    
}

void InOrderTraversal(BST_Node *root){
    if(root!=nullptr){
        InOrderTraversal(root->left);
        printf("%d ", root->data);
        InOrderTraversal(root->right);
    }
}


void PostOrderTraversal(BST_Node *root){
    if(root!=nullptr){
        PostOrderTraversal(root->left);
        PostOrderTraversal(root->right);
        printf("%d ", root->data);
    }
}

int main(){
    BST_Node* bst =nullptr;
    
    bst = insert(bst, 10);
    bst = insert(bst, 6);
    bst = insert(bst, 4);
    bst = insert(bst, 8);
    bst = insert(bst, 14);
    bst = insert(bst, 12);
    bst = insert(bst, 16);
   
    BST_Node* dll = TreeToList(bst);
    print_dll(dll);
    
    return 0;
}
/*
alternative solution:

void ConvertNode(BST_Node* pNode, BST_Node*& pLastNodeInList){
    if(pNode == nullptr)
        return;

    BST_Node *pCurrent = pNode;

    if (pCurrent->left != nullptr)
        ConvertNode(pCurrent->left, pLastNodeInList); // move pCurrent to the left most leaf

    pCurrent->left = pLastNodeInList; // initially pLastNodeInList is nullptr, then it is updated to pCurrent
	
    if(pLastNodeInList != nullptr)
        pLastNodeInList->right = pCurrent;
    pLastNodeInList = pCurrent;

    if (pCurrent->right != nullptr)
        ConvertNode(pCurrent->right, pLastNodeInList);
}

BST_Node* bst_to_dll(BST_Node* pRootOfTree)
{
    BST_Node *pLastNodeInList = nullptr;
    ConvertNode(pRootOfTree, pLastNodeInList);

    // pLastNodeInList points to the tail of double-linked list,
    // but we need to return its head
    BST_Node *pHeadOfList = pLastNodeInList;
    while(pHeadOfList != nullptr && pHeadOfList->left != nullptr)
        pHeadOfList = pHeadOfList->left;

    return pHeadOfList;
}

*/