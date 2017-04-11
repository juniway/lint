// smipler
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

class Solution {
public:
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
  int overflow = 0;
      // Start typing your C/C++ solution below
        // DO NOT write int main() function
        ListNode rootNode(0);
        ListNode *pCurNode = &rootNode;
        int forward = 0;
        while(l1||l2)
        {
            int v1 = (l1 ? l1->val : 0);
            int v2 = (l2 ? l2->val : 0);
            int sum = v1 + v2 + forward;
            forward = sum / 10;
            sum = sum % 10;
            ListNode *pNode = new ListNode(sum);
            pCurNode->next = pNode;
            pCurNode = pNode;
            if(l1) l1 = l1->next;
            if(l2) l2 = l2 ->next;
        }
        if(forward > 0)
        {
            ListNode *pNode = new ListNode(forward);
            pCurNode->next = pNode;
        }
        return rootNode.next;
    }  
};