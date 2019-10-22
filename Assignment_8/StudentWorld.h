#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "Actor.h"
#include <vector>
#include "GameWorld.h"
#include <string>
#include "Level.h"
#include "GameConstants.h"
#include <sstream>
#include <iostream>
#include <iomanip>

using namespace std;

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetPath);
    virtual int init();
    virtual int move();
	virtual void cleanUp();
	int sizeOf(); //useful??
	bool actorBlock(Actor* a, int depth, double x, double y);
	bool actorOverlap(double x1, double y1, double x2, double y2);
	bool checkAllOverlap(double x, double y);
	bool flameBlock(Actor* a, int depth, double x, double y);
	~StudentWorld();
	void addActor(Actor* a);
	int exitFunc(double x, double y);
	Penelope* getPlayer()
	{
		return m_player;
	}
	Actor* getActor(int k);
	bool isEveryoneDead();

private:
	Penelope* m_player;
	std::vector<Actor*> actorList;
};

#endif // STUDENTWORLD_H_
