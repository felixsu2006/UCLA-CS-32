#include "Actor.h"
#include "StudentWorld.h"


//check the logic for StudentWorld* place in the parameters and everywhere else
// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp
Actor::Actor(StudentWorld* place, int id, int x, int y, int direction, int depth)
	: GraphObject(id,SPRITE_WIDTH * x,SPRITE_HEIGHT * y,0,0)
{
	world = place;
}

Actor::~Actor()
{}

bool Actor::isAlive()
{
	return aliveCheck;
}

StudentWorld* Actor::getWorld()
{
	return world;
}

bool Actor::isCollide(double x, double y)
{
	return !world->actorExist(x, y);
}


void Actor::direction(Direction d)//is dis even necessary
{
	setDirection(d);
}

Wall::Wall(StudentWorld* place, int x, int y)
	: Actor(place, IID_WALL, x, y, 0, 0)
{

}

void Wall::doSomething()
{
	return;
}

Wall::~Wall()
{
}

Penelope::Penelope(StudentWorld* place, int x, int y)
	: Actor(place, IID_PLAYER, x, y, 0, 0)
{
	
}

bool Penelope::penelopeMove(Direction d)
{
	if (d == left)
	{
		if (!isCollide(getX() - 4, getY()))
			return false;
		moveTo(getX() - 4, getY());
		setDirection(left);
		return true;
	}
	else if (d == right)
	{
		if (!isCollide(getX() + 4, getY()))
			return false;
		moveTo(getX() + 4, getY());
		setDirection(right);
		return true;
	}
	else if (d == up)
	{
		if (!isCollide(getX(), getY() + 4))
			return false;
		moveTo(getX(), getY() + 4);
		setDirection(up);
		return true;
	}
	else if (d == down)
	{
		if (!isCollide(getX(), getY() - 4))
			return false;
		moveTo(getX(), getY() - 4);
		setDirection(down);
		return true;
	}
	return false;
}
void Penelope::doSomething() //unsigned char key
{
	int ch;
	if (getWorld()->getKey(ch))//something to do with a pointer to either a student or game world via getKey -- getWorld()->getKey(ch)
	{
		switch (ch)
		{
		case KEY_PRESS_LEFT:
		{
			penelopeMove(left);
			break;
		}
		case KEY_PRESS_RIGHT:
		{
			penelopeMove(right);
			break;
		}
		case KEY_PRESS_UP:
		{
			penelopeMove(up);
			break;
		}
		case KEY_PRESS_DOWN:
		{
			penelopeMove(down);
			break;
		}
		}
	}
	return;
}

Penelope::~Penelope()
{
}
