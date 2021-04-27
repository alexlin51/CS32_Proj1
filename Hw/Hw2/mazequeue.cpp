#include <string>
#include <queue>
#include <iostream>

using namespace std;

class Coord
{
public:
    Coord(int r, int c) : m_row(r), m_col(c) {}
    int r() const { return m_row; }
    int c() const { return m_col; }
private:
    int m_row;
    int m_col;
};

bool pathExists(char maze[][10], int sr, int sc, int er, int ec) {
    queue<Coord> cQueue;

    const int MAXROW = 10;
    const int MAXCOL = 10;

    cQueue.push(Coord(sr, sc));
    maze[sr][sc] = 'e';

    while (cQueue.empty() != true) {
        Coord current = cQueue.front();
        cQueue.pop();

        int currRow = current.r();
        int currCol = current.c();

        if (currRow == er && currCol == ec) {
            return true;
        }

        if (currRow < MAXROW && maze[currRow + 1][currCol] == '.') {
            cQueue.push(Coord(currRow + 1, currCol));
            maze[currRow + 1][currCol] = 'e';
        }
        if (currCol > 0 && maze[currRow][currCol - 1] == '.') {
            cQueue.push(Coord(currRow, currCol - 1));
            maze[currRow][currCol - 1] = 'e';
        }
        if (currRow > 0 && maze[currRow - 1][currCol] == '.') {
            cQueue.push(Coord(currRow - 1, currCol));
            maze[currRow - 1][currCol] = 'e';
        }
        if (currCol < MAXCOL && maze[currRow][currCol + 1] == '.') {
            cQueue.push(Coord(currRow, currCol + 1));
            maze[currRow][currCol + 1] = 'e';
        }
    }
    return false;
}

int main()
{
    char maze[10][10] = {
                { 'X','X','X','X','X','X','X','X','X','X' },
                { 'X','.','.','.','.','X','.','.','X','X' },
                { 'X','.','X','X','.','X','X','.','.','X' },
                { 'X','X','X','.','.','.','.','X','.','X' },
                { 'X','.','X','X','X','.','X','X','X','X' },
                { 'X','.','X','.','.','.','X','.','.','X' },
                { 'X','.','.','.','X','.','X','.','.','X' },
                { 'X','X','X','X','X','.','X','.','X','X' },
                { 'X','.','.','.','.','.','.','.','.','X' },
                { 'X','X','X','X','X','X','X','X','X','X' }
    };

    if (pathExists(maze, 3, 5, 8, 8))
        cout << "Solvable!!" << endl;
    else
        cout << "Out of luck!" << endl;
}