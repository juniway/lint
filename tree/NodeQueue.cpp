#include<iostream>
using namespace std;

template<class T>
struct Node{

    //Node() = default;
    Node() : val(T()), next(nullptr){
        cout<<"default Constructor.\n"<<endl;
    }
    Node(T data) : val(data), next(nullptr){
        cout<<"Node Constructor.\n"<<endl;
    }
    //~Node() = default();
    T val;
    Node<T>* next;
};

template<class T>
struct NodeQueue{
    Node<T>* first, *last;

    NodeQueue():first(nullptr), last(nullptr){}
    ~NodeQueue(){}

    void enqueue(Node<T>* node){
        if(first == nullptr){
            first = node;
            last = first;
        }else{
            last->next = node;
            last = node;
        }
    }

    Node<T>* dequeue(){
        if(first == nullptr) return nullptr;
        Node<T>* tmp = new Node<T>(first);
        first = first->next;
        if(last == first){
            last = first;
        }
        return tmp;
    }

    void printQueue(){
        cout<<"======Print Queue======"<<endl;
        auto tmp = first;
        while(tmp){
            cout<<tmp->val<<endl;
            tmp = tmp->next;
        }
        cout<<"======End Print======"<<endl;

    }

};


int main(){

    Node<int>* nd = new Node<int>[5];
    NodeQueue<int> nq;
    for(int i = 0; i < 5; ++i){
        nq.enqueue(nd+i);
    }
    nq.printQueue();

    system("pause");
}