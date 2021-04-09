#include "History.h"

#include <iostream>
#include <cstdlib>

History::History(int nRows, int nCols)
{
	m_rows = nRows;
	m_cols = nCols;
	
	for (int i = 0; i < nRows; i++) {
		for (int j = 0; j < nCols; j++) {
			grid[i][j] = 0;
		}
	}
}

bool History::record(int r, int c)
{
	if (r < 1 || r > m_rows || c < 1 || c > m_cols) {
		return false;
	}

	grid[r - 1][c - 1]++;

	return true;
}

void History::display() const
{
	clearScreen();
    for (int i = 0; i < m_rows; i++)
    {
        for (int j = 0; j < m_cols; j++)
        {
            int visit = grid[i][j]; 

			switch (visit) {
				case 0:
					std::cout << '.';
					break;
				case 1:
					std::cout << 'A';
					break;
				case 2:
					std::cout << 'B';
					break;
				case 3:
					std::cout << 'C';
					break;
				case 4:
					std::cout << 'D';
					break;
				case 5:
					std::cout << 'E';
					break;
				case 6:
					std::cout << 'F';
					break;
				case 7:
					std::cout << 'G';
					break;
				case 8:
					std::cout << 'H';
					break;
				case 9:
					std::cout << 'I';
					break;
				case 10:
					std::cout << 'J';
					break;
				case 11:
					std::cout << 'K';
					break;
				case 12:
					std::cout << 'L';
					break;
				case 13:
					std::cout << 'M';
					break;
				case 14:
					std::cout << 'N';
					break;
				case 15:
					std::cout << 'O';
					break;
				case 16:
					std::cout << 'P';
					break;
				case 17:
					std::cout << 'Q';
					break;
				case 18:
					std::cout << 'R';
					break;
				case 19:
					std::cout << 'S';
					break;
				case 20:
					std::cout << 'T';
					break;
				case 21:
					std::cout << 'U';
					break;
				case 22:
					std::cout << 'V';
					break;
				case 23:
					std::cout << 'W';
					break;
				case 24:
					std::cout << 'X';
					break;
				case 25:
					std::cout << 'Y';
					break;
				default:
					std::cout << 'Z';
			}
            
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
