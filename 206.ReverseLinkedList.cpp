[LeetCode 206] Reverse a singly linked list.

// 算法1: pre 指针
class Solution {
public:
    ListNode* reverseList(ListNode *head){
	    ListNode *pre = nullptr;
	    while(head != nullptr){ // reverse from node 0
	        ListNode *temp = head->next;
	        head->next = pre;
	        pre = head;
	        head = temp;
	    }
    	return pre;
	}
};

// 算法2: Dummy Head

    cur
    1 ————> 2 ————> 3 ————> 4 ————> 5
    ^
    |
dummyhead
      ------------>
     /     cur     \
    1 <———— 2 <———— 3 ————> 4 ————> 5
            ^
            |
        dummyhead
过程: 把当前节点指向它的下一个的下一个节点，
	  然后把它自己的下一个节点指向当前节点
	  把它下一个节点的下一个节点再指向它的下一个节点
	  把dummyhead指向它的下一个节点

class Solution {
public:
    ListNode* reverseList(ListNode* head){
       if(head == nullptr || head->next == nullptr) return head;
       ListNode dummyhead(0);
       dummyhead.next = head;
       ListNode* cur = head;

       while(cur->next != nullptr){
           ListNode* tmp = cur->next;
           cur->next = tmp->next;
           tmp->next = dummyhead.next;
           dummyhead.next = tmp;
       }

       return dummyhead.next;
    //   return;
    }
};


// iterative
void reverse(Node*& head) {
	if (head == nullptr) return;
	Node* prev = nullptr;
	Node* cur = head;
	while(cur) {
		Node* next = cur->next;
		cur->next = prev;
		prev = curr;
		cur = next;
	}
	head = prev;
}

// recursive
void reverse(Node*& p) {
	if (p != nullptr) return;
	Node* rest = p->next;
	if (!rest) return;
	reverse(rest);
	p->next->next = p;
	p->next = nullptr;
	p = rest;
}