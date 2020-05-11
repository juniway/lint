// KTP, Knight's Tour Problem
// https://en.wikipedia.org/wiki/Knight%27s_tour
A knight's tour is a sequence of moves of a knight on a chessboard
such that the knight visits every square only once.

The knight's tour problem is the mathematical problem of finding a knight's tour.
Creating a program to find a knight's tour is a common problem given to
computer science students.[1]
Variations of the knight's tour problem involve chessboards of different sizes
than the usual 8 × 8, as well as irregular (non-rectangular) boards.

The knight's tour problem is an instance of the more general Hamiltonian path problem
in graph theory.
The problem of finding a closed knight's tour is similarly an instance of the
Hamiltonian cycle problem. Unlike the general Hamiltonian path problem,
the knight's tour problem can be solved in linear time.


Warnsdorf's rule
Warnsdorf's rule is a heuristic for finding a knight's tour.
We move the knight so that we always proceed to the square from which the knight will have the fewest onward moves.
When calculating the number of onward moves for each candidate square, we do not count moves that revisit any square already visited.
It is, of course, possible to have two or more choices for which the number of onward moves is equal;
there are various methods for breaking such ties, including one devised by Pohl [14] and another by Squirrel and Cull.[15]

This rule may also more generally be applied to any graph.
In graph-theoretic terms, each move is made to the adjacent vertex with the least degree.
 Although the Hamiltonian path problem is NP-hard in general, on many graphs that occur in practice
 this heuristic is able to successfully locate a solution in linear time.[14] The knight's tour is a special case.[16]


#include <stdio.h>
#include <string.h>
#define N 8

int board[N][N] = {0};
int ktmove1[8] = {1,2,2,1,-1,-2,-2,-1};   // 对应骑士可走的8个方向
int ktmove2[8] = {-2,-1,1,2,2,2,-1,-2};
int nexti[8] = {0};                       // 测试下一步的出路
int nextj[8] = {0};
int exits[8] = {0};                       // 记录出路的格个数

int travel(int x, int y) {
    int i,j,k,m,l,tmpi,tmpj,tmp,min,cnt;
    memset(ktmove1, 0, sizeof(ktmove1));
    memset(ktmove2, 0, sizeof(ktmove2));
    memset(exits, 0, sizeof(exits));
    i = x;
    j = y;
    board[i][j] = 1;
    for(m=2; m<=N*N; m++) {
        k = 0;
        //试探8个方向
        for(l=0; l<8; l++) {
            tmpi = i + ktmove1[l];
            tmpj = j + ktmove2[l];
            if(tmpi<0 || tmpj<0 || tmpi>7 || tmpj>7)
                continue;
            if(board[tmpi][tmpj]==0) {
                nexti[k] = tmpi;
                nextj[k] = tmpj;
                k++;
            }
        }
        cnt = k;
        if(cnt==0) return 0;        // 如果可走的方向为0，返回
        else if(cnt==1) min = 0;    // 如果可走的方向为1，直接是出路最少的方向
        else {
            //找下一个位置的出路数
            for(l=0; l<cnt; l++) {
                for(k=0; k<8; k++) {
                    tmpi = nexti[l] + ktmove1[k];
                    tmpj = nextj[l] + ktmove2[k];
                    if(tmpi<0 || tmpj<0 || tmpi>7 || tmpj>7)
                        continue;
                    if(board[tmpi][tmpj]==0)
                        exits[l]++;
                }
            }
            tmp = exits[0];
            min = 0;
            //可走方向中寻找最少出路的方向
            for(l=1; l<cnt; l++)
                if(exits[l] < tmp) {
                    tmp = exits[l];
                    min = 1;
                }
        }
        //走最少出路的方向
        i = nexti[min];
        j = nextj[min];
        board[i][j] = m;
    }
    return 1;
}

int main() {
    int sx,sy,i,j;
    //输入起始点
    while(scanf("%d%d",&sx,&sy)!=EOF){
        if(sx<1 || sy<1 || sx>N || sy>N) break;
        if(travel(sx, sy))
            printf("Travel finished!\n");
        else
            printf("Travel falled!\n");
        for(i=0; i<N; i++) {
            for(j=0; j<N; j++) {
                printf("%2d ",board[i][j]);
            }
        puts("");
        }
    }
    return 0;
}
