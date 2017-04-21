// [BackTracking Problem] Langford pair
// http://www.geeksforgeeks.org/fill-two-instances-numbers-1-n-specific-way/
// http://www.geeksforgeeks.org/tag/backtracking/
/*
In combinatorial mathematics, a Langford pairing, also called a Langford sequence,
is a permutation of the sequence of 2n numbers 1, 1, 2, 2, ..., n, n
in which the two ones are one unit apart, the two twos are two units apart,
and more generally the two copies of each number k are k units apart.
Langford pairings are named after C. Dudley Langford, who posed the problem of constructing them in 1958.

Langford's problem is the task of finding Langford pairings for a given value of n.
*/

// For example, a Langford pairing for n = 3 is given by the sequence 2,3,1,2,1,3.
// there is no Langford pairing when n = 1, 2, or 5.

// A Langford pairing for n = 4.
//  _________4________
// |                  |
// |        _______3__|___
// |       |          |   |
// 4   1   3  1   2   4   3   2
//     |______|   |___________|
//         1            2

/*
n =  1 :          0 solutions (     0 s)
n =  2 :          0 solutions (     0 s)
n =  3 :          2 solutions (     0 s)
n =  4 :          2 solutions (     0 s)
n =  5 :          0 solutions (     0 s)
n =  6 :          0 solutions (     0 s)
n =  7 :         52 solutions (     0 s)
n =  8 :        300 solutions (     0 s)
n =  9 :          0 solutions (     1 s)
n = 10 :          0 solutions (     6 s)
n = 11 :      35584 solutions (    45 s)
n = 12 :     216288 solutions (   390 s)
*/


// 分析：
// 此问题属于回溯法，深度优先搜索

// 试比较回溯法与分枝限界算法，分别谈谈这两个算法比较适合的问题？
// 二者都是在解空间树里搜索问题的可靠解或最优解，但是搜索的方式不同，
// 1). 回溯法采用深度优先的方式，直到达到问题的一个可行解，或经判断,
// 沿此路径不会达到问题的可行解或最优解时，则提前停止向前继续搜索，
// 并沿原路返回到该路径上最后一个还可扩展的节点，然后，从该节点出发朝新的方向纵深搜索。
// 2). 分枝限界法采用的是宽度优先的方式，它将活节点存放在一个特殊的表中，
// 其策略是，在扩展节点处，首先生成其所有的儿子节点，将那些导致不可行解或导致非最优解的
// 儿子节点舍弃，其余儿子节点加入活节点表中，然后，从活节点中取出一个节点作为当前扩展节点，
// 重复上述节点中扩展过程。可以看出，回溯法一般用于求问题的一个可行解，
// 而分枝限界可以用于求出问题的所有可行解。

#include <iostream>
#include <cstdio>
using namespace std;
const static int N = 7;


bool explore(int* sol, int gap, int len);
void explore_all(int* sol, int gap, int len);
bool explore1(int* sol, int gap, int len);

void print(int* sol, int N){
    if(sol == nullptr){
        cout << "Not exist a langford pair.\n";
        return;
    }

    printf("[ ");
    for(int i = 0; i < N; ++i){
        printf("%d ", sol[i]);
    }
    printf("]\n");
}

int* exist_langford(int N){
    int* langford = new int[2*N];
    if(explore(langford, N, 2*N)) return langford;
    return nullptr;
}

void get_all_langford(int N){
    int* langford = new int[2*N];

    explore_all(langford, N, 2*N);
}


bool explore(int* sol, int gap, int len){
    if(gap == 0){
        cout <<"Yes!\n";
        return true;
    }
    for(int i = len - 1; i - gap > 0 ; i--) {
        if(sol[i] == 0 && sol[i - gap - 1] == 0){
            sol[i] = gap;
            sol[i - gap - 1] = gap;
            if(explore(sol, gap - 1, len)) return true;
            else{
                sol[i] = 0;
                sol[i - gap - 1] = 0;
            }
        }
    }
    return false;
}

void explore_all(int* sol, int gap, int len){
    if(gap == 0){
        print(sol, 2*N);
        return;
    }
    for(int i = len - 1; i - gap > 0 ; i--) {
        if(sol[i] == 0 && sol[i - gap - 1] == 0){
            sol[i] = gap;
            sol[i - gap - 1] = gap;
            explore_all(sol, gap - 1, len); //return true;
            sol[i] = 0;
            sol[i - gap - 1] = 0;
            // if(gap - 1 == 0) return;
        }
    }
    return;
}

int *exist_langford1(int N){
    int * sol = new int[2*N];
    if(explore1(sol, 1, 2*N)) return sol;
    return nullptr;

}

bool explore1(int *a, int gap, int len){

    // printf("len=%d, gap=%d\n", len, gap);

    if(gap == len/2 + 1){
        cout << "gap = " << gap << endl;
        return true;
    }
    for(int i = 0; i < len - gap - 1; ++i){
        if(a[i] == 0 && a[i + gap + 1] == 0){
            a[i] = a[i + gap + 1] = gap;
            if(explore1(a, gap + 1, len)) return true;
            else{
                a[i] = 0;
                a[i + gap + 1] = 0;
            }
        }
    }
    return false;
}



int main(){

    // exist_langford(N);
    get_all_langford(N);
    // int *sol = exist_langford(N);
    // print(sol, 2*N);

    // int *sol1 = exist_langford1(N);
    // print(sol1, 2*N);

    return 0;
}