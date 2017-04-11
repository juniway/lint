Add Two Numbers
You are given two linked lists representing two non-negative numbers. 
The digits are stored in reverse order and each of their nodes contain a single digit. 
Add the two numbers and return it as a linked list.

Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
Output: 7 -> 0 -> 8

class Solution {
public:
	ListNode* addTwoNumbers(ListNode *l1, ListNode *l2){

	// Start typing your C/C++ solution below
	// DO NOT write int main() function
	ListNode *head = new ListNode(0);
	ListNode *cur = head;
	int add = 0;
	//print(head);
	//cout<<"the result"<<endl;
	while ( l1 != NULL || l2 != NULL || add == 1){
		if (add == 1){
			cur->val = 1;
			add = 0;
		}

		if (l1 !=NULL && l2 == NULL){ // list1 is not empty, but list2 is empty
			if(cur->val + l1->val > 9)
				add = 1;
				cur->val = (cur->val + l1->val)%10;
		}
		else if(l1 == NULL && l2 != NULL){ // list 1 is empty, but list2 is not empty
			if(cur->val + l2->val > 9)
				add = 1;
			cur->val = (cur->val + l2->val)%10;
		}
		
		if(l1 == NULL && l2 == NULL && add == 1){ // list1 and list2 both are empty, and add is 1
			cur->val = 1;
		}
		
		if(l1 != NULL && l2 != NULL){ // l1 and l2 both are not empty
			if(cur->val + l1->val + l2->val > 9)
				add = 1;
			cur->val = (cur->val + l1->val + l2->val)%10;
			//l1 = l1->next;
			//l2 = l2->next;
		} 
		if(l1 == NULL || l1->next == NULL)
			l1 = NULL;
		else
			l1 = l1->next;
		
		if(l2 == NULL || l2->next == NULL)
			l2 = NULL;
		else
			l2 = l2->next;
		
		if(l1 != NULL || l2 != NULL || add == 1){
			cur->next = new ListNode(0);
			cur = cur->next;
		}
		//print(head);
	} // end of while() loop
	
	cur->next = NULL; 
	//print(head);
	return head;
	}
};

class Solution {
public:
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
  int overflow = 0;
        ListNode *ret = NULL;
        ListNode **pnode = &ret;
        while(l1 && l2) {
            int val = l1->val + l2->val + overflow;
            overflow = val / 10;
            *pnode = new ListNode(val % 10);
            pnode = &((*pnode)->next);
            l1 = l1->next;
            l2 = l2->next;
        }
        ListNode *lremain = l1 ? l1 : l2;
        while(lremain) {
            int val = lremain->val + overflow;
            overflow = val / 10;
            *pnode = new ListNode(val % 10);
            pnode = &((*pnode)->next);
            lremain = lremain->next;
        }
        if(overflow > 0) {
            *pnode = new ListNode(overflow);
        }
        return ret;
  
    }  
};