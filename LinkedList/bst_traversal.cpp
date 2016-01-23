// root -> left -> right
void iterative_preorder(BstNode *node){
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

// left -> root -> right
void iterative_inorder(BstNode *node){
	std::stack<BstNode*> st;
	while(!st.empty() || node != nullptr){
		if(node != nullptr){
			st.push(node);
			node = node->left;
		}
		else{
			node = st.top();
			visit(node);
			st.pop();
			node = node->right;
		}
	}
}

void iterative_postorder(BstNode *node){
	
}