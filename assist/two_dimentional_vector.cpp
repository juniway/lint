vector�ĳ�ʼ����С�͸���ֵ 
(1)vector< ���� > ��ʶ�� ;
(2)vector< ���� > ��ʶ��(�������) ��
(3)vector< ���� > ��ʶ���������������ʼ����ֵ����

vector< int > arry(5, 1);

ע������һ����СΪ5�����飬����ÿ��ֵ����Ϊ1��
for( int i = 0; i < 5; i ++ )
	cout << arry[i] << " ";

������Ϊ��1 1 1 1 1


ͬ�����������͵ģ�
vector<char> arry(3, '*');

�����ά��vector:
vector< vector <int>> Arry��10�� vector<int>(0)��;

ʹ�������C++ Vector���г�ʼ��
int i[10] ={1,2,3,4,5,6,7,78,8} ;  

///��һ��   
vector<int> vi(i+1,i+3); ///�ӵ�2��Ԫ�ص�������Ԫ��  
for(vector <int>::interator it = vi.begin() ; it != vi.end() ; it++){  
	cout << *it <<" " ;
} 


vector �����ݵĴ���������
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
using namespace std;

int main(void){
   vector<int> num;   // STL�е�vector����
   int element;

   // �ӱ�׼�����豸����������
   // ֱ��������Ƿ���������Ϊֹ

   while (cin >> element)     //ctrl+Z �������� 
      num.push_back(element);

   // STL�е������㷨
   sort(vi.begin() , vi.end()); /// ��С����  
   reverse(vi.begin(),vi.end()) /// �Ӵ��С 

   // ���������������׼����豸
   for (int i = 0; i < num.size(); i ++)
      cout << num[i] << "\n";
   //Ҳ����������

   system("pause");
   return 0;
}

 ���ڶ�άvector�Ķ��塣

1)����һ��10��vectorԪ�أ�����ÿ��vector��ֵ1-10��

#include<stdio.h>
#include<vector>
#include <iostream>

using namespace std;

int main(){
	int i = 0, j = 0;

//����һ����ά�Ķ�̬���飬��10�У�ÿһ����һ����һ��vector�洢��һ�е����ݡ�

�� ��ÿһ�еĳ����ǿ��Ա仯�ġ�֮�����õ�vector<int>(0)�Ƕ�vector��ʼ���������ܶ�vector����Ԫ�ء�
 vector< vector<int> > Array( 10, vector<int>(0) ); 

for( j = 0; j < 10; j++ ){
	for ( i = 0; i < 9; i++ ){
		Array[ j ].push_back( i );

	}
}

for( j = 0; j < 10; j++ ){
	for( i = 0; i < Array[ j ].size(); i++ ){
		cout << Array[ j ][ i ] << "  ";
	}
	cout<< endl;
}


����һ�����ж��Ǳ仯�����顣

#include<stdio.h>
#include<vector>
#include <iostream>

using namespace std;

void main(){
	int i = 0, j = 0;

	vector< vector<int> > Array;
	vector< int > line;
	for(j = 0; j < 10; j++){
		Array.push_back(line);//Ҫ��ÿһ��vector��ʼ���������ܴ���Ԫ�ء�
		for (i = 0; i < 9; i++){
			Array[j].push_back(i);
		}
	}

	for(j = 0; j < 10; j++){
		for(i = 0; i < Array[j].size(); i++){
			cout << Array[j][i] << "  ";
		}
		cout<< endl;
	}
}

ʹ�� vettor erase ָ��Ԫ��

#include "iostream"
#include "vector"

using namespace std;

int   main(){
    vector<int>   arr;
    arr.push_back(6);
    arr.push_back(8);
    arr.push_back(3);
    arr.push_back(8);

    for(vector<int>::iterator it=arr.begin(); it!=arr.end(); ){
        if(* it == 8){
            it = arr.erase(it);
        }
        else{
            ++it;
        }
    }

    cout << "After remove 8:\n";

    for(vector<int>::iterator it = arr.begin(); it < arr.end(); ++it){
        cout << * it << " ";
    }
    cout << endl;
}
//use iterator to traverse two dimentional vector
include <iostream>
#include <vector>
using namespace std;



int main()
{
   vector<vector<char> >vec1;
   char array[]="hello";
   vector<char>vec2(array,array+6);
   vec1.push_back(vec2);
   vector<vector<char> >::iterator ite=vec1.begin();
   cout<<(*ite)[0]<<endl; 
    system("pause");
    return 0;
}


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
	for( ; row_it != row_end; ++row_it){
		vector<int>::iterator col_it = row_it->begin();
		vector<int>::iterator col_end = row_it->end();
		for ( ; col_it != col_end; ++col_it )
			cout<< setw ( 3 ) << *col_it;
		cout<<'\n';
	}
	return 0;
}
