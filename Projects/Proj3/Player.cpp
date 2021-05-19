// Player.cpp

#include "provided.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;

// HELPER FUNCTIONS  

// returns true if we can add another piece to column
bool validCol(const Scaffold& s, int col) {
    col -= 1;
    if (col < 0 || col >= s.cols()) {
        return false;
    }
    for (int i = 0; i != s.levels(); i++) {
        if (s.checkerAt(col + 1, i + 1) == VACANT) {
            return true;
        }
    }
    return false;
}

// returns the index of the largest value in vector
int bestMove(vector<int> vals) {
    int idx = 0;
    for (int i = 0; i != vals.size(); i++) {
        if (vals[idx] < vals[i]) {
           idx = i;
        }
    }
    return idx;
}

bool winningResult(const Scaffold& s, int n, int color, int& result) {
    // We need to check vertical, Horizontal, and 2 Diagonals

    // Will return true or false based on if the game is finished
    // will set result to 1 if color wins, 0 if tie, and -1 of other color wins

    // Vertical Check
    int count = 0;
    int prev = -2;
    for (int i = 0; i != s.cols(); i++) {
        for (int j = 0; j != s.levels(); j++) {
            if (prev != s.checkerAt(i + 1, j + 1)) {
                prev = s.checkerAt(i + 1, j + 1);
                count = 1;
            }
            else {
                count += 1;
            }
            if (count == n) {
                if (prev == BLACK || prev == RED) {
                    if (prev == color) {
                        result = 1;
                    }
                    else {
                        result = -1;
                    }
                    return true;
                }
            }
        }
        count = 0;
        prev = -2;
    }

    // Hortizontal Check
    for (int i = 0; i != s.levels(); i++) {
        for (int j = 0; j != s.cols(); j++) {
            if (prev != s.checkerAt(j + 1, i + 1)) {
                prev = s.checkerAt(j + 1, i + 1);
                count = 1;
            }
            else {
                count += 1;
            }
            if (count == n) {
                if (prev == BLACK || prev == RED) {
                    if (prev == color) {
                        result = 1;
                    }
                    else {
                        result = -1;
                    }
                    return true;
                }
            }
        }
        count = 0;
        prev = -2;
    }


    // TL -> BR Diagonal Check
    for (int i = 0; i != s.cols(); i++) {
        int col = i;
        int row = s.levels() - 1;
        while (row >= 0 && col < s.cols()) {
            if (prev != s.checkerAt(col + 1, row + 1)) {
                prev = s.checkerAt(col + 1, row + 1);
                count = 1;
            }
            else {
                count += 1;
            }
            if (count == n) {
                if (prev == BLACK || prev == RED) {
                    if (prev == color) {
                        result = 1;
                    }
                    else {
                        result = -1;
                    }
                    return true;
                }
            }
            col += 1;
            row -= 1;
        }
        count = 0;
        prev = -2;
    }
    for (int i = s.levels() - 2; i >= 0; i--) {
        int row = i;
        int col = 0;
        while (row >= 0 && col < s.cols()) {
            if (prev != s.checkerAt(col + 1, row + 1)) {
                prev = s.checkerAt(col + 1, row + 1);
                count = 1;
            }
            else {
                count += 1;
            }
            if (count == n) {
                if (prev == BLACK || prev == RED) {
                    if (prev == color) {
                        result = 1;
                    }
                    else {
                        result = -1;
                    }
                    return true;
                }
            }
            col += 1;
            row -= 1;
        }
        count = 0;
        prev = -2;
    }

    // BL -> TR Diagonal Check
    for (int i = 0; i != s.levels(); i++) {
        int row = i;
        int col = 0;
        while (row < s.levels() && col < s.cols()) {
            if (prev != s.checkerAt(col + 1, row + 1)) {
                prev = s.checkerAt(col + 1, row + 1);
                count = 1;
            }
            else {
                count += 1;
            }
            if (count == n) {
                if (prev == BLACK || prev == RED) {
                    if (prev == color) {
                        result = 1;
                    }
                    else {
                        result = -1;
                    }
                    return true;
                }
            }
            col += 1;
            row += 1;
        }
        count = 0;
        prev = -2;
    }
    for (int i = 1; i != s.cols(); i++) {
        int row = 0;
        int col = i;
        while (row < s.levels() && col < s.cols()) {
            if (prev != s.checkerAt(col + 1, row + 1)) {
                prev = s.checkerAt(col + 1, row + 1);
                count = 1;
            }
            else {
                count += 1;
            }
            if (count == n) {
                if (prev == BLACK || prev == RED) {
                    if (prev == color) {
                        result = 1;
                    }
                    else {
                        result = -1;
                    }
                    return true;
                }
            }
            col += 1;
            row += 1;
        }
        count = 0;
        prev = -2;
    }

    if (s.numberEmpty() > 0) {
        return false;
    }
    else {
        result = TIE_GAME;
        return true;
    }
}

// Player Class Implementations

class HumanPlayerImpl
{
public:
    virtual bool isInteractive() const { return true; }
    int chooseMove(const Scaffold& s, int N, int color);
};

class BadPlayerImpl
{
public:
    int chooseMove(const Scaffold& s, int N, int color);
};

class SmartPlayerImpl
{
public:
    int chooseMove(const Scaffold& s, int N, int color);
};

int HumanPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
    int selection = -1;
    while (!validCol(s, selection)) {
        cin >> selection;
        if (!validCol(s, selection)) {
            cout << "Column filled. Please enter another column." << endl;
        }
    }
    return selection;
}

int BadPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
    if (s.numberEmpty() > 0) {
        for (int i = 0; i != s.cols(); i++) {
            for (int j = 0; j != s.levels(); j++) {
                if (s.checkerAt(i + 1, j + 1) == VACANT) {
                    return i + 1;
                }
            }
        }
    }
    return 0;
}

void smartChoose(const Scaffold& p, int N, int color, int& r_col, int& val, bool comp, int level) {
    const int BIG = 9999;
    int other;
    if (color == RED) {
        other = BLACK;
    }
    else {
        other = RED;
    }

    Scaffold s(p);
    int colSize = s.cols();
    vector<int> results;
    vector<int> col_track;
    for (int i = 0; i != colSize; i++) {
        if (validCol(s, i + 1)) {
            s.makeMove(i + 1, color);
            int res;
            bool finish = winningResult(s, N, color, res);
            if (finish) {
                int large;
                if (res == -1) {
                    large = 0 - BIG + level;
                }
                else if (res == 1) {
                    large = BIG - level;
                }
                else if (res == 0) {
                    large = 0;
                }
                results.push_back(large);
                col_track.push_back(i+1);
            }
            else {
                int t_col;
                int t_val;
                smartChoose(s, N, other, t_col, t_val, !comp, level+1);
                results.push_back(0-t_val);
                col_track.push_back(i+1);
            }
            s.undoMove();
        }
    }

    int p_col = bestMove(results);
    r_col = col_track[p_col];
    val = results[p_col];
    return;
}

int SmartPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
    int col;
    int val;
    smartChoose(s, N, color, col, val, true, 1);
    return col;
}

//******************** Player derived class functions *************************

//  These functions simply delegate to the Impl classes' functions.
//  You probably don't want to change any of this code. 

HumanPlayer::HumanPlayer(string nm)
    : Player(nm)
{
    m_impl = new HumanPlayerImpl;
}

HumanPlayer::~HumanPlayer()
{
    delete m_impl;
}

int HumanPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    return m_impl->chooseMove(s, N, color);
}

BadPlayer::BadPlayer(string nm)
    : Player(nm)
{
    m_impl = new BadPlayerImpl;
}

BadPlayer::~BadPlayer()
{
    delete m_impl;
}

int BadPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    return m_impl->chooseMove(s, N, color);
}

SmartPlayer::SmartPlayer(string nm)
    : Player(nm)
{
    m_impl = new SmartPlayerImpl;
}

SmartPlayer::~SmartPlayer()
{
    delete m_impl;
}

int SmartPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    return m_impl->chooseMove(s, N, color);
}