#include<sstream>
#include<iostream>

using namespace std;

int main( void ){
 stringstream ss;
 string records = "carea 89 M 65.3";
 ss<<records;
 string name;
 int age;
 char sex;
 float weight;
 ss>>name>>age>>sex>>weight;
 cout<<"������"<<name<<endl
  <<"���䣺"<<age<<endl
  <<"�Ա�"<<sex<<endl
  <<"���أ�"<<weight<<endl;
 return 0;
}