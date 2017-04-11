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
 cout<<"姓名："<<name<<endl
  <<"年龄："<<age<<endl
  <<"性别："<<sex<<endl
  <<"体重："<<weight<<endl;
 return 0;
}