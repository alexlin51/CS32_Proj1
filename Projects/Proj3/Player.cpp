// Player.cpp

#include "provided.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;

// HELPER FUNCTIONS  

bool validCol(const Scaffold& s, int col) {
    col -= 1;
    if (col < 0 || col >= s.cols()) {
        return false;
    }
    for (int i = 0; i != s.levels(); i++) {
        if (s.checkerAt(col, i) == VACANT) {
            return true;
        }
    }
    return false;
}

bool bestMove(vector<int> vals, int target, int output[2]) {
    for (int i = 0; i != vals.size(); i++) {
        if (vals[i] == target) {
            output[0] = i + 1;
            output[1] = vals[i];
            return true;
        }
    }
    return false;
}

bool winningResult(const Scaffold& s, int n, int color, int result) {
    // We need to check vertical, Horizontal, and 2 Diagonals

    // Will return true or false based on if the game is finished
    // Will store results in result (-1,0,1)

    // Vertical Check
    int count = 0;
    int prev = -2;
    for (int i = 0; i != s.cols(); i++) {
        for (int j = 0; j != s.levels(); j++) {
            if (prev != s.checkerAt(i, j)) {
                prev = s.checkerAt(i, j);
                count = 1;
            }
            else {
                count += 1;
            }
            if (count == n) {
                if (prev == BLACK || prev == RED) {
                    if (prev == color) {
                        result = 1;
                        return true;
                    }
                    else {
                        result = -1;
                        return true;
                    }
                }
            }
        }
        count = 0;
        prev = -2;
    }

    // Hortizontal Check
    for (int i = 0; i != s.levels(); i++) {
        for (int j = 0; j != s.cols(); j++) {
            if (prev != s.checkerAt(j, i)) {
                prev = s.checkerAt(j, i);
                count = 1;
            }
            else {
                count += 1;
            }
            if (count == n) {
                if (prev == BLACK || prev == RED) {
                    if (prev == color) {
                        result = 1;
                        return true;
                    }
                    else {
                        result = -1;
                        return true;
                    }
                }
            }
        }
        count = 0;
        prev = -2;
    }

    // TL -> BR Diagonal Check
    for (int i = 0; i != s.cols(); i++) {
        int col = i;
        int row = 0;
        while (row < s.levels() && col < s.cols()) {
            if (prev != s.checkerAt(col, row)) {
                prev = s.checkerAt(col, row);
                count = 1;
            }
            else {
                count += 1;
            }
            if (count == n) {
                if (prev == BLACK || prev == RED) {
                    if (prev == color) {
                        result = 1;
                        return true;
                    }
                    else {
                        result = -1;
                        return true;
                    }
                }
            }
            col += 1;
            row += 1;
        }
        count = 0;
        prev = -2;
    }
    for (int i = 1; i != s.levels(); i++) {
        int row = i;
        int col = 0;
        while (row < s.levels() && col < s.cols()) {
            if (prev != s.checkerAt(col, row)) {
                prev = s.checkerAt(col, row);
                count = 1;
            }
            else {
                count += 1;
            }
            if (count == n) {
                if (prev == BLACK || prev == RED) {
                    if (prev == color) {
                        result = 1;
                        return true;
                    }
                    else {
                        result = -1;
                        return true;
                    }
                }
            }
            col += 1;
            row += 1;
        }
        count = 0;
        prev = -2;
    }

    // BL -> TR Diagonal Check
    for (int i = 0; i != s.levels(); i++) {
        int row = i;
        int col = 0;
        while (row >= 0 && col < s.cols()) {
            if (prev != s.checkerAt(col, row)) {
                prev = s.checkerAt(col, row);
                count = 1;
            }
            else {
                count += 1;
            }
            if (count == n) {
                if (prev == BLACK || prev == RED) {
                    if (prev == color) {
                        result = 1;
                        return true;
                    }
                    else {
                        result = -1;
                        return true;
                    }
                }
            }
            col += 1;
            row -= 1;
        }
        count = 0;
        prev = -2;
    }
    for (int i = 1; i != s.cols(); i++) {
        int row = 0;
        int col = i;
        while (row >= 0 && col < s.cols()) {
            if (prev != s.checkerAt(col, row)) {
                prev = s.checkerAt(col, row);
                count = 1;
            }
            else {
                count += 1;
            }
            if (count == n) {
                if (prev == BLACK || prev == RED) {
                    if (prev == color) {
                        result = 1;
                        return true;
                    }
                    else {
                        result = -1;
                        return true;
                    }
                }
            }
            col += 1;
            row -= 1;
        }
        count = 0;
        prev = -2;
    }

    if (s.numberEmpty() > 0) {
        return false;
    }
    else {
        result = 0;
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
    cout << "Please choose a column" << "(1-" << s.cols() << ") " << "for your next move." << endl;
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
                if (s.checkerAt(i, j) == VACANT) {
                    return i + 1;
                }
            }
        }
    }
    return 0;
}

void smartChoose(const Scaffold& p, int N, int color, int r[2]) {
    Scaffold s(p);
    int colSize = s.cols();
    vector<int> results;
    int after[2];
    for (int i = 0; i != colSize; i++) {
        if (validCol(s, i + 1)) {
            s.makeMove(i + 1, color);
            int ans = -2;
            bool finish = winningResult(s, N, color, ans);
            if (finish && (ans == 1 || ans == 0)) {
                results.push_back(ans);
            }
            else {
                if (color == RED) {
                    smartChoose(s, N, BLACK, after);
                }
                else if (color == BLACK) {
                    smartChoose(s, N, RED, after);
                }
                results.push_back(after[0]);
            }
            s.undoMove();
        }
        else {
            results.push_back(-2);
        }
    }

    int output[2];
    bool win = bestMove(results, 1, output);
    if (win) {
        r = output;
        return;
    }
    win = bestMove(results, 0, output);
    if (win) {
        r = output;
        return;
    }
    win = bestMove(results, -1, output);
    if (win) {
        r = output;
        return;
    }
}

int SmartPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
    int response[2];
    smartChoose(s, N, color, response);

    return response[0];
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
