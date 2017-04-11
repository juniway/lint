/* 
 * Stack_Implementation_use_struct.cpp
 */

typedef struct {
	float v[20];
	int top;
} Stack;

Stack *init(void){
	Stack *r = malloc(sizeof(Stack));
	r->top = 0;
	return r;
}

void push(Stack *S, float val){
	S->v[(S->top)++] =  val;
}

float pop(Stack *S){
	return (S->v[--(S->top)]);
}
int empty(Stack *S){
	return (S->top <= 0);
}

// Using the Stack data structure in C programs
Stack *S;
S = init();
push(S, 2.31);
push(S, 1.19);
printf("%g\n", pop(S));

push(S, 6.7);
push(S, pop(S) + pop(S)); // replace top 2 elements by their sum

void MyStackPrint(Stack *A){
	if(A->top == 0) printf("empty!");
	else{
		int i;
		for(i=0; i<A->top; ++i)
			printf("%g ", A->v[i]);
	}
}

static int DStack_init = 0;
typedef struct{
	float *vals;
	int size, top;
}DStack;

int DStack_init(DStack *S, int size){
	if(DStack_init)
		return 0;
	else DStack_init = 1;
	S->top = 0;
	S->size = size;
	S->vals = (float *) malloc(size*sizeof(float));
	return (S->vals != 0);
}

int DStack_push(DStack *S, float val){
	if(!DStack_init || S->top > S->size)
		return -1;
	else{
		S->vals[(S->top)++] = val;
		return 0;
	}
}

float DStack_pop(DStack *S){
	return (!DStack_init || S->top <=0 ? 0.0 : S->vals[--(S->top)]);
}

typedef struct {
	TYPE *vals;
	int size, top;
}GDStack;				// generic dynamic stack

int GDStack_push(GDStack *S, TYPE val){...}

// put all source into file GDStack.h
// in application code, do:
#define TYPE float
#include "GDStack.h"
GDStack S;

#define TYPE int

#include "GDStack.h"
GDStack S2;

typedef struct {
	TYPE *vals;
	int size, top;
} GDStack_TYPE;

int GDStack_TYPE_push(GDStack_TYPE *S, TYPE val){...}

//How to use: put all source into base files GDStack.h and GDStack.c
// use editor's global search & replace to convert "TYPE" into "float" or "int"
// and store in new files GDStack_float.* and GDStack_int.*

// in application code, do:
#include<"GDStack_float.h">
#include<"GDStack_int.h">
GDStack_float S1;
GDStack_int S2;
GDStack_String T;

// above solution works, but extremely ugly and still has problems...

// Data structure abstraction
// Data Encapsulation
// Inheritance

// Object

/*********************************************************************
 How will C++ help sove the above Stack problems?
*********************************************************************/

/* 
 * ifstream	--- Read-Only files
 * ofstream --- Write-Only files
 * fstream  --- Read/Write files
 */ 

 ifstream foofile("foo"); // open existing file "foo" Read-Only
 ofstream foofile("foo"); // create new file "foo" for writing

 if(!foofile)	cerr << "unable to open file 'foo'" << endl;

#include<fstream>
#include<cstdlib>

int main(int, char **){
	char filename[512];
	int birth = 1642;
	char *name = "Issac Newton";

	cout<<"file name is:";
	if(!(cin>>filename))
		return -1;
	ofstream out(filename); // open filename for writing
	if(!out){
		cerr<<"uable to open output file "
			<< filename << endl;
			return -1;
	}
	out << name << "was born in" << birth <<endl;
	return 0;
}

template <typename T, std::size_t N>
class Stack{
public:
	Stack();
	void push(T value);
	void pop();
	T top() const;
	std::size_t count() const;
private:
	std::array<T, N> baseArray;
	std::array<T>::iterator iter;
};

template <typename T, std::size_t N>
Stack::Stack():baseArray(), iter(baseArray.end()){}

template <typename T, std::size_t N>
void Stack::push(T value){
	if(iter == baseArray.begin())
		throw std::exception();
	--iter;
	*iter = value;
}

template <typename T, std::size_t N>
void Stack::pop(){
	if(iter == baseArray.end())
		throw std::exception;
	++iter;
}

template <typename T, std::size_t N>
T Stack::top(){
	if(iter == baseArray.end())
		throw std::exception();
	return *iter;
}

template <typename T, std::size_t N>
std::size_t Stack::count() const{
	return baseArray.end() - iter;
}
/*
An std::array doesn't seem like a good backend for a stack, 
because its size must be known at compile time (meaning that 
you can either only handle small stacks or allocate a lot of 
potentially wasted memory). std::vector seems like a better 
choice, but if that can't be used (because the assignment says 
so etc.) you'll have to go back to int[] arrays. 
(Or use a dynamic number of fixed size std::arrays that you keep 
in a linked list.

Well, stacks are traditionally implemented in fixed sized containers, 
populated from back to front. Maybe a deque would be a best choice.
*/


