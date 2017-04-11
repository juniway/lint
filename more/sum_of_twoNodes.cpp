/*
Find out whether there exists two nodes that has a sum of specific number in a BST Node*
*/

#include<stdio.h>
#include<stdlib.h>
#include<stack>

using namespace std;
struct Node{
    int data;
    struct Node *left;
    struct Node *right;
};



Node* insert(int num){
    Node* root = (Node*)malloc(sizeof(struct Node*));
    root->data = num;
    root->left = NULL;
    root->right = NULL;
    return root;
}

bool twoNodesHaveSum(Node* root1, int sum, int *v1, int *v2){
    Node* root2 = root1;
    stack<Node*> s1, s2;
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
        if(s1.top()!=s2.top() && val1 + val2 == sum){
            *v1 = val1;
            *v2 = val2;
            return true;
        }
        else if(val1 + val2 > sum){
            root2 = s2.top();
            root2 = root2->left;
            s2.pop();
            root1 = NULL;
        }
        else{
            root1 = s1.top();
            root1 = root1->right;
            s1.pop();
            root2 = NULL;
        }
    }while((root1 || !s1.empty())&& (root2 || !s2.empty()));
    return false;
}

int main(){
    Node* root = insert(5);
    root->left = insert(2);
    root->left->left = insert(1);
    root->left->right = insert(3);
    root->right = insert(7);
    root->right->left = insert(6);
    root->right->right = insert(21);
    int v1,v2;
    if(sumNums(root,10,&v1,&v2)){
        printf("%d %d",v1,v2);
    }
    else
        printf("Sum not found!");
    return 0;
}