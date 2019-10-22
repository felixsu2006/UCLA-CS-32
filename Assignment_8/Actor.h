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
	Actor(StudentWorld* place, int id, double x, double y, int direction, int depth);
	virtual void doSomething() = 0;
	virtual ~Actor()
	{}
	bool isAlive();
	void kill();
	int depth();
	void direction(Direction d);
	StudentWorld* getWorld();
	bool movement(Direction d, int amount);
	virtual bool infectionPossible()
	{
		return false;
	}
	virtual bool paralysisPossible()
	{
		return false;
	}
	virtual bool canOverlap()
	{
		return false;
	}
	void infected()
	{
		infectionStatus = true;
	}
	void cured()
	{
		infectionStatus = false;
	}
	virtual bool canBurn()
	{
		return true;
	}
	virtual bool canExplode() //for landmine
	{
		return false;
	}
	bool infectionCheck()
	{
		return infectionStatus;
	}
	virtual bool blocksFlames()
	{
		return false;
	}
	virtual bool isDumb()
	{
		return false;
	}


	void pointValue(int x);
	double distance(double x1, double y1, double x2, double y2);
	double closestActor(Actor* a, double x, double y, bool infect, bool para, int type); //returns the closestActor specified by the bool values to actor a
private:
	StudentWorld* world;
	bool aliveCheck = true;
	int m_depth;
	bool infectionStatus = false;
};

class Human : public Actor
{
public:
	Human(StudentWorld* place, int id, double x, double y);
	virtual void doSomething() = 0;
	virtual ~Human()
	{}
	void infectionIncrement()
	{
		infectionCount++;
	}
	int getInfection()
	{
		return infectionCount;
	}
	virtual bool infectionPossible()
	{
		return true;
	}
	void resetInfection()
	{
		infectionCount = 0;
	}
private:
	int infectionCount = 0;

};

class Penelope : public Human
{
public:
	Penelope(StudentWorld* place, double x, double y);
	virtual void doSomething();
	virtual ~Penelope()
	{}
	bool completionCheck();
	void win()
	{
		completionStatus = true;
	}
	void landmineAdd(int x)
	{
		landmines += x;
	}
	void gasAdd(int x)
	{
		gas += x;
	}
	void vaccineAdd(int x)
	{
		vaccines += x;
	}
	void decLandmine()
	{
		landmines--;
	}
	void decGas()
	{
		gas--;
	}
	void decVaccine()
	{
		vaccines--;
	}
	int daVaccine()
	{
		return vaccines;
	}
	int daGas()
	{
		return gas;
	}
	int daMines()
	{
		return landmines;
	}
private:
	int gas = 0;
	int landmines = 0;
	int vaccines = 0;
	bool completionStatus = false;
};

class Citizen : public Human
{
public:
	Citizen(StudentWorld* place, double x, double y);
	virtual void doSomething();
	virtual ~Citizen();
	virtual bool paralysisPossible()
	{
		return true;
	}
	//implement step 7
	void runAway();
private:

	bool paralysisCheck = false;
};

class Zombie : public Actor
{
public:
	Zombie(StudentWorld* place, double x, double y)
		:Actor(place, IID_ZOMBIE, x, y, 0, 0)
	{

	}
	virtual void doSomething() = 0;
	virtual bool paralysisPossible()
	{
		return true;
	}
	bool isParalyzed()
	{
		return paralysisCheck;
	}
	void paralysisSwap()
	{
		paralysisCheck = !paralysisCheck;
	}
	int movementPlan()
	{
		return movementPlanDistance;
	}
	void randomizeMovementPlan();
	void moveZombie(Direction d);
	void setMovementPlanDistance(int k)
	{
		movementPlanDistance = k;
	}
	void decMovementPlanDistance()
	{
		movementPlanDistance--;
	}
	virtual ~Zombie();

	bool doVomit(Actor* a);

private:
	int movementPlanDistance = 0;
	bool paralysisCheck = false;
};

class dumbZombie : public Zombie
{
public:
	dumbZombie(StudentWorld* place, double x, double y)
		:Zombie(place, x, y)
	{
		cerr << paralysisPossible() << "||" << infectionPossible() << endl;
	}
	virtual void doSomething();
	virtual bool isDumb()
	{
		return true;
	}

};

class smartZombie : public Zombie
{
public:
	smartZombie(StudentWorld* place, double x, double y)
		:Zombie(place, x, y)
	{
		cerr << paralysisPossible() << "||" << infectionPossible() << endl;
	}
	virtual void doSomething();
	void runTowards(Actor* a);
	Actor* closestHuman(Actor* a);
};

class Wall : public Actor
{	//wall object must have an image ID of IID_WALL
public:
	Wall(StudentWorld* place, double x, double y);	//start at the location on the level as specified in the current level's data file
			//use Level class and StudentWorld object
			//direction of right, depth of zero
	virtual void doSomething(); //do nothing
	virtual ~Wall();
	virtual bool canBurn()
	{
		return false;
	}
	virtual bool blocksFlames()
	{
		return true;
	}
	
private:
};

class Exit : public Actor
{
public:
	Exit(StudentWorld* place, double x, double y);
	virtual void doSomething();
	virtual ~Exit();
	virtual bool canOverlap()
	{
		return true;
	}
	virtual bool canBurn()
	{
		return false;
	}
	virtual bool blocksFlames()
	{
		return true;
	}
};

class Thing : public Actor
{
public:
	Thing(StudentWorld* place, int id, int depth, double x, double y, int dir)
		:Actor(place, id, x, y, dir, depth)
	{}
	bool isOverlap(Actor* a, double x, double y, string action); //checks if something is overlapping with it, a points to itself, x, y are coordinates 
	virtual void doSomething() = 0;
	virtual bool canOverlap()
	{
		return true;
	}
	void mineFunc(Actor* a, Actor* theMine);
};

class Pit : public Thing
{
public:
	Pit(StudentWorld* place, double x, double y)
		:Thing(place, IID_PIT, 0, x, y, right)
	{}
	virtual void doSomething();
	virtual bool canBurn()
	{
		return false;
	}
};

class Flame : public Thing
{
public:
	Flame(StudentWorld* place, double x, double y, int direction)
		:Thing(place, IID_FLAME, 0, x, y, direction)
	{}
	virtual void doSomething();
	virtual bool canBurn()
	{
		return false;
	}
private:
	int tickLife = 0;
};

class Vomit : public Thing
{
public:
	Vomit(StudentWorld* place, double x, double y, int direction)
		:Thing(place, IID_VOMIT, 0, x, y, direction)
	{}
	virtual void doSomething();
	virtual bool canBurn()
	{
		return false;
	}
private:
	int tickLife = 0;
};

class Landmine : public Thing
{
public:
	Landmine(StudentWorld* place, double x, double y, int direction)
		:Thing(place, IID_LANDMINE, 1, x, y, direction)
	{}
	virtual void doSomething();
	virtual bool canExplode()
	{
		return true;
	}
private:
	int safetyTick = 30;
	bool active = false;
};

class Goodie : public Thing
{
public:
	Goodie(StudentWorld* place, int id, int depth, double x, double y, int dir)
		:Thing(place, id, depth, x, y, dir)
	{}
	virtual void doSomething();
	bool isOverlap(double x, double y); //checks for penelope ONLY
	virtual void pickUp(Penelope* p) = 0;
	virtual bool canBurn()
	{
		return true;
	}

};

class vaccineGoodie : public Goodie
{
public:
	vaccineGoodie(StudentWorld* place, double x, double y)
		:Goodie(place, IID_VACCINE_GOODIE, 1, x, y, right)
	{}
	virtual void pickUp(Penelope* p)
	{
		p->vaccineAdd(1);
	}
};

class landmineGoodie : public Goodie
{
public:
	landmineGoodie(StudentWorld* place, double x, double y)
		:Goodie(place, IID_LANDMINE_GOODIE, 1, x, y, right)
	{}
	virtual void pickUp(Penelope* p)
	{
		p->landmineAdd(2);
	}
};

class gasGoodie : public Goodie
{
public:
	gasGoodie(StudentWorld* place, double x, double y)
		:Goodie(place, IID_GAS_CAN_GOODIE, 1, x, y, right)
	{}
	virtual void pickUp(Penelope* p)
	{
		p->gasAdd(5);
	}
};


#endif // ACTOR_H_
