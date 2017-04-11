#include<iostream>
#include<vector>
#include<list>
#include<complex>

using namespace std;
/*
template<typename T>
T* begin(Vector<T>& a{
    return &a[0];
}

template<typename T>
T* end(Vector<T> a){
	return a.begin()+a.size();
}

void f2(const Vector<string>& vs){
	for(auto& s: vs)
		cout<<s<<'\n';
}
*/
// Write a function that calculates the sum of the element values of any container like this:
template<typename Container, typename Value>
Value sum(const Container&c, Value v){
	for(auto x: c)
		v+=x;
	return v;
}

// the Value argument nd the function argument v are there to allow the caller to specify the type and initial value of the accumulator

void user(const vector<int>& vi, std::list<double> ld, std::vector<complex<double>>& vc){
	int x = sum(vi, 0); cout<<x<<endl;
	double y = sum(ld, 0.0); cout<<y<<endl;
	auto z = sum(vc, complex<double>{}); cout<<z<<endl;
}

int main(){
	vector<int> vi{1, 1, 1, 1, 1, 1}; // size 6
	list<double> ld{2.0, 2.0, 2.0, 2.0, 2.0, 2.0}; // size 6
	vector<complex<double>> vc{{1.0, 0}, {1.0, 0}, {1.0, 0}}; // size 3
	user(vi, ld, vc);
	
	return 0;
}


template<typename T>
class Less_than{
public:
	Less_than(const T& v):val(v){}
	bool operator(const T& x) const{return x<val;}
private:
	const T val;
}

// a predicate is something that we can invoke to return true or false, for example:

// the ability oto carry data plus their efficiency make function objects particularly useful as arguments to algorithms

/* we have to define Less_than separately from its use. That could be seen as inconvenient.
   Consequently, there is a notation for implicitly generating function objects:
   
   count<<"number of values less than" << x<<":"<< count(vec, [&](int a){return a<x;});
	
 */
 
 // the notation [&](int a){ return a<x; }} is a lambda expression.
 
 
void f(const vector<int>& vec, const list<string>& lst, int x, const string& s){
	cout<<"number of values that less than"<<x<<":"<<count(vec, Less_than<int>{x})<<endl;
	coutn<<"number of values that less than"<<s<<":"<<count<lst, Less_than<string>{s})<<endl;
}

template<typename C, typename P>
int count(const C& c, P pred){
	int cnt=0;
	for(const auto& x:c)
		if(pred(x))
			++cnt;
	return cnt;
}


