 
 

 // inOrder: left->root->right
void in_order(Node* node){

    std::stack<Node*> stk;
    while(node != nullptr || !stk.empty()){
        if(node != nullptr){
            stk.push(node);
            node = node->left;
        }
        else{
            node = stk.top(); // cout << node;
            stk.pop();
            node = node->right;
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
}


void pre_ord(Node *head){
     vector<node*> v;
     if(head == NULL)
       return;
     
     node *root = head;
     v.push_back(root);
     while(v.size()){
          while(root->left != NULL){
             v.push_back(root->left);
             root = root->left;
          }
          node *tmp = v.back();
          v.pop_back();
          cout<<"Data = "<<tmp->data<<endl;
          if(tmp->right != NULL){
             v.push_back(tmp->right);
             root = tmp->right;
          }
     }
}



template <typename TreeNode, typename Visitor>
void binary_tree_traverse_inorder(TreeNode* node, Visitor visit)
{
    std::stack<TreeNode*> stack;
    while (node || !stack.empty()) {
        if (node) {
            // go left as far as possible, push to the stack
            stack.push(node);
            node = node->left;
        } else {
            // we are at the bottom, pop from the stack
            node = stack.pop();
            visit(node);
            node = node->right;
        }
    }
}


 void inOrderTraversalWithoutRecursion(struct node* node){
  std::stack<struct node*> stk;
  struct node* current = node;
  while(current != nullptr){
    while(current != nullptr){
      stk.push(current);
      current = current->left;
    }
    // now stack stores all the nodes along the path to the left leaf
    // we reach to the left leaf node
    while(current == nullptr && !stk.empty()){
      current = stk.top();
      stk.pop();
      printf("%d \t", current->data);
      current = current->right;
    }
  }
}
