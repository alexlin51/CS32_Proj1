// Game.cpp

#include "provided.h"
#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

class GameImpl
{
public:
    GameImpl(int nColumns, int nLevels, int N, Player* red, Player* black);
    bool completed(int& winner) const;
    bool takeTurn();
    void play();
    int checkerAt(int c, int r) const;
private:
    Scaffold* n_scaf;
    Player* red_p;
    Player* black_p;
    int turn;
    int n;
};

GameImpl::GameImpl(int nColumns, int nLevels, int N, Player* red, Player* black)
{
    n_scaf = new Scaffold(nColumns, nLevels);
    red_p = red;
    black_p = black;
    n = N;
    turn = RED;
}

bool GameImpl::completed(int& winner) const
{
    // We need to check vertical, Horizontal, and 2 Diagonals

    // Vertical Check
    int count = 0;
    int prev = -2;
    for (int i = 0; i != n_scaf->cols(); i++) {
        for (int j = 0; j != n_scaf->levels(); j++) {
            if (prev != n_scaf->checkerAt(i +1, j +1 )) {
                prev = n_scaf->checkerAt(i +1 , j + 1);
                count = 1;
            }
            else {
                count += 1;
            }
            if (count == n) {
                if (prev == BLACK || prev == RED) {
                    winner = prev;
                    return true;
                }
            }
        }
        count = 0;
        prev = -2;
    }

    // Hortizontal Check
    for (int i = 0; i != n_scaf->levels(); i++) {
        for (int j = 0; j != n_scaf->cols(); j++) {
            if (prev != n_scaf->checkerAt(j+1, i+1)) {
                prev = n_scaf->checkerAt(j+1, i+1);
                count = 1;
            }
            else {
                count += 1;
            }
            if (count == n) {
                if (prev == BLACK || prev == RED) {
                    winner = prev;
                    return true;
                }
            }
        }
        count = 0;
        prev = -2;
    }

    // TL -> BR Diagonal Check
    for (int i = 0; i != n_scaf->cols(); i++) {
        int col = i;
        int row = n_scaf->levels() -1;
        while (row >= 0 && col < n_scaf->cols()) {
            if (prev != n_scaf->checkerAt(col+1, row+1)) {
                prev = n_scaf->checkerAt(col+1, row+1);
                count = 1;
            }
            else {
                count += 1;
            }
            if (count == n) {
                if (prev == BLACK || prev == RED) {
                    winner = prev;
                    return true;
                }
            }
            col += 1;
            row -= 1;
        }
        count = 0;
        prev = -2;
    }
    for (int i = n_scaf->levels() - 2; i >= 0; i--) {
        int row = i;
        int col = 0;
        while (row >= 0 && col < n_scaf->cols()) {
            if (prev != n_scaf->checkerAt(col+1, row+1)) {
                prev = n_scaf->checkerAt(col+1, row+1);
                count = 1;
            }
            else {
                count += 1;
            }
            if (count == n) {
                if (prev == BLACK || prev == RED) {
                    winner = prev;
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
    for (int i = 0; i != n_scaf->levels(); i++) {
        int row = i;
        int col = 0;
        while (row < n_scaf->levels() && col < n_scaf->cols()) {
            if (prev != n_scaf->checkerAt(col+1, row+1)) {
                prev = n_scaf->checkerAt(col+1, row+1);
                count = 1;
            }
            else {
                count += 1;
            }
            if (count == n) {
                if (prev == BLACK || prev == RED) {
                    winner = prev;
                    return true;
                }
            }
            col += 1;
            row += 1;
        }
        count = 0;
        prev = -2;
    }
    for (int i = 1; i != n_scaf->cols(); i++) {
        int row = 0;
        int col = i;
        while (row < n_scaf->levels() && col < n_scaf->cols()) {
            if (prev != n_scaf->checkerAt(col+1, row+1)) {
                prev = n_scaf->checkerAt(col+1, row+1);
                count = 1;
            }
            else {
                count += 1;
            }
            if (count == n) {
                if (prev == BLACK || prev == RED) {
                    winner = prev;
                    return true;
                }
            }
            col += 1;
            row += 1;
        }
        count = 0;
        prev = -2;
    }

    if (n_scaf->numberEmpty() > 0) {
        return false;
    }
    else {
        winner = TIE_GAME;
        return true;
    }

}

bool GameImpl::takeTurn()
{
    int win;
    int col;
    if (completed(win)) {
        return false;
    }
    if (turn == RED) {
        if (red_p->isInteractive()) {
            cout << "Please choose a column" << "(1-" << n_scaf->cols() << ") " << "for your next move." << endl;
        }
        col = red_p->chooseMove(*n_scaf, n, RED);
        n_scaf->makeMove(col, RED);
        turn = BLACK;
    }
    else if (turn == BLACK) {
        if (black_p->isInteractive()) {
            cout << "Please choose a column" << "(1-" << n_scaf->cols() << ") " << "for your next move." << endl;
        }
        col = black_p->chooseMove(*n_scaf, n, BLACK);
        n_scaf->makeMove(col, BLACK);
        turn = RED;
    }
    return true;
}

void GameImpl::play()
{
    int win;
    while (!completed(win)) {
        if (turn == RED) {
            cout << red_p->name() << "'s turn" << endl;
        }
        else if (turn == BLACK) {
            cout << black_p->name() << "'s turn" << endl;
        }
        takeTurn();
        n_scaf->display();
        if (!completed(win)) {
            cout << " " << endl;
            cout << "Press Enter to continue..." << endl;
            cin.get();
        }
    }

    string player;
    int hold;
    if (completed(hold)) {
        switch (hold) {
        case RED:
            player = red_p->name();
            break;
        case BLACK:
            player = black_p->name();
            break;
        case TIE_GAME:
            player = "TIE";
            break;
        default:
            player = "";
        }
    }

    cout << "------------------------------------------------" << endl;
    if (player == "TIE") {
        cout << "Tie game!! Give it a go again and see who wins!" << endl;
    }
    else {
        cout << "The winner of the game is " << player << "!" << endl;
    }
}

int GameImpl::checkerAt(int c, int r) const
{
    return n_scaf->checkerAt(c, r);
}

//******************** Game functions *******************************

//  These functions simply delegate to GameImpl's functions.
//  You probably don't want to change any of this code. 

Game::Game(int nColumns, int nLevels, int N, Player* red, Player* black)
{
    m_impl = new GameImpl(nColumns, nLevels, N, red, black);
}

Game::~Game()
{
    delete m_impl;
}

bool Game::completed(int& winner) const
{
    return m_impl->completed(winner);
}

bool Game::takeTurn()
{
    return m_impl->takeTurn();
}

void Game::play()
{
    m_impl->play();
}

int Game::checkerAt(int c, int r) const
{
    return m_impl->checkerAt(c, r);
}

