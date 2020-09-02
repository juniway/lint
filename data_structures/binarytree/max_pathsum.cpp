#include <iostream>
#include <algorithm>
#include <limits.h>

using namespace std;

struct Node{
    Node *left, *right;
    int val;

    Node(int v){
        val = v;
        left = NULL;
        right = NULL;
    }
};

Node* createTree(){
    /*
            3
           / \
          2   20
         /   /  \
        7   5   -8

    */
    Node* root = new Node(-10);

    // Creating 2nd level:
    Node* one = new Node(2);
    Node* two = new Node(1);
    root->left = one;
    root->right = two;

    // Creating 3rd level:
    // Node* three = new Node(7);
    // Node* four = new Node(5);
    // Node* five = new Node(-8);
    // one->left = three;
    // two->left = four;
    // two->right = five;

    return root;
}

int findMaxSum(Node* root, int &globalMax){
    if(root == NULL) return 0;

    int left = findMaxSum(root->left, globalMax);
    int right = findMaxSum(root->right, globalMax);

    int returnMax = std::max(std::max(left, right) + root->val, root->val);

    // int max = std::max(returnMax, left + right + root->val);
    // if(max > globalMax)
    //     globalMax = max;
    globalMax = std::max(globalMax, std::max(returnMax, left + right + root->val));

    return returnMax;
}

int main(){
    Node* myTree = createTree();

    int globalMax = INT_MIN;
    findMaxSum(myTree, globalMax);

    cout << "Maximum possible sum: " << globalMax << endl;

    return 0;
}

