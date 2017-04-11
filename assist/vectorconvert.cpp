#include<vector>
#include<iostream>
#include<cstring>

using namespace std;

template <typename T>
T extract(const vector<int> &v, int pos){ //const vector<unsigned char> &v
	T value;
	memcpy(&value, &v[pos], sizeof(T));
	return value;
}

int main(){
	vector<int> v;  // vector<unsigned char> v;
	//Simulate that we have read a binary file.
	//Add some binary data to v.
	v.push_back(2);
	v.push_back(1);
	//00000001 00000010 == 258
	int ina = v[0];
	int inb = v.front();
	int inc = v.back();
	cout<<"ina="<<ina<<" inb="<<inb<<" inc="<<inc<<endl;
	
	/*
	int a = extract<int>(v,0); //a==258
	cout<<"a="<<a<<endl;
	int b = extract<short>(v,1); //b==258
	cout<<"b="<<b<<endl;
	//add 2 more to simulate extraction of a 4 byte int.
	v.push_back(0);
	v.push_back(0);
	int c = extract<int>(v,0); //c == 258
	cout<<"c="<<c<<endl;
	//Get the last two elements.
	int d = extract<short>(v,2); // d==0
	cout<<"d="<<d<<endl;
	*/
	return 0;
}