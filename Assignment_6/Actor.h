#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include <string>
#include <iostream>
using namespace std;

class StudentWorld;

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class Actor : public GraphObject
{
public:
	Actor(StudentWorld* place, int id, int x, int y, int direction, int depth);
	virtual void doSomething() = 0;
	virtual ~Actor();
	bool isAlive();
	bool isCollide(double x, double y);	//useful??
	virtual void direction(Direction d);
	StudentWorld* getWorld();
private:
	StudentWorld* world;
	bool aliveCheck = true;
};

class Penelope : public Actor
{
public:
	Penelope(StudentWorld* place, int x, int y);
	virtual void doSomething();
	virtual ~Penelope();
	bool penelopeMove(Direction d);
private:
	int flames = 0;
	int mines = 0;
	int vaccines = 0;
};

class Wall : public Actor
{	//wall object must have an image ID of IID_WALL
public:
	Wall(StudentWorld* place, int x, int y);	//start at the location on the level as specified in the current level's data file
			//use Level class and StudentWorld object
			//direction of right, depth of zero
	virtual void doSomething(); //do nothing
	virtual ~Wall();
private:
};
#endif // ACTOR_H_
