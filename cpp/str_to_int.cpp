#include<iostream>
#include<string>
#include<sstream>

int main(){
	using namespace std;
	/*
	string str("001");
	int num;
	int a=122, b=3334, c=89;
	string s1("Hello"), s2("God"), s3, s4;
	int a1, b1, c1;
	string str1, str2;
	stringstream ss, ss1;
	ss<<str;
	ss>>num;
	cout<<num<<endl;
	ss1<<a<<" "<<s1<<" "<<b<<" "<<s2<<" "<<c;	// int, string to stream
	
	//ss1>>a1;cout<<"a1="<<a1;
	//ss1>>str1;cout<<",str1="<<str1<<endl;
	ss1>>a1>>str1>>b1>>str2>>c1;			// stream to int, string
	cout<<"a1="<<a1<<",b1="<<b1<<",c1="<<c1<<",str1="<<str1<<",str2="<<str2<<endl;

	s3 = ss1.str();
	cout<<"s3="<<s3<<endl;
	getline(ss1, s4);
	cout<<"s4="<<s4<<endl;
	*/
	stringstream sss, sss1;
	string st="I love you", st1="";
	
	string e1, e2, e3;

	sss<<st;
	cout<<sss.str()<<endl;
	sss>>e1>>e2>>e3;
	cout<<"e1="<<e1<<",e2="<<e2<<",e3="<<e3<<endl;
	return 0;
}
