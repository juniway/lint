vector的初始化大小和赋初值 
(1)vector< 类型 > 标识符 ;
(2)vector< 类型 > 标识符(最大容量) ；
(3)vector< 类型 > 标识符（最大容量，初始所有值）；

vector< int > arry(5, 1);

注：定义一个大小为5的数组，并将每个值都赋为1；
for( int i = 0; i < 5; i ++ )
	cout << arry[i] << " ";

输出结果为：1 1 1 1 1


同理定义其他类型的：
vector<char> arry(3, '*');

定义二维的vector:
vector< vector <int>> Arry（10， vector<int>(0)）;

使用数组对C++ Vector进行初始化
int i[10] ={1,2,3,4,5,6,7,78,8} ;  

///第一种   
vector<int> vi(i+1,i+3); ///从第2个元素到第三个元素  
for(vector <int>::interator it = vi.begin() ; it != vi.end() ; it++){  
	cout << *it <<" " ;
} 


vector 的数据的存入和输出：
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
using namespace std;

int main(void){
   vector<int> num;   // STL中的vector容器
   int element;

   // 从标准输入设备读入整数，
   // 直到输入的是非整型数据为止

   while (cin >> element)     //ctrl+Z 结束输入 
      num.push_back(element);

   // STL中的排序算法
   sort(vi.begin() , vi.end()); /// 从小到大  
   reverse(vi.begin(),vi.end()) /// 从大道小 

   // 将排序结果输出到标准输出设备
   for (int i = 0; i < num.size(); i ++)
      cout << num[i] << "\n";
   //也可以这样做

   system("pause");
   return 0;
}

 对于二维vector的定义。

1)定义一个10个vector元素，并对每个vector符值1-10。

#include<stdio.h>
#include<vector>
#include <iostream>

using namespace std;

int main(){
	int i = 0, j = 0;

//定义一个二维的动态数组，有10行，每一行是一个用一个vector存储这一行的数据。

所 以每一行的长度是可以变化的。之所以用到vector<int>(0)是对vector初始化，否则不能对vector存入元素。
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


定义一个行列都是变化的数组。

#include<stdio.h>
#include<vector>
#include <iostream>

using namespace std;

void main(){
	int i = 0, j = 0;

	vector< vector<int> > Array;
	vector< int > line;
	for(j = 0; j < 10; j++){
		Array.push_back(line);//要对每一个vector初始化，否则不能存入元素。
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

使用 vettor erase 指定元素

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
