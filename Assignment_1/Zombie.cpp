#include "Arena.h"
#include <iostream>
#include <string>
#include <random>
#include <utility>
#include <cstdlib>
#include "Zombie.h"
using namespace std;


Zombie::Zombie(Arena* ap, int r, int c)
{
	if (ap == nullptr)
	{
		cout << "***** A zombie must be created in some Arena!" << endl;
		exit(1);
	}
	if (r < 1 || r > ap->rows() || c < 1 || c > ap->cols())
	{
		cout << "***** Zombie created with invalid coordinates (" << r << ","
			<< c << ")!" << endl;
		exit(1);
	}
	m_arena = ap;
	m_row = r;
	m_col = c;
	m_health = INITIAL_ZOMBIE_HEALTH;
}

int Zombie::row() const
{
	return m_row;
}

int Zombie::col() const
{
	return m_col;
}

void Zombie::move()
{
	// Attempt to move in a random direction; if we can't move, do not move
	int dir = randInt(0, NUMDIRS - 1);  // dir is now UP, DOWN, LEFT, or RIGHT
	m_arena->determineNewPosition(m_row, m_col, dir);
}

bool Zombie::getAttacked(int dir)  // return true if dies
{
	m_health--;
	if (m_health == 0)
	{
		m_arena->history().record(m_row, m_col);
		return true;
	}
	if (!m_arena->determineNewPosition(m_row, m_col, dir))
	{
		m_health = 0;
		m_arena->history().record(m_row, m_col);
		return true;
	}
	return false;
}