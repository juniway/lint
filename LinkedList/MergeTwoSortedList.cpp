// recursive method

ListNode* Merge(ListNode* pHead1, ListNode* pHead2){
	if(pHead1 == nullptr){
		return pHead2;
	}
	else if(pHead2 == nullptr){
		return pHead1;
	}

	ListNode* pMergedHead = nullptr;
	if(pHead1->m_data < pHead2->m_data){
		pMergedHead = pHead1->m_data;
		pMergedHead->m_next = Merge(pHead1->m_next, pHead2);
	}
	else{
		pMergedHead = pHead2->m_data;
		pMergedHead->m_next = Merge(pHead1, pHead2->m_next);
	}

	return pMergedHead;
}

