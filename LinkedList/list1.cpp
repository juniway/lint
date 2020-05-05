#include <iostream>
#include <vector>

using namespace std;

struct Node {
    int data;
    Node *next;
    Node() {}
    Node(int v) : data(v) {}
};

class List {
public:
    Node *head;
    int len;
	List(Node *root):head(root) {}

	void PrintList();
	void Reverse();
	Node* Middle();
    bool IsLoop();
    bool IsLoop1();
};

// create a list with random nodes: from rightmost to leftmost
List* CreateList(int len) {
    srand(time(NULL));
    Node *p = nullptr, *pre = nullptr;
    for (int i = 0; i < len; i++) {
        p = new Node();
        p->data = rand() % 100 + 1; //随机数
        p->next = pre;
        pre = p;
    }

	if (p == nullptr) return nullptr;

	List *l = new List(p);
	l->len = len;

	return l;
}

void List::PrintList() {
    Node *h = this->head;
    for(int i = 0; i < this->len; ++i) {
        cout << h->data << "->";
        h = h->next;
    }

    cout << "null" << endl;
}

void List::Reverse() {
    Node *pre = nullptr, *p = this->head;

    while (p && p->next) {
        Node *tmp = p->next;
        p->next = pre;
        pre = p;
        p = tmp;
    }
    this->head = p;
    p->next = pre;
}

Node* List::Middle() {
	Node *first, *second;
	first = second = this->head;
	while(first != nullptr && second != nullptr && second->next != nullptr) {
		first = first->next;
		second = second->next->next;	
	}

	return first;
}

// (1) Floyd cycle finding algorithm
// Aka the tortoise and hare algorithm
bool List::IsLoop() {
    Node *slow, *fast;
    slow = fast = this->head;

    while(slow && fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;

        if(slow == fast)
            return true;
    }

    return false;
}

List* CreateLoopList() {
    Node *p1 = new Node(3);
    p1->next = nullptr;

    Node *p2 = new Node(4);
    p2->next = p1;

    Node *p3 = new Node(5);
    p3->next = p2;

    Node *p4 = new Node(6);
    p4->next = p3;

    Node *p5 = new Node(6);
    p5->next = p4;

    Node *p6 = new Node(7);
    p6->next = p5;

    p1->next = p4;

    List *l = new List(p6);
    l->len = 6;
    return l;
}

List* CreateLoopList1(int len) {
    srand(time(NULL));
    Node *p = nullptr, *pre = nullptr;

    Node *tail = nullptr;
    int pos = rand()%len;
    for (int i = 0; i < len; i++) {
        p = new Node();
        p->data = rand() % 100 + 1; //随机数
        p->next = pre;
        if(pre == nullptr) tail = p;
        pre = p;

        if (i == pos) tail->next = p;
    }

	if (p == nullptr) return nullptr;


	List *l = new List(p);
	l->len = len;

	return l;
}
// (2) Better than Floyd's algorithm
// https://stackoverflow.com/questions/2663115/how-to-detect-a-loop-in-a-linked-list
bool List::IsLoop1(){
    if(this->head == nullptr) return false;

    Node *slow, *fast;
    slow = fast = this->head;

    int taken = 0, limit = 2;
    while (fast->next != nullptr) {
        fast = fast->next;
        taken++;
        if(slow == fast) return true;

        if(taken == limit){
            taken = 0;
            limit <<= 1;    // equivalent to limit *= 2;
            slow = fast;    // teleporting the turtle (to the hare's position) 
        }
    }
    return false;
}

vector<List*> genMultiList(int cnt) {
    vector<List*> vl;
    srand(time(NULL));
    for (int i = 0; i < cnt; ++i) {
        vl.push_back(CreateList(rand()%10+1));
    }
    return vl;
}

int main() {
	List *l = CreateList(4);
	l->PrintList();
	l->Reverse();
	l->PrintList();
	Node *mid = l->Middle();
	cout << "middle: " << mid->data << endl;

    cout << "==========================================" << endl;
    cout << endl;
    vector<List*> vl = genMultiList(5);
    for (auto &i:vl) {
        i->PrintList();
        cout << "mid: " << i->Middle()->data << endl;
    }

    cout << "==========================================" << endl;

    List *ll = CreateLoopList();
    ll->PrintList();
    cout << "loop: " << ll->IsLoop() << endl;

    List *ll2 = CreateLoopList1(5);
    ll2->PrintList();
    cout << "loop: " << ll2->IsLoop() << endl;

    l->PrintList();
    cout << "loop: " << l->IsLoop() << endl;
}
