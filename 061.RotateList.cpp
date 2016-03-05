[LeetCode 61] Rotate List
Given a list, rotate the list to the right by k places, where k is non-negative.

For example:
Given 1->2->3->4->5->NULL and k = 2,
return 4->5->1->2->3->NULL.


ListNode *rotateRight(ListNode *head, int k) {
	if(head == NULL || k == 0) return head;
	int len = 1;
	ListNode *p = head;
	while(p->next != NULL){
		p = p->next;
		len++;
	}
	k = len - k % len; // 非常巧妙，对于类似的k可能大于len的情况都可以用这个办法解决
	p->next = head;
	int step =0;
	while(step < k){
		p = p->next;
		step++;
	}
	// k %= len;
	// int step = len - k;
	// while(step > 0){
	// 	p = p->next;
	// 	step--;
	// }


	head = p->next;
	p->next = NULL;
	return head;
}