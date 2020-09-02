#include <iostream>
#include <vector>
#include <stack>
#include "../tree.hpp"
using namespace std;

// The key point is:
// when you pop a node from stack, ensure its children is not explored already

void post_order(Node *root){
    stack<Node*> s;
    Node *lastvisitnode = nullptr;
    while(!s.empty() || root != nullptr){
        if(root != nullptr){
            s.push(root);
            root = root->left;
        }
        else{
            Node *p = s.top();
            if(p->right != nullptr && p->right != lastvisitnode)
                root = p->right;
            else{
                cout << p->data << " ";
                lastvisitnode = p;
                s.pop();
            }
        }
    }
}

vector<int> post_order1(Node* root) {
    vector<int> res;
    stack<Node*> s;
    s.push(root);
    while (!s.empty()) {
        root = s.top();
        s.pop();
        res.push_back(root->data);
        if (root->left) s.push(root->left);
        if (root->right) s.push(root->right);
    }
    reverse(res.begin(), res.end());
    return res;
}

vector<int> post_order2(Node* root) {
    vector<int> res;
    stack<Node*> s;
    while(!s.empty() || root) {
        if (root != nullptr) {
            s.push(root);
            res.push_back(root->data);
            root = root->right;
        } else {
            root = s.top()->left;
            s.pop();
        }
    }

    reverse(res.begin(), res.end());
    return res;
}

void postorder(Node* head) { 
    Node* temp = head; 
    unordered_set<Node*> visited; 
    while (temp && visited.find(temp) == visited.end()) { 
  
        // Visited left subtree 
        if (temp->left &&  
         visited.find(temp->left) == visited.end()) 
            temp = temp->left; 
  
        // Visited right subtree 
        else if (temp->right &&  
        visited.find(temp->right) == visited.end()) 
            temp = temp->right; 
  
        // Print node 
        else { 
            printf("%d ", temp->data); 
            visited.insert(temp); 
            temp = head; 
        } 
    } 
} 

// https://www.geeksforgeeks.org/postorder-traversal-binary-tree-without-recursion-without-stack/?ref=rp

void testPostOrder() {
    Node *root = BuildSimpleBST();
    auto res = post_order2(root);

    for (auto v : res) cout << v << " ";
    cout << endl;
}

int main(int argc, char *argv[]) {
    testPostOrder();
    return 0;
}
