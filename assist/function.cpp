#include<iostream>
#include<vector>

using namespace std;


int* getinfo(vector<int>& vt){
	int* temp = new int[vt.size()];
	for(int i=0; i<vt.size(); ++i)
		temp[i]=vt[i];
	return temp;
}

int main(){
	vector<int> v;
	v.push_back(5); cout<<*(v.begin())<<endl;
	v.push_back(9);
	v.push_back(12);
	v.push_back(3);
	
	int *a = new int[v.size()];
	a=getinfo(v);
	for(int i=0; i<4; ++i){
		cout<<a[i]<<" ";
	}
	cout<<endl;
	for(int i=0; i<4; ++i){
		cout<<v[i]<<" ";
	}
	cout<<endl;
	delete[] a;
	
	return 0;
}