bools DoesTree1HaveTree2(BstNode*, BstNode*);

bool HasSubTree(BstNode* pRoot1, BstNode* pRoot2){
	bool result = false;
	if(pRoot1 != nullptr && pRoot2 != nullptr){
		if(pRoot1->m_data == pRoot2->m_data){
			result = DoesTree1HaveTree2(pRoot1, pRoot2);
		}
		if(!result){
			result = HasSubTree(pRoot1->left, pRoot2);
		}
		if(!result){
			result = HasSubTree(pRoot1->right, pRoot2);
		}
	}

	return result;
}

bool DoesTree1HaveTree2(BstNode* pRoot1, BstNode* pRoot2){
	if(pRoot1 == nullptr) return false;
	if(pRoot2 == nullptr) return true;

	if(pRoot1->m_data != pRoot2->m_data){
		return false;
	}

	return DoesTree1HaveTree2(pRoot1->m_left, pRoot2->m_left) && DoesTree1HaveTree2(pRoot1->m_right, pRoot2->m_right);
}