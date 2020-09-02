#include <iostream>
#include <vector>
#include <string>
using namespace std;

string tictactoe(vector<string>& board) {
    int N = board[0].size();
    int sum_row = 0, sum_col = 0, sum_dia_main = 0, sum_dia_anti = 0, isFull = 1;
    for (int i = 0; i < N; i++) {
        sum_row = 0, sum_col = 0;
        sum_dia_main += board[i][i];
        sum_dia_anti += board[i][N - i - 1];
        for (int j = 0; j < N; j++) {
            sum_row += board[i][j];
            sum_col += board[j][i];
            if (board[i][j] == ' ') isFull = 0;
        }
        if (sum_row == ((int)'X') * N || sum_col == ((int)'X') * N) {
            return string("X");
        }
        if (sum_row == ((int)'O') * N || sum_col == ((int)'O') * N) {
            return string("O");
        }
    }
    if(sum_dia_main == ((int)'X') * N || sum_dia_main == ((int)'X') * N)
        return string("X");
    if(sum_dia_anti == ((int)'O') * N || sum_dia_anti == ((int)'O') * N)
        return string("O");

    if(isFull) return string("Draw");
    else return string("pending");
}
