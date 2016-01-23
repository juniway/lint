class Solution{
public:
	ListNode *removeNthFromEnd(ListNode *head, int k){
		if(n == 0) return head;
		int num = 0;
		ListNode* curSlow = head;
		ListNode* curFast = head;

		for(int i = 0; i < k; ++i){
			curFast = curFast->next;
		}
		while(curFast != nullptr){
			curSlow = curSlow->next;
			curFast = curFast->next;
		}
		if(curSlow == head){

		}else{
			
		}
		return curSlow;

	}
}