// Scaffold.cpp

#include "provided.h"
#include <string>
#include <stack>
#include <vector>
#include <iostream>
using namespace std;


class ScaffoldImpl
{
  public:
    ScaffoldImpl(int nColumns, int nLevels); 
    ScaffoldImpl(const ScaffoldImpl& other);
    int cols() const;
    int levels() const;
    int numberEmpty() const;
    int checkerAt(int column, int level) const; 
    void display() const; 
    bool makeMove(int column, int color); 
    int undoMove(); 
  private:
    vector<vector<int>> n_board;
    stack<int> n_moves;
    int n_remaining;
    int n_col;
    int n_row;
};

ScaffoldImpl::ScaffoldImpl(int nColumns, int nLevels)
{
    if (nColumns <= 0 || nLevels <= 0) {
        cerr << "Ensure columns and nLevels are postive." << endl;
        exit(1);
    }

    n_col = nColumns;
    n_row = nLevels;
    n_remaining = n_col * n_row;
    for (int i = 0; i != n_col; i++) {
        vector<int> level;
        for (int j = 0; j != n_row; j++) {
            level.push_back(VACANT);
        }
        n_board.push_back(level);
    }
}

ScaffoldImpl::ScaffoldImpl(const ScaffoldImpl& other)
{
    n_board = other.n_board;
    n_remaining = other.n_remaining;
    n_col = other.n_col;
    n_row = other.n_row;
    n_moves = other.n_moves;
}

int ScaffoldImpl::cols() const
{
    return n_col;  
}

int ScaffoldImpl::levels() const
{
    return n_row;  
}

int ScaffoldImpl::numberEmpty() const
{
    return n_remaining;
}

int ScaffoldImpl::checkerAt(int column, int level) const
{
    return n_board[column][level];  
}

void ScaffoldImpl::display() const
{
    for (int i = n_row; i != 0; i--) {
        for (int j = 0; j != n_col; j++) {
            cout << '|';
            switch (n_board[j][i-1]) {
                case BLACK:
                    cout << 'B';
                    break;
                case RED:
                    cout << 'R';
                    break;
                default:
                    cout << ' ';
            }
        }
        cout << '|' << endl;
    }
    for (int i = 0; i != n_col; i++) {
        cout << "+-";
    }
    cout << '+' << endl;
}

bool ScaffoldImpl::makeMove(int column, int color)
{
    if (column < 0 || column > n_col - 1) {
        return false;
    }
    column -= 1;
    if (color == RED || color == BLACK) {}
    else {
        return false;
    }
    for (int i = 0; i != n_row; i++) {
        if (n_board[column][i] == VACANT) {
            n_board[column][i] = color;
            n_moves.push(column);
            n_remaining -= 1;
            return true;
        }
    }
    return false;
}

int ScaffoldImpl::undoMove()
{
    if (!n_moves.empty()) {
        int lastCol = n_moves.top();
        n_moves.pop();
        for (int i = 0; i != n_row; i++) {
            if (n_board[lastCol][i] == VACANT && i != 0) {
                n_board[lastCol][i - 1] = VACANT;
                n_remaining += 1;
                return lastCol;
            }
            if (i == n_row - 1 && n_board[lastCol][i] != VACANT) {
                n_board[lastCol][i] = VACANT;
                n_remaining += 1;
                return lastCol;
            }
        }
    }
    return 0;
}

//******************** Scaffold functions *******************************

//  These functions simply delegate to ScaffoldImpl's functions.
//  You probably don't want to change any of this code. 

Scaffold::Scaffold(int nColumns, int nLevels)
{
    m_impl = new ScaffoldImpl(nColumns, nLevels);
}
 
Scaffold::~Scaffold()
{
    delete m_impl;
}
 
Scaffold::Scaffold(const Scaffold& other)
{
    m_impl = new ScaffoldImpl(*other.m_impl);
}
 
Scaffold& Scaffold::operator=(const Scaffold& rhs)
{
    if (this != &rhs)
    {
        Scaffold temp(rhs);
        swap(m_impl, temp.m_impl);
    }
    return *this;
}
 
int Scaffold::cols() const
{
    return m_impl->cols();
}

int Scaffold::levels() const
{
    return m_impl->levels();
}

int Scaffold::numberEmpty() const
{
    return m_impl->numberEmpty();
}

int Scaffold::checkerAt(int column, int level) const
{
    return m_impl->checkerAt(column, level);
}
 
void Scaffold::display() const
{
    m_impl->display();
}
 
bool Scaffold::makeMove(int column, int color)
{
    return m_impl->makeMove(column, color);
}
 
int Scaffold::undoMove()
{
    return m_impl->undoMove();
}
