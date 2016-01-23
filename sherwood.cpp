// http://www.cnblogs.com/tanky_woo/archive/2010/12/12/1903651.html
// http://m.blog.csdn.net/blog/u010786109/41483445
template <typename Type>
void Shuffle (Type a[], int len)
{
    // 随机洗牌算法
    static RandomNumber rnd;
    for (int i = 0; i < len; ++i) 
    {
        int j = rnd.Random(len-i) + i;
        Swap (a[i], a[j]) ;    
    }
}