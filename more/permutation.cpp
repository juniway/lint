// permutation.cpp

// 1.
void permute(string& str, int index, vector<string>& result){
	if(index == str.size()){
		v.push_back(str);
		return;
	}
	for(int i = index; str[i] != ""; ++i){
		swap(str[i], str[index]);
		permute(str, index + 1, v);
		swap(str[i], str[index]);
	}
}

// 2.
void permute(string select, string remain){
	if(remain == ""){
		cout << select << endl;
		return;
	}
	for(int i = 0; remain[i] != ""; ++i){
		string wk(remain);
		permute(select + remain[i], wk.erase(i, 1));
	}
}

全排序
全排列是将一组数按一定顺序进行排列，如果这组数有n个，那么全排列数为n!个。现以{1, 2, 3, 4, 5}为
例说明如何编写全排列的递归算法。

1、首先看最后两个数4, 5。 它们的全排列为4 5和5 4, 即以4开头的5的全排列和以5开头的4的全排列。
由于一个数的全排列就是其本身，从而得到以上结果。
2、再看后三个数3, 4, 5。它们的全排列为3 4 5、3 5 4、 4 3 5、 4 5 3、 5 3 4、 5 4 3 六组数。
即以3开头的和4,5的全排列的组合、以4开头的和3,5的全排列的组合和以5开头的和3,4的全排列的组合.
从而可以推断，设一组数p = {r1, r2, r3, ... ,rn}, 全排列为perm(p)，pn = p - {rn}。
因此perm(p) = r1perm(p1), r2perm(p2), r3perm(p3), ... , rnperm(pn)。当n = 1时perm(p} = r1。
为了更容易理解，将整组数中的所有的数分别与第一个数交换，这样就总是在处理后n-1个数的全排列。

设R={r1,r2,...,rn}是要进行排列的n个元素，Ri = R-{ri}. 集合 X 中元素的全排列记为Perm(X)。(ri)Perm(X)表示在全排列Perm(X)的每一个排列上加前缀ri得到的排列。R的全排列可归纳定义如下：
当 n = 1 时， Perm(R) = (r),其中r 是集合R中唯一的元素；
当 n >1 时， Perm(R)有 (r1)Perm(R1),(r2)Perm(R2),.......,(rn)Perm(Rn)构成
依此递归定义，可设计产生Perm(R)的递归算法如下：

template <class T>
void Perm(T list[], int k, int m){
    if(k == m){
        for(int i = 0; i <= m; i++)
            cout << list[i];
        cout << endl;
    }
    else{
        for(int i = k; i <= m; i++){
			Swap(list[k], list[i]);
			Perm(list, k + 1, m) ;
			Swap(list[k], list[i]);
		}
    }
}

template<class T >
inline void Swap(T &a,T & b){
	Type temp = a; a = b; b = temp;
}

 n个数的全排列问题相对简单，可以通过交换位置按序枚举来实现。STL提供了求某个序列下一个排列的算法next_permutation，其算法原理如下：
1. 从当前序列最尾端开始往前寻找两个相邻元素，令前面一个元素为*i，后一个元素为*ii，且满足*i<*ii；
2. 再次从当前序列末端开始向前扫描，找出第一个大于*i的元素，令为*j（j可能等于ii），将i，j元素对调；
3. 将ii之后（含ii）的所有元素颠倒次序，这样所得的排列即为当前序列的下一个排列。
其实现代码如下：
template <class BidirectionalIterator>
bool next_permutation(BidirectionalIterator first, BidirectionalIterator last)
{
	if (first == last) return false;   // 空範圍
	BidirectionalIterator i = first;
	++i;
	if (i == last) return false;       // 只有一個元素
	i = last;                          // i 指向尾端
	--i;
	for(;;){
		BidirectionalIterator ii = i;
		--i;
		// 以上，鎖定一組（兩個）相鄰元素
		if (*i<*ii){                    // 如果前一個元素小於後一個元素
			BidirectionalIterator j = last;  // 令 j指向尾端
			while (!(*i<*--j));            // 由尾端往前找，直到遇上比 *i 大的元素
			iter_swap(i, j);                 // 交換 i, j
			reverse(ii, last);               // 將 ii 之後的元素全部逆向重排
			return true;
		}
		if (i == first){                   // 進行至最前面了
			reverse(first, last);            // 全部逆向重排
			return false;
		}
	}
}

下面程序演示了利用next_permutation来求取某个序列全排列的方法：
int main()
{
 int ia[] = {1,2,3,4};
 vector<int> iv(ia,ia+sizeof(ia)/sizeof(int));

 copy(iv.begin(),iv.end(),ostream_iterator<int>(cout," "));
 cout << endl;
 while(next_permutation(iv.begin(),iv.end()))
 {
  copy(iv.begin(),iv.end(),ostream_iterator<int>(cout," "));
  cout << endl;
 }

 return 0;
}
注意：上面程序中初始序列是按数值的从小到大的顺序排列的，如果初始序列无序的话，
上面程序只能求出从当前序列开始的后续部分排列，
也就是说next_permutation求出的排列是按排列从小到大的顺序进行的。

// 非递归全排列算法
// http://permute.tchs.info/01example.php
// NOTICE:  Copyright 1991-2010, Phillip Paul Fuchs

#define N    12   // number of elements to permute.  Let N > 2

void QuickPerm()
{
   unsigned int a[N], p[N+1];
   register unsigned int i, j, tmp; // Upper Index i; Lower Index j

   for(i = 0; i < N; i++)   // initialize arrays; a[N] can be any type
   {
      a[i] = i + 1;   // a[i] value is not revealed and can be arbitrary
      p[i] = i;
   }
   p[N] = N; // p[N] > 0 controls iteration and the index boundary for i
   //display(a, 0, 0);   // remove comment to display array a[]
   i = 1;   // setup first swap points to be 1 and 0 respectively (i & j)
   while(i < N)
   {
      p[i]--;             // decrease index "weight" for i by one
      j = i % 2 * p[i];   // IF i is odd then j = p[i] otherwise j = 0
      tmp = a[j];         // swap(a[j], a[i])
      a[j] = a[i];
      a[i] = tmp;
      //display(a, j, i); // remove comment to display target array a[]
      i = 1;              // reset index i to 1 (assumed)
      while (!p[i])       // while (p[i] == 0)
      {
         p[i] = i;        // reset p[i] zero value
         i++;             // set new index value for i (increase by one)
      } // while(!p[i])
   } // while(i < N)
} // QuickPerm()

void display(unsigned int *a, unsigned int j, unsigned int i)
{
   for(unsigned int x = 0; x < N; x++)
      printf("%d ",a[x]);
   printf("swapped(%d, %d)\n", j, i);
   getch();  // press any key to continue...
} // display()