
#ifndef HISTORY_INCLUDED
#define HISTORY_INCLUDED
#include "globals.h"

class History
{
public:
	History(int nRows, int nCols);
	bool record(int r, int c);
	void display() const;

private:
	int m_row;
	int m_col;
	int dim[MAXROWS][MAXCOLS];
	char disp[MAXROWS][MAXCOLS];
};

#endif //HISTORY_INCLUDED