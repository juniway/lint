#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

#define INT_MAX 0x7fffffff
#define INT_MIN 0x80000000

// 非递归解法
class NQueen {
public:
    static int index;
    void show(vector<int> queen){
        for(int i = 0; i < (int)queen.size(); i++){
            for (int j = 0; j < kN; ++j) {
                if (j == queen[i]) {
                    cout << j;
                } else cout << "*";
                // cout << queen[i] << " " << endl;
            }
            cout << endl;
        }
        cout << endl;
        index++;
    }

    void init(vector<int>& queen){
         for(int i = 0; i < (int)queen.size(); i++){
             queen[i] = INT_MAX;
         }
    }

    // k 表示层数, i 表示列数
    void process(vector<int> queen) {
         int k = 0, i = 0;
         init(queen); // 初始化数组
         while(k < 8) {
             while(i < 8) {
                 if(check(queen, k, i)) {
                     queen[k] = i;  // 放置皇后k
                     i = 0;         // 探测下一行 将 i 清 0，因为要从下一行的第 0 列开始继续探测
                     break;
                 } else {
                     ++i;           // 探测下一列
                 }
             }

             if(queen[k] == INT_MAX) {  // 从上面的循环中跳出来之后，检查 queen[k] 是否被设置过，如果没，则说明第k行没有找到可以放皇后的地方
                if(k == 0) break;       // 回溯到第一行还没有，就终止
                else {
                    --k;                // 回到上一行
                    i = queen[k] + 1;   // 把上一行皇后的位置往后放一列
                    queen[k] = INT_MAX; // 重置上一行皇后原先的值
                    continue;           // 清除位置 重新探测
                 }
             }

             if(k == 7) {               // 找到解了
                 show(queen);
                 i = queen[k] + 1;      // 把最后一行皇后的位置往后放一列，继续探测下一种可能的解
                 queen[k]=  INT_MAX;
                 continue;              // 清除位置 重新探测
             }

             ++k;                       // 探测下一行
         }
     }

    // 新皇后放入的位置
    bool check(vector<int> queen, int row, int col){
        for(int i = 0; i < row; i++)
            if(queen[i] == col) return false; // 水平及垂直方向检测
        for(int i = 0; i < row; i++)
            if(row - i == abs(col - queen[i])) return false; // 对角线检测
        return true;
    }

private:
    static const int kN = 8;
};

int NQueen::index = 0;

int main() {
    NQueen queen;
    vector<int> v(8, -1);
    queen.process(v);
    cout << "共有" << NQueen::index << "种解法" << endl;
}
