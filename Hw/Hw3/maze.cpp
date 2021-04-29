#include <string>
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
    if (sr == er && sc == ec) {
        return true;
    }
    else {
        maze[sr][sc] = 'v';
        
        const int dir[4][2] = { {1,0},{0,1},{-1,0},{0,-1} };
        const int dirCount = 4;
        const int rowIdx = 0;
        const int colIdx = 1;

        for (int i = 0; i != dirCount; i++) {
            if (maze[sr + dir[i][rowIdx]][sc + dir[i][colIdx]] == '.') {
                bool exists = pathExists(maze, sr + dir[i][rowIdx], sc + dir[i][colIdx], er, ec);
                if (exists) {
                    return true;
                }
            }
        }
        return false;
    }
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
                { 'X','X','X','X','X','.','.','.','X','X' },
                { 'X','.','.','.','.','.','X','.','.','X' },
                { 'X','X','X','X','X','X','X','X','X','X' }
    };

    if (pathExists(maze, 3, 5, 8, 8))
        cout << "Solvable!" << endl;
    else
        cout << "Out of luck!" << endl;
}
