ListNode* ReverseList(ListNode* pHead){
	ListNode* pReversedHead = nullptr;
	ListNode* pNode = pHead;
	ListNode* pPrev = nullptr;

	while(pNode != nullptr){
		ListNode* pNext = pNode->m_pNext;
		if(pNext == nullptr){
			pReversedHead = pNode;
		}
		pNode->m_pNext = pPrev;
		pPrev = pNode;
		pNode = pNext;
	}

	return pReversedHead;
}

ListNode* ReversedList(ListNode* pHead){
	std::stack<ListNode*> st;
	while(pHead != nullptr){
		st.push(pHead);
		pHead = pHead->m_pNext;
	}

	pHead = st.top();
	ListNode* cur = pHead;

	while(true){
		st.pop();
		if(st.empty()){
			cur->next = nullptr;
			return pHead;
		}
		cur->next = st.top();
	}
}