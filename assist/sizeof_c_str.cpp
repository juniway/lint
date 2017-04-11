#include<iostream>
#include<string>
using namespace std;

int main(){
	string ss("aabbcc");
	cout<<sizeof(ss)<<" "<<sizeof(ss.c_str())<<endl;

	return 0;
}