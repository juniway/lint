// http://www.cnblogs.com/c-cloud/p/3224788.html
// http://computing.dcu.ie/~humphrys/Notes/String/kmp.html
// http://www.cnblogs.com/easonliu/p/3660748.html
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void getNext(const char P[], int next[]){
    int m = strlen(P);
    next[0] = 0;

    int k = 0; // 最大前后缀长度
    for(int i = 1; i < m; ++i){ // 从第二个字符开始，依次计算每一个字符对应的next值
        while(k > 0 && P[i] != P[k])
            k = next[k-1];
        if(P[i] == P[k]){
            k++;
        }
        next[i] = k;
    }
}

void computeNext(const char pattern[], int next[]){
    int m = strlen(P);
    int index = 0;
    for(int i = 1; i < m;){
        if(pattern[i] == pattern[index]){
            next[i] = index + 1;
            index++;
            i++;
        }else{
            if(index != 0){
                index = next[index-1];
            }else{
                next[i] = 0;
                i++;
            }
        }
    }
}

// 此种解法中next[i] 表示的是到i这个元素为止(但不包括i)前面已经匹配了的最大长度
// j = -1表示到第i个元素时，前面有0个匹配
// next[0] = -1 表示第0个元素前有-1个匹配，专门表示第一个元素用的
void getNext(vector<int> &next, string &P) {
    int n = (int)P.length();
    int i = 0, j = -1;
    next[i] = j;
    while (i < n) {
        while (j != -1 && P[i] != P[j]) j = next[j];
        ++i, ++j;
        next[i] = j;
    }
}

/*
    上面的是通常用的KMP算法，但是算法是有一定缺陷的。
    比如我们的模式串  pattern =“AAAAB”，其中很容易得到next数组为01230。
    如果目标匹配串为 “AAAACAAAAB” ，大家可以模拟一下，A要回溯多次。
    就是说我们的next数组优化并不彻底。
    优化算法：next[i]表示匹配串在i处如果匹配失败下次移到的位置。
    下面是优化后的的求next数组的代码。
    虽然两种写求得next值不一样，但是kmp函数的写法是一样的。
    此时得出的next数组是{-1, -1, -1, -1, 3}
*/
void getNext(vector<int> &next, string &needle) {
    int i = 0, j = -1;
    next[i] = j;
    while (i < needle.length() - 1) {
        while (j != -1 && needle[i] != needle[j]) j = next[j];
        ++i; ++j;
        //特殊情况，这里即为优化之处。考虑下AAAAB, 防止4个A形成0123在匹配时多次迭代。
        if (needle[i] == needle[j]) next[i] = next[j];
        else next[i] = j;
    }
}


int kmp(const char T[], const char P[]){
    int n = strlen(T);
    int m = strlen(P);
    int *next = malloc(n*sizeof(int));
    int i, j;

    makeNext(P, next);

    for (i = 0, j = 0; i < n; ++i){
        while(j > 0 && P[j] != T[i])
            j = next[j-1];
        if (P[j] == T[i])
            j++;
        if (j == m){
            free(next);
            return i - m + 1;
        }
    }
    free(next);
    return -1;
}

int compute_kmp(const char text[], const char pattern[]){
    int n = strlen(text);
    int m = strlen(pattern);
    int* next = new int[n];
    int i = 0;
    int j = 0;
    while(i < n && j < m){
        if(text[i] == pattern[j]){
            i++;
            j++;
        }else{
            if(j!=0){
                j = next[j-1];
            }else{
                i++;
            }
        }
    }
    if(j == m){
        delete next;
        return i - m + 1;
    }

    delete next;
    return -1;
}

int strStr_kmp(string haystack, string needle) {
    int n = haystack.length(), m = needle.length();

    if (haystack.empty()) return needle.empty() ? 0 : -1;
    if (needle.empty()) return 0;
    vector<int> next(m + 1);
    getNext(next, needle);
    int i = 0, j = 0;
    while (i != n) {
        while (j != -1 && haystack[i] != needle[j]) j = next[j];
        ++i; ++j;
        if (j == needle.length()) return i - j;
    }
    return -1;
}





int main(){

    char str[] = "abc";
    printf("sizeof:%d, strlen:%d\n", sizeof str, strlen(str));

    char T[] = "abcdabcd";
    char P[] = "abc";
    printf("%s\n",T);
    printf("%s\n",P );
    // makeNext(P,next);
    kmp(T, P);
    // for (i = 0; i < strlen(P); ++i)
    //     printf("%d",next[i]);

    printf("\n");

    return 0;
}