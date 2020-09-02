void MirrorBTree(BstNode *pNode){
	if(pNode == nullptr) return;
	if(pNode->m_pLeft == nullptr && pNode->m_pRight == nullptr)
		return;

	auto tmp = pNode->m_pLeft;
	pNode->m_pLeft = pNode->m_pRight;
	pNode->m_pRight = tmp;
	MirrorBTree(pNode->m_pLeft);
	MirrorBTree(pNode->m_pRight);
}