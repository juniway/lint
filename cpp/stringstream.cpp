#include<iostream>
#include<string>
#include<cstring>
#include<sstream>
#include<ctime>
#include<cstdlib>

using namespace std;

int main(){

	char buff[128]="REGISTER 1 2 data";
	int i;
	string a;
	cout<<sizeof(buff)<<" "<<strlen(buff)<<endl;
	
	string b="1234567890";
	cout<<sizeof(b.c_str())<<" "<< strlen(b.c_str())<<endl;

	char * buf = new char[128];
	cout<<sizeof(buf)<<" "<<strlen(buf)<<endl;

	stringstream ss;
	string strdata;
	
	ss<<buff;
	cout<<ss.str()<<endl;
	int loc = ss.str().find(' ', 0);
	loc = ss.str().find(" ", loc+1);
	loc = ss.str().find(" ", loc+1);
	strdata=ss.str().substr(loc+1, ss.str().length()-1);
	cout<<"strdata="<<strdata<<endl;
	ss>>a>>i;
	cout<<"a="<<a<<endl;
	cout<<"i="<<i<<endl;
	cout<<"ss.str()="<<ss.str()<<endl;
	srand(time(NULL));
	int port_of_me = rand()%1000+46000;
	cout<<"port_of_me:"<<port_of_me<<endl;
	return 0;
}
