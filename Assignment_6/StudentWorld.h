#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "Actor.h"
#include <vector>
#include "GameWorld.h"
#include <string>
#include "Level.h"
#include "GameConstants.h"

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
	bool actorExist(double x, double y);
	~StudentWorld();

private:
	Penelope* m_player;
	std::vector<Actor*> actorList;
};

#endif // STUDENTWORLD_H_
