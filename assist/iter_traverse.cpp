/*
*  Each row is an independent data structure, so you have no choice but to
*  use two iterators. It's exactly the same as when you build the vector of vectors:
*/

#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;
int main(){
	vector< vector<int> > v;
	for (int i = 0; i < 10; i++){
		v.push_back (vector<int>());
		for (int j = 0; j < 10; j++)
			v[i].push_back (i+j);
	}
	vector< vector<int> >::iterator row_it = v.begin();
	vector< vector<int> >::iterator row_end = v.end();
	for(; row_it != row_end; ++row_it){
		vector<int>::iterator col_it = row_it->begin();
		vector<int>::iterator col_end = row_it->end();
		for (; col_it != col_end; ++col_it )
			cout<< setw (3) << *col_it;
		cout<<endl;
	}
	return 0;
}


