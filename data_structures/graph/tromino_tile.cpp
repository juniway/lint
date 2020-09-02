#include <iostream>
#include <vector>

using namespace std;

struct Point {
    int x, y;
    Point(int x, int y):x(x), y(y) {}
};

void tile(vector<vector<char>> &board, Point tl, Point br, Point p) {
    int n = br.x - tl.x;
    if (n < 1) return;

    int mid_row = n / 2;
    int mid_col = n / 2;

    if (p.x >= tl.x && p.x <= tl.x + mid_row && p.y >= tl.y && p.y <= tl.y + mid_col){
        char c = board[p.x][p.y];
        board[tl.x + mid_row][tl.y + mid_col + 1] = 'C';
        board[tl.x + mid_row + 1][tl.y + mid_col + 1] = 'C';
        board[tl.x + mid_row + 1][tl.y + mid_col] = 'C';
        board[p.x][p.y] = c;

        tile(board, Point(tl.x, tl.y), Point(tl.x + mid_row, tl.y + mid_col), p);
        tile(board, Point(tl.x, tl.y + mid_col + 1), Point(tl.x + mid_row, br.y), Point(tl.x + mid_row, tl.y + mid_col + 1));
        tile(board, Point(tl.x + mid_row + 1, tl.y + mid_col + 1), Point(br.x, br.y), Point(tl.x + mid_row + 1, tl.y + mid_col + 1));
        tile(board, Point(tl.x + mid_row + 1, tl.y), Point(br.x, tl.y + mid_col), Point(tl.x + mid_row + 1, tl.y + mid_col));

        return;
    }
    else if (p.x >= tl.x && p.x <= tl.x + mid_row && p.y > tl.y + mid_col && p.y <= br.y) {
        char c = board[p.x][p.y];
        board[tl.x + mid_row][tl.y + mid_col] = 'D';
        board[tl.x + mid_row + 1][tl.y + mid_col + 1] = 'D';
        board[tl.x + mid_row + 1][tl.y + mid_col] = 'D';
        board[p.x][p.y] = c;

        tile(board, Point(tl.x, tl.y), Point(tl.x + mid_row, tl.y + mid_col), Point(tl.x + mid_row, tl.y + mid_col));
        tile(board, Point(tl.x, tl.y + mid_col + 1), Point(tl.x + mid_row, br.y), p);
        tile(board, Point(tl.x + mid_row + 1, tl.y + mid_col + 1), Point(br.x, br.y), Point(tl.x + mid_row + 1, tl.y + mid_col + 1));
        tile(board, Point(tl.x + mid_row + 1, tl.y), Point(br.x, tl.y + mid_col), Point(tl.x + mid_row + 1, tl.y + mid_col));

        return;
    }
    else if (p.x > tl.x + mid_row && p.x <= br.x  && p.y >= tl.y && p.y <= tl.y + mid_col) {
        char c = board[p.x][p.y];
        board[tl.x + mid_row][tl.y + mid_col] = 'B';
        board[tl.x + mid_row][tl.y + mid_col + 1] = 'B';
        board[tl.x + mid_row + 1][tl.y + mid_col + 1] = 'B';
        board[p.x][p.y] = c;

        tile(board, Point(tl.x, tl.y), Point(tl.x + mid_row, tl.y + mid_col), Point(tl.x + mid_row, tl.y + mid_col));
        tile(board, Point(tl.x, tl.y + mid_col + 1), Point(tl.x + mid_row, br.y), Point(tl.x + mid_row, tl.y + mid_col + 1));
        tile(board, Point(tl.x + mid_row + 1, tl.y + mid_col + 1), Point(br.x, br.y), Point(tl.x + mid_row + 1, tl.y + mid_col + 1));
        tile(board, Point(tl.x + mid_row + 1, tl.y), Point(br.x, tl.y + mid_col), p);

        return;
    }
    else {
        char c = board[p.x][p.y];
        board[tl.x + mid_row][tl.y + mid_col] = 'A';
        board[tl.x + mid_row + 1][tl.y + mid_col] = 'A';
        board[tl.x + mid_row][tl.y + mid_col + 1] = 'A';
        board[p.x][p.y] = c;

        tile(board, Point(tl.x, tl.y), Point(tl.x + mid_row, tl.y + mid_col), Point(tl.x + mid_row, tl.y + mid_col));
        tile(board, Point(tl.x, tl.y + mid_col + 1), Point(tl.x + mid_row, br.y), Point(tl.x + mid_row, tl.y + mid_col + 1));
        tile(board, Point(tl.x + mid_row + 1, tl.y + mid_col + 1), Point(br.x, br.y), p);
        tile(board, Point(tl.x + mid_row + 1, tl.y), Point(br.x, tl.y + mid_col), Point(tl.x + mid_row + 1, tl.y + mid_col));

        return;
    }
}

void printBoard(const vector<vector<char>>& board) {
    for (auto i : board) {
        for (auto j : i) {
            cout << j << " ";
        }
        cout << "\n";
    }

    cout << "\n";
}

void trominoTile(int n, Point p) {
    vector<vector<char>> board(n, vector<char>(n, '0'));
    board[p.x][p.y] = 'x';
    tile(board, Point(0, 0), Point(n-1, n-1), p);
    printBoard(board);
}



int main(int argc, char *argv[]) {
    // trominoTile(3, Point(1, 1));
    // trominoTile(2, Point(1, 1));
    // trominoTile(2, Point(0, 0));
    // trominoTile(2, Point(0, 1));
    // trominoTile(2, Point(1, 0));

    // trominoTile(4, Point(3, 1));
    // trominoTile(4, Point(1, 3));
    // trominoTile(4, Point(1, 1));
    // trominoTile(4, Point(1, 2));
    // trominoTile(4, Point(2, 2));
    // trominoTile(4, Point(3, 2));
    // trominoTile(4, Point(2, 3));
    // trominoTile(8, Point(3, 5));
    // trominoTile(8, Point(1, 7));
    // trominoTile(8, Point(7, 2));
    // trominoTile(8, Point(4, 1));
    // trominoTile(8, Point(5, 2));
    //
    return 0;
}
