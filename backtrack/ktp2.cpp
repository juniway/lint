#include <iostream> 
#include <iomanip>  //setw()的头文件 
#define N 8        //定义一个宏并赋初值 
using namespace std; 
int b[N][N];    //定义全局性的二维数组保存步数 
bool a[N][N];   //记录某一点是否已经走过, false 表示没走过
int num = 0;      //记录方案数 
int dx[] = {1,  1, -1, -1, 2,  2, -2, -2};  // 对应骑士可走的8个方向  
int dy[] = {2, -2,  2, -2, 1, -1,  1, -1};  // 提供每一步的走法

bool isMoveOK(int x1, int y1, bool a[N][N]){
	if((x1 >= 0 && x1 < N)&& (y1 >= 0 && y1 < N)&& !a[x1][y1])
		return true;
	return false;
}

void print(){
    num++;     //方案数加一
    cout<<"方案"<<num<<" :"<<endl;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cout << setw(4)<< b[i][j]; //依次输出经过每一点时的步数 
        } 
        cout << endl;
    } 
}

bool solve(int x, int y, int k){ //计算走法
    int x1, y1;
    cout << "k=" << k << endl;
    if(k == N*N - 1){
        print();
        return true;
    }
    for(int i = 0; i < N; i++){
        x1 = x + dx[i];
        y1 = y + dy[i];
        if(isMoveOK(x1, y1, a)){
            cout << "ok" << endl;
            a[x1][y1] = true;  // true 记录该点已经走过
            b[x1][y1] = k;
            if(solve(x1, y1, k + 1)){
                cout << "if\n";
                return true;
            }
            else{
                cout << "else\n";
                a[x1][y1] = false;
            }
            
        } 
    }
    return false;
}

int main(){ 
    int i, j;
    for(i = 0; i < N; i++){
        for(j = 0; j < N; j++)
            a[i][j] = false;
    } 
    
    b[0][0] = 1; //设置起始点
    a[0][0] = true;
    if(solve (0, 0, 0));  //调用函数计算结果
        cout << "succeed\n";
    return 0;
}