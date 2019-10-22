#include <iostream>
#include <string>
#include <random>
#include <utility>
#include <cstdlib>
#include "History.h"

using namespace std;

History::History(int nRows, int nCols)
{
	m_row = nRows;
	m_col = nCols;
	for (int k = 0; k < nRows; k++)
	{
		for (int j = 0; j < nCols; j++)
		{
			dim[k][j] = 0;
		}
	}

	for (int k = 0; k < MAXROWS; k++)
	{
		for (int j = 0; j < MAXCOLS; j++)
		{
			disp[k][j] = '.';
		}
	}
}

bool History::record(int r, int c)
{
	if (r < 1 || c < 1 || r > m_row || c > m_col)
		return false;
	
	dim[r - 1][c - 1]++;
	if (dim[r - 1][c - 1] == 1)
		disp[r - 1][c - 1] = 'A';
	else if (dim[r - 1][c - 1] >= 26)
		disp[r - 1][c - 1] = 'Z';
	else
		disp[r - 1][c - 1]++;
	return true;
}

void History::display() const
{
	clearScreen();
	for (int k = 0; k < m_row; k++)
	{
		for (int j = 0; j < m_col; j++)
		{
			cout << disp[k][j];
		}
		cout << endl;
	}
	cout << endl;
}