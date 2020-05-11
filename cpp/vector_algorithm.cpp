#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>
using namespace std;

void main()
{
int iarray[]={0,1,2,3,4,5,6,6,6,7,8};
vector<int> ivector(iarray,iarray+sizeof(iarray)/sizeof(int));
int iarray1[]={6,6};
vector<int> ivector1(iarray1,iarray1+sizeof(iarray1)/sizeof(int));
int iarray2[]={5,6};
vector<int> ivector2(iarray2,iarray2+sizeof(iarray2)/sizeof(int));
int iarray3[]={0,1,2,3,4,5,7,7,7,9,7};
vector<int> ivector3(iarray3,iarray3+sizeof(iarray3)/sizeof(int));

//找出ivector之中相邻元素值相等的第一个元素
cout<<*adjacent_find(ivector.begin(),ivector.end())<<endl;

//找出ivector之中元素值为6的元素个数
cout<<count(ivector.begin(),ivector.end(),6)<<endl;

//找出ivector之中小于7的元素个数
cout<<count_if(ivector.begin(),ivector.end(),bind2nd(less<int>(),7))<<endl;

//找出ivector之中元素值为4的第一个元素所在位置的元素
cout<<*find(ivector.begin(),ivector.end(),4)<<endl;

//找出ivector之中大于2的第一个元素所在位置的元素
cout<<*find_if(ivector.begin(),ivector.end(),bind2nd(greater<int>(),2))
<<endl;

//找出ivector之中子序列ivector1所出现的最后一个位置，再往后3个位置的元素
cout<<*(find_end(ivector.begin(),ivector.end(),ivector1.begin(),
ivector1.end())+3)<<endl;

//找出ivector之中子序列ivector1所出现的第一个位置，再往后3个位置的元素
cout<<*(find_first_of(ivector.begin(),ivector.end(),ivector1.begin(),
ivector1.end())+3)<<endl;

//子序列ivector2在ivector中出现的起点位置元素
cout<<*search(ivector.begin(),ivector.end(),ivector2.begin(),ivector2.end())
<<endl;

//查找连续出现3个6的起点位置元素
cout<<*search_n(ivector.begin(),ivector.end(),3,6,equal_to<int>())<<endl;

//判断两个区间ivector和ivector3相等否(0为假，1为真）
cout << equal(ivector.begin(), ivector.end(), ivector3.begin()) << endl;

//查找区间ivector3在ivector中不匹配点的位置
pair<int*,int*>result=mismatch(ivector.begin(),ivector.end(),ivector3.begin());
cout<< result.first - ivector.begin() << endl;
}

#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>
using namespace std;

class even_by_two{             //类定义形式的函数对象
public:
int operator()() const
{return _x+=2;}
private:
static int _x;
};
int even_by_two::_x=0;       //静态数据成员初始化

void main()
{
int iarray[]={0,1,2,3,4,5,6,6,6,7,8};
int iarray1[]={0,1,2,3,4,4,5,5,6,6,6,6,6,7,8};
vector<int> ivector(iarray,iarray+sizeof(iarray)/sizeof(int));
vector<int> ivector1(iarray+6,iarray+8);
vector<int> ivector2(iarray1,iarray1+sizeof(iarray1)/sizeof(int));
ostream_iterator< int > output( cout, " " ); //定义流迭代器用于输出数据

//迭代遍历ivector1区间，对每一个元素进行even_by_two操作
    generate(ivector1.begin(),ivector1.end(),even_by_two());
copy(ivector1.begin(),ivector1.end(),output);
cout<<endl;

//迭代遍历ivector的指定区间（起点和长度），对每一个元素进行even_by_two操作
    generate_n(ivector.begin(),3,even_by_two());
copy(ivector.begin(),ivector.end(),output);
cout<<endl;

//删除元素6
    remove(ivector.begin(),ivector.end(),6);
copy(ivector.begin(),ivector.end(),output);
cout<<endl;

//删除(实际并未从原序列中删除）元素6，结果置于另一个区间
    vector<int> ivector3(12);
remove_copy(ivector.begin(),ivector.end(),ivector3.begin(),6);
copy(ivector3.begin(),ivector3.end(),output);
cout<<endl;

//删除(实际并未从原序列中删除）小于6的元素
remove_if(ivector.begin(),ivector.end(),bind2nd(less<int>(),6));
copy(ivector.begin(),ivector.end(),output);
cout<<endl;

//删除(实际并未从原序列中删除)小于7的元素，结果置于另一个区间，
remove_copy_if(ivector.begin(),ivector.end(),ivector3.begin(),
bind2nd(less<int>(),7));
copy(ivector3.begin(),ivector3.end(),output);
cout<<endl;

//将所有的元素值6，改为元素值3
replace(ivector.begin(),ivector.end(),6,3);
copy(ivector.begin(),ivector.end(),output);
cout<<endl;

//将所有的元素值3，改为元素值5,结果放置到另一个区间
replace_copy(ivector.begin(),ivector.end(),ivector3.begin(),3,5);
copy(ivector3.begin(),ivector3.end(),output);
cout<<endl;

//将所有小于5的元素值，改为元素值2
replace_if(ivector.begin(),ivector.end(),bind2nd(less<int>(),5),2);
copy(ivector.begin(),ivector.end(),output);
cout<<endl;

//将所有的元素值8，改为元素值9,结果放置到另一个区间
replace_copy_if(ivector.begin(),ivector.end(),ivector3.begin(),
bind2nd(equal_to<int>(),8),9);
copy(ivector3.begin(),ivector3.end(),output);
cout<<endl;

//逆向重排每一个元素
reverse(ivector.begin(),ivector.end());
copy(ivector.begin(),ivector.end(),output);
cout<<endl;

//逆向重排每一个元素,结果置于另一个区间
reverse_copy(ivector.begin(),ivector.end(),ivector3.begin());
copy(ivector3.begin(),ivector3.end(),output);
cout<<endl;

//旋转（互换元素）[first,middle), 和[middle,end)
rotate(ivector.begin(),ivector.begin()+4,ivector.end());
copy(ivector.begin(),ivector.end(),output);
cout<<endl;

//旋转（互换元素）[first,middle], 和[middle,end]，结果置于另一个区间，
rotate_copy(ivector.begin(),ivector.begin()+5,ivector.end(),
ivector3.begin());
copy(ivector3.begin(),ivector3.end(),output);
cout<<endl;
}

#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>
using namespace std;

void main()
{
int iarray[]={26,17,15,22,23,33,32,40};
vector<int> ivector(iarray,iarray+sizeof(iarray)/sizeof(int));

// 查找并输出最大、最小值元素
cout<<*max_element(ivector.begin(),ivector.end())<<endl;
cout<<*min_element(ivector.begin(),ivector.end())<<endl;

//将ivector.begin()+4-ivector.begin()各元素排序，
//放进[ivector.begin(),ivector.begin()+4]区间。剩余元素不保证维持原来相对次序
partial_sort(ivector.begin(),ivector.begin()+3,ivector.end());
copy(ivector.begin(),ivector.end(),ostream_iterator<int>(cout," "));
cout<<endl;

//局部排序并复制到别处
vector<int> ivector1(5);
partial_sort_copy(ivector.begin(),ivector.end(),ivector1.begin(),
ivector1.end());
copy(ivector1.begin(),ivector1.end(),ostream_iterator<int>(cout," "));
cout<<endl;

//排序，缺省为递增。
sort(ivector.begin(),ivector.end());
copy(ivector.begin(),ivector.end(),ostream_iterator<int>(cout," "));
cout<<endl;

//将指定元素插入到区间内不影响区间原来排序的最低、最高位置
cout<<*lower_bound(ivector.begin(),ivector.end(),24)<<endl;
cout<<*upper_bound(ivector.begin(),ivector.end(),24)<<endl;

//对于有序区间，可以用二分查找方法寻找某个元素
    cout<<binary_search(ivector.begin(),ivector.end(),33)<<endl;
    cout<<binary_search(ivector.begin(),ivector.end(),34)<<endl;

//下一个排列组合
next_permutation(ivector.begin(),ivector.end());
copy(ivector.begin(),ivector.end(),ostream_iterator<int>(cout," "));
cout<<endl;

//上一个排列组合
prev_permutation(ivector.begin(),ivector.end());
copy(ivector.begin(),ivector.end(),ostream_iterator<int>(cout," "));
cout<<endl;

//合并两个序列ivector和ivector1，并将结果放到ivector2中
vector<int> ivector2(13);
merge(ivector.begin(),ivector.end(),ivector1.begin(),ivector1.end(),
ivector2.begin());
copy(ivector2.begin(),ivector2.end(),ostream_iterator<int>(cout," "));
cout<<endl;

//将小于*(ivector.begin()+5)的元素放置在该元素之左
//其余置于该元素之右。不保证维持原有的相对位置
nth_element(ivector2.begin(),ivector2.begin()+5,ivector2.end());
copy(ivector2.begin(),ivector2.end(),ostream_iterator<int>(cout," "));
cout<<endl;

//排序，并保持原来相对位置
stable_sort(ivector2.begin(),ivector2.end());
copy(ivector2.begin(),ivector2.end(),ostream_iterator<int>(cout," "));
cout<<endl;

//针对一个有序区间，找出其中一个子区间，其中每个元素都与某特定元素值相同
pair<vector<int>::iterator,vector<int>::iterator> pairIte;
pairIte=equal_range(ivector2.begin(),ivector2.end(),22);
cout<<*(pairIte.first)<<endl;
cout<<*(pairIte.second)<<endl;

//合并两个有序序列，然后就地替换
int iarray3[] = { 1, 3, 5, 7, 2, 4, 6, 8 };
vector<int> ivector3(iarray3,iarray3+sizeof(iarray3)/sizeof(int));
inplace_merge(ivector3.begin(), ivector3.begin()+ 4, ivector3.end());
copy(ivector3.begin(),ivector3.end(), ostream_iterator<int>(cout, " "));
cout<<endl;

//以字典顺序比较序列ivector3和ivector4
int iarray4[] = { 1, 3, 5, 7,1, 5, 9, 3 };
vector<int> ivector4(iarray4,iarray4+sizeof(iarray4)/sizeof(int));
cout<< lexicographical_compare(ivector3.begin(),ivector3.end(),
ivector4.begin(),ivector4.end()) << endl

}