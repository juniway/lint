struct ListNode{
public:
    ListNode(int value):val(value){}
    ListNode *next;
    int val;
};

class Solution{
public:
    ListNode *AddTwoNumbers(ListNode *l1, ListNode *l2){
        int carry = 0;
        ListNode head(0);
        ListNode *pcur = &head;

        while(l1 != nullptr || l2 != nullptr){
            int val1 = l1 ? l1->val : 0;
            int val2 = l2 ? l2->val : 0;
            int sum = val1 + val2 + carry;
            carry = sum / 10;
            ListNode *pNode = new ListNode(sum%10);
            pcur->next = pNode;
            pcur = pNode;

            if(l1 != nullptr) l1 = l1->next;
            if(l2 != nullptr) l2 = l2->next;
        }

        if(carry != 0){
            ListNode *pNode = new ListNode(carry);
            pcur->next = pNode;
        }

        return head.next; 
    }
}
