#include <iostream>
#include <stack>
using namespace std;



class Coord
{
public:
	Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
	int r() const { return m_r; }
	int c() const { return m_c; }
private:
	int m_r;
	int m_c;
};

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
	stack<Coord> coordStack;
	Coord end(er, ec);
	coordStack.push(Coord(sr,sc));
	maze[sr][sc] = 'f';
	while (!coordStack.empty())
	{
		Coord a = coordStack.top();
		coordStack.pop();
		cout << "(" << a.r() << "," << a.c() << ")" << endl;
		if (a.r() == end.r() && a.c() == end.c())
			return true;
		if (maze[a.r() + 1][a.c()] == '.' && (a.r() + 1) <= nRows)
		{
			coordStack.push(Coord(a.r() + 1, a.c()));
			maze[a.r() + 1][a.c()] = 'f';
		}
		if (maze[a.r()][a.c() - 1] == '.' && (a.c() - 1) >= 0)
		{
			coordStack.push(Coord(a.r(), a.c() - 1));
			maze[a.r()][a.c() - 1] = 'f';
		}
		if (maze[a.r() - 1][a.c()] == '.' && (a.r() - 1) >= 0)
		{
			coordStack.push(Coord(a.r() - 1, a.c()));
			maze[a.r() - 1][a.c()] = 'f';
		}
		if (maze[a.r()][a.c() + 1] == '.' && (a.c() + 1) <= nCols)
		{
			coordStack.push(Coord(a.r(), a.c() + 1));
			maze[a.r(), a.c() + 1];
		}
	}
	return false;
}

int main()
{
	string maze[10] = {
		"XXXXXXXXXX",
		"X....X...X",
		"X.XX.XX..X",
		"XXX....X.X",
		"X.XXX.XXXX",
		"X.X...X..X",
		"X...X.X..X",
		"XXXXX.X.XX",
		"X........X",
		"XXXXXXXXXX"
	};

	if (pathExists(maze, 10, 10, 3, 5, 8, 8))
		cout << "Solvable!" << endl;
	else
		cout << "Out of luck!" << endl;
}
