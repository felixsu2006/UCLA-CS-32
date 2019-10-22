#include "Actor.h"
#include "StudentWorld.h"


//check the logic for StudentWorld* place in the parameters and everywhere else
// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp
Actor::Actor(StudentWorld* place, int id, double x, double y, int direction, int depth)
	: GraphObject(id,SPRITE_WIDTH * x,SPRITE_HEIGHT * y,direction,depth)
{
	world = place;
	m_depth = depth;
}

void Actor::pointValue(int x)
{
	getWorld()->increaseScore(x);
}

double Actor::distance(double x1, double y1, double x2, double y2)
{
	double x_dif = x1 - x2;
	double y_dif = y1 - y2;
	double diag = x_dif * x_dif + y_dif * y_dif;
	return sqrt(diag);
}

double Actor::closestActor(Actor* a, double x, double y, bool infect, bool para, int type)
{
	double min = -1;
	if (type == 0)
	{
		if (infect == false && para == true)
		{
			//zombies
			for (int k = 0; k < getWorld()->sizeOf(); k++)
			{
				if (a == getWorld()->getActor(k))
					continue;
				if (!getWorld()->getActor(k)->infectionPossible() && getWorld()->getActor(k)->paralysisPossible())
				{
					if (min == -1)
						min = distance(a->getX(), a->getY(), getWorld()->getActor(k)->getX(), getWorld()->getActor(k)->getY());
					else if (min > distance(a->getX(), a->getY(), getWorld()->getActor(k)->getX(), getWorld()->getActor(k)->getY()))
						min = distance(a->getX(), a->getY(), getWorld()->getActor(k)->getX(), getWorld()->getActor(k)->getY());
				}
			}
			return min; //if return -1, there are no zombies
		}
		else if (infect == true && para == true)
		{
			//citizen
			for (int k = 0; k < getWorld()->sizeOf(); k++)
			{
				if (a == getWorld()->getActor(k))
					continue;
				if (getWorld()->getActor(k)->infectionPossible() && getWorld()->getActor(k)->paralysisPossible())
				{
					if (min == -1)
						min = distance(a->getX(), a->getY(), getWorld()->getActor(k)->getX(), getWorld()->getActor(k)->getY());
					else if (min > distance(a->getX(), a->getY(), getWorld()->getActor(k)->getX(), getWorld()->getActor(k)->getY()))
						min = distance(a->getX(), a->getY(), getWorld()->getActor(k)->getX(), getWorld()->getActor(k)->getY());
				}
			}
			return min;
		}
		else if (infect == true && para == false)
		{
			min = distance(a->getX(), a->getY(), getWorld()->getPlayer()->getX(), getWorld()->getPlayer()->getY());
		}
		else
			return min;
		return min;
	}
	else if (type == 1)
	{
		if (infect == false && para == true)
		{
			//zombies
			for (int k = 0; k < getWorld()->sizeOf(); k++)
			{
				if (a == getWorld()->getActor(k))
					continue;
				if (!getWorld()->getActor(k)->infectionPossible() && getWorld()->getActor(k)->paralysisPossible())
				{
					if (min == -1)
						min = distance(x, y, getWorld()->getActor(k)->getX(), getWorld()->getActor(k)->getY());
					else if (min > distance(x, y, getWorld()->getActor(k)->getX(), getWorld()->getActor(k)->getY()))
						min = distance(x, y, getWorld()->getActor(k)->getX(), getWorld()->getActor(k)->getY());
				}
			}
			return min; //if return -1, there are no zombies
		}
		else if (infect == true && para == true)
		{
			//citizen
			for (int k = 0; k < getWorld()->sizeOf(); k++)
			{
				if (a == getWorld()->getActor(k))
					continue;
				if (getWorld()->getActor(k)->infectionPossible() && getWorld()->getActor(k)->paralysisPossible())
				{
					if (min == -1)
						min = distance(x, y, getWorld()->getActor(k)->getX(), getWorld()->getActor(k)->getY());
					else if (min > distance(x, y, getWorld()->getActor(k)->getX(), getWorld()->getActor(k)->getY()))
						min = distance(x, y, getWorld()->getActor(k)->getX(), getWorld()->getActor(k)->getY());
				}
			}
			return min;
		}
		else if (infect == true && para == false)
		{
			min = distance(x, y, getWorld()->getPlayer()->getX(), getWorld()->getPlayer()->getY());
		}
		else
			return min;
		return min;
	}
	else
		return min;
}

bool Actor::isAlive()
{
	return aliveCheck;
}

StudentWorld* Actor::getWorld()
{
	return world;
}

int Actor::depth()
{
	return m_depth;
}

void Actor::direction(Direction d)//is dis even necessary
{
	setDirection(d);
}

void Actor::kill()
{
	aliveCheck = false;
}


bool Actor::movement(Direction d, int amount)
{
	if (d == left)
	{
		if (getWorld()->actorBlock(this, depth(), getX() - amount, getY()))
			return false;
		setDirection(left);
		moveTo(getX() - amount, getY());
		return true;
	}
	else if (d == right)
	{
		if (getWorld()->actorBlock(this, depth(), getX() + amount, getY()))
			return false;
		setDirection(right);
		moveTo(getX() + amount, getY());
		return true;
	}
	else if (d == up)
	{
		if (getWorld()->actorBlock(this, depth(), getX(), getY() + amount))
			return false;
		setDirection(up);
		moveTo(getX(), getY() + amount);
		return true;
	}
	else if (d == down)
	{
		if (getWorld()->actorBlock(this, depth(), getX(), getY() - amount))
			return false;
		setDirection(down);
		moveTo(getX(), getY() - amount);
		return true;
	}
	return false;
}

//----------------------------------------------------------------//
//---------------------------WALL---------------------------------//
//----------------------------------------------------------------//

Wall::Wall(StudentWorld* place, double x, double y)
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

//----------------------------------------------------------------//
//----------------------------HUMAN-------------------------------//
//----------------------------------------------------------------//


Human::Human(StudentWorld* place, int id, double x, double y)
	: Actor(place, id, x, y, 0, 0)
{
}


//----------------------------------------------------------------//
//----------------------------PENELOPE----------------------------//
//----------------------------------------------------------------//

Penelope::Penelope(StudentWorld* place, double x, double y)
	: Human(place, IID_PLAYER, x, y)
{}

bool Penelope::completionCheck()
{
	return completionStatus;
}


void Penelope::doSomething() //unsigned char key
{
	//keep penelope invincible for now
	int ch;
	if (infectionCheck())
	{
		infectionIncrement();
		if (getInfection() == 500)
		{
			kill();
			return;
		}
	}
	if (getWorld()->getKey(ch))//something to do with a pointer to either a student or game world via getKey -- getWorld()->getKey(ch)
	{
		switch (ch)
		{
		case KEY_PRESS_LEFT:
		{
			movement(left, 4);
			break;
		}
		case KEY_PRESS_RIGHT:
		{
			movement(right, 4);
			break;
		}
		case KEY_PRESS_UP:
		{
			movement(up, 4);
			break;
		}
		case KEY_PRESS_DOWN:
		{
			movement(down, 4);
			break;
		}/*
		case 'b':
		{
			cerr << getWorld()->getScore() << endl;
			break;
		}
		case 'k':
		{
			cerr << getWorld()->sizeOf() << endl;
			break;
		}
		case 'g':
		{
			smartZombie* zombie = new smartZombie(getWorld(), 1, 1);
			getWorld()->addActor(zombie);
			cerr << "hurdur" << endl;
			break;
		}
		*/
		case KEY_PRESS_ENTER:
		{
			if (vaccines > 0)
			{
				cured();
				resetInfection();
				vaccines--;
				break;
			}
			else
				break;
		}
		case KEY_PRESS_TAB:
		{
			if (landmines > 0)
			{
				landmines--;
				Landmine* landmine = new Landmine(getWorld(), getX() / SPRITE_WIDTH, getY() / SPRITE_HEIGHT, right);
				getWorld()->addActor(landmine);
				break;
			}
			else
				break;
		}
		case KEY_PRESS_SPACE:
		{
			if (gas > 0)
			{
				getWorld()->playSound(SOUND_PLAYER_FIRE);
				int count = 0;
				gas--;
				double x_coord = getX() / SPRITE_WIDTH;
				double y_coord = getY() / SPRITE_HEIGHT;
				//!getWorld()->flameBlock(a, 0, SPRITE_WIDTH * (x_coord + 1), SPRITE_HEIGHT* y_coord)
				if (getDirection() == right)
				{
					for (int k = 1; k < 4; k++)
					{
						if (!getWorld()->flameBlock(this, 0, SPRITE_WIDTH * (x_coord + k), SPRITE_HEIGHT * y_coord))
						{
							count++;
						}
						else
							k = 4;
					}

					for (int k = 1; k <= count; k++)
					{
						Flame* flame = new Flame(getWorld(), x_coord + k, y_coord, right);
						getWorld()->addActor(flame);
					}
					break;
				}
				else if (getDirection() == left)
				{
					for (int k = 1; k < 4; k++)
					{
						if (!getWorld()->flameBlock(this, 0, SPRITE_WIDTH * (x_coord - k), SPRITE_HEIGHT * y_coord))
						{
							count++;
						}
						else
							k = 4;
					}

					for (int k = 1; k <= count; k++)
					{
						Flame* flame = new Flame(getWorld(), x_coord - k, y_coord, left);
						getWorld()->addActor(flame);
					}
					break;
				}
				else if (getDirection() == up)
				{
					for (int k = 1; k < 4; k++)
					{
						if (!getWorld()->flameBlock(this, 0, SPRITE_WIDTH * (x_coord), SPRITE_HEIGHT * (y_coord + k)))
						{
							count++;
						}
						else
							k = 4;
					}
					for (int k = 1; k <= count; k++)
					{
						Flame* flame = new Flame(getWorld(), x_coord, y_coord + k, up);
						getWorld()->addActor(flame);
					}
					break;
				}
				else
				{
					for (int k = 1; k < 4; k++)
					{
						if (!getWorld()->flameBlock(this, 0, SPRITE_WIDTH * (x_coord), SPRITE_HEIGHT * (y_coord - k)))
						{
							count++;
						}
						else
							k = 4;
					}
					for (int k = 1; k <= count; k++)
					{
						Flame* flame = new Flame(getWorld(), x_coord, y_coord - k, down);
						getWorld()->addActor(flame);
					}
					break;
				}

				break;
			}
			else
				break;
		}
		}
	}
	return;
}


//----------------------------------------------------------------//
//---------------------------EXIT---------------------------------//
//----------------------------------------------------------------//

Exit::Exit(StudentWorld* place, double x, double y)
	: Actor(place, IID_EXIT, x, y, 0, 1)
{

}

void Exit::doSomething()
{
	
		//cerr << getWorld()->getActor(k)->paralysisPossible() << "||" << getWorld()->getActor(k)->infectionPossible() << endl;
		int bunc = getWorld()->exitFunc(getX(), getY());
		if (bunc == 1)
		{
			pointValue(500); //adds 500 points if saved
			getWorld()->playSound(SOUND_CITIZEN_SAVED);
			return;
		}
		else if (getWorld()->actorOverlap(getX(), getY(), getWorld()->getPlayer()->getX(), getWorld()->getPlayer()->getY()) && getWorld()->isEveryoneDead())
		{
			getWorld()->getPlayer()->win();
			return;
		}
		else
			return;
}

Exit::~Exit()
{

}


//----------------------------------------------------------------//
//--------------------------CITIZEN-------------------------------//
//----------------------------------------------------------------//

Citizen::Citizen(StudentWorld* place, double x, double y)
	:Human(place, IID_CITIZEN, x, y)
{
}

Citizen::~Citizen()
{
	
}

void Citizen::runAway()
{
	if (closestActor(this, -1, -1, false, true, 0) <= 80)
	{
		double min = closestActor(this, -1, -1, false, true, 0);
		double current = closestActor(this, -1, -1, false, true, 0);
		int direction_check = getDirection();
		int direction = getDirection();
		if (min < closestActor(this, getX() - 2, getY(), false, true, 1) && !getWorld()->actorBlock(this, this->depth(), getX() - 2, getY()))
		{
			min = closestActor(this, getX() - 2, getY(), false, true, 1);
			direction = left;
		}
		if (min < closestActor(this, getX() + 2, getY(), false, true, 1) && !getWorld()->actorBlock(this, this->depth(), getX() + 2, getY()))
		{
			min = closestActor(this, getX() + 2, getY(), false, true, 1);
			direction = right;
		}
		if (min < closestActor(this, getX(), getY() - 2, false, true, 1) && !getWorld()->actorBlock(this, this->depth(), getX(), getY() - 2))
		{
			min = closestActor(this, getX(), getY() - 2, false, true, 1);
			direction = down;
		}
		if (min < closestActor(this, getX(), getY() + 2, false, true, 1) && !getWorld()->actorBlock(this, this->depth(), getX(), getY() + 2))
		{
			min = closestActor(this, getX(), getY() + 2, false, true, 1);
			direction = up;
		}

		if (min == current && direction == direction_check)
		{
			return;
		}
			
		else
		{
			movement(direction, 2);
			return;
		}
	}
	return;
}

void Citizen::doSomething()
{
	if (!isAlive())
		return;
	if (infectionCheck())
	{
		infectionIncrement();
		if (getInfection() == 500)
		{
			kill();	
			getWorld()->playSound(SOUND_ZOMBIE_BORN);
			pointValue(-1000);
			int k = randInt(1, 10);
			if (k <= 7)
			{
				dumbZombie* dumbzombie = new dumbZombie(getWorld(), getX()/SPRITE_WIDTH, getY()/SPRITE_HEIGHT);
				getWorld()->addActor(dumbzombie);
			}
			else
			{
				smartZombie* smartzombie = new smartZombie(getWorld(), getX()/SPRITE_WIDTH, getY()/SPRITE_HEIGHT);
				getWorld()->addActor(smartzombie);
			}
			return;
		}
	}
	if (paralysisCheck)
	{
		paralysisCheck = false;
		return;
	}
	else
	{
		paralysisCheck = true;
		double dist_p = distance(getX(), getY(), getWorld()->getPlayer()->getX(), getWorld()->getPlayer()->getY());
		double dist_z = closestActor(this, -1, -1, false, true, 0);
		//if(dist_p < dist_z && NO ZOMBIES)
		if((dist_p < dist_z || dist_z == -1) && dist_p <= 80) //check if correct
		{
			if (getX() == getWorld()->getPlayer()->getX() || getY() == getWorld()->getPlayer()->getY())
			{
				if (getX() != getWorld()->getPlayer()->getX())
				{
					if (getX() < getWorld()->getPlayer()->getX() && !getWorld()->actorBlock(this, depth(), getX() + 2, getY()))
					{
						movement(right, 2);
						return;
					}
					else if (getX() > getWorld()->getPlayer()->getX() && !getWorld()->actorBlock(this, depth(), getX() - 2, getY()))
					{
						movement(left, 2);
						return;
					}
					else
					{
						runAway();
					}
				}
				else if (getY() != getWorld()->getPlayer()->getY())
				{
					if (getY() < getWorld()->getPlayer()->getY() && !getWorld()->actorBlock(this, depth(), getX(), getY() + 2))
					{
						movement(up, 2);
						return;
					}
					else if (getY() > getWorld()->getPlayer()->getY() && !getWorld()->actorBlock(this, depth(), getX(), getY() - 2))
					{
						movement(down, 2);
						return;
					}
					else
						runAway();
				}
			}
			else
			{
				//dir_1: 1 = right, 2 = left || dir_2: 1 = up, 2 = down
				int dir_1, dir_2;
				if (getX() < getWorld()->getPlayer()->getX())
					dir_1 = 1;
				else
					dir_1 = 2;

				if (getY() < getWorld()->getPlayer()->getY())
					dir_2 = 1;
				else
					dir_2 = 2;
				int k = randInt(1, 2);
				if (k == 1)
				{
					if (dir_1 == 1)
					{
						if (movement(right, 2))
							return;
						else if (dir_2 == 1 && movement(up, 2))
							return;
						else if (dir_2 == 2 && movement(down, 2))
							return;
						else
							runAway();
					}
					else
					{
						if (movement(left, 2))
							return;
						else if (dir_2 == 1 && movement(up, 2))
							return;
						else if (dir_2 == 2 && movement(down, 2))
							return;
						else
							runAway();
					}
				}
				else
				{
					if (dir_2 == 1)
					{
						if (movement(up, 2))
							return;
						else if (dir_1 == 1 && movement(right, 2))
							return;
						else if (dir_1 == 2 && movement(left, 2))
							return;
						else
							runAway();
					}
					else
					{
						if (movement(down, 2))
							return;
						else if (dir_1 == 1 && movement(right, 2))
							return;
						else if (dir_1 == 2 && movement(left, 2))
							return;
						else
							runAway();
					}
				}

			}

		}
		else if (dist_z <= 80)
		{
			runAway();
		}
		else
			return;
	}
}

//----------------------------------------------------------------//
//-----------------------------ZOMBIE-----------------------------//
//----------------------------------------------------------------//

void Zombie::randomizeMovementPlan()
{
	movementPlanDistance = randInt(3, 10);
	int k = randInt(1, 4);
	if (k == 1)
		setDirection(right);
	else if (k == 2)
		setDirection(left);
	else if (k == 3)
		setDirection(up);
	else
		setDirection(down);
}

void Zombie::moveZombie(Direction d)
{
	if (movement(d, 1))
		movementPlanDistance--;
	else
		movementPlanDistance = 0;
}

bool Zombie::doVomit(Actor* a)
{
	Actor* player = getWorld()->getPlayer();
	int size = getWorld()->sizeOf();
	double vomit_x = -1;
	double vomit_y = -1;
	if (a->getDirection() == right && (player->getX() > a->getX()))
	{
		vomit_x = a->getX() + SPRITE_WIDTH;
		vomit_y = a->getY();
	}
	else if (a->getDirection() == left && (player->getX() < a->getX()))
	{
		vomit_x = a->getX() - SPRITE_WIDTH;
		vomit_y = a->getY();
	}
	else if (a->getDirection() == up && (player->getY() > a->getY()))
	{
		vomit_y = a->getY() + SPRITE_HEIGHT;
		vomit_x = a->getX();
	}
	else if (a->getDirection() == down && (player->getY() < a->getY()))
	{
		vomit_y = a->getY() - SPRITE_HEIGHT;
		vomit_x = a->getX();
	}
	else
	{
		for (int k = 0; k < size; k++)
		{
			Actor* temp = getWorld()->getActor(k);
			if (temp->paralysisPossible() && temp->infectionPossible())
			{
				if (a->getDirection() == right && (temp->getX() > a->getX()))
				{
					vomit_x = a->getX() + SPRITE_WIDTH;
					vomit_y = a->getY();
				}
				else if (a->getDirection() == left && (temp->getX() < a->getX()))
				{
					vomit_x = a->getX() - SPRITE_WIDTH;
					vomit_y = a->getY();
				}
				else if (a->getDirection() == up && (temp->getY() > a->getY()))
				{
					vomit_y = a->getY() + SPRITE_HEIGHT;
					vomit_x = a->getX();
				}
				else if (a->getDirection() == down && (temp->getY() < a->getY()))
				{
					vomit_y = a->getY() - SPRITE_HEIGHT;
					vomit_x = a->getX();
				}
			}


		}

		
	}

	if (vomit_x == -1 || vomit_y == -1)
		return false;
	
	for (int k = 0; k < size; k++)
	{
		Actor* temp = getWorld()->getActor(k);
		if (temp->paralysisPossible() && temp->infectionPossible())
		{
			if (getWorld()->actorOverlap(vomit_x, vomit_y, temp->getX(), temp->getY()))
			{
				int rand = randInt(1, 3);
				if (rand == 1)
				{
					Vomit* vomit = new Vomit(getWorld(), vomit_x/SPRITE_WIDTH, vomit_y/SPRITE_HEIGHT, a->getDirection());
					getWorld()->addActor(vomit);
					getWorld()->playSound(SOUND_ZOMBIE_VOMIT);
					return true;
				}
				
			}
		}
	}

	if (getWorld()->actorOverlap(vomit_x, vomit_y, player->getX(), player->getY()))
	{
		int rand = randInt(1, 3);
		if (rand == 1)
		{
			Vomit* vomit = new Vomit(getWorld(), vomit_x/SPRITE_WIDTH, vomit_y/SPRITE_HEIGHT, a->getDirection());
			getWorld()->addActor(vomit);
			getWorld()->playSound(SOUND_ZOMBIE_VOMIT);
			return true;
		}

	}
	return false;

}


Zombie::~Zombie()
{

}

//----------------------------------------------------------------//
//----------------------------DUMBZOMBIE--------------------------//
//----------------------------------------------------------------//

void dumbZombie::doSomething()
{
	if (!isAlive())
		return;
	if (isParalyzed())
	{
		paralysisSwap();
		return;
	}
	paralysisSwap();
	if(doVomit(this))//vomit stuff
		return;
	if (movementPlan() == 0)
		randomizeMovementPlan();
	moveZombie(getDirection());


}

//----------------------------------------------------------------//
//-------------------------SMARTZOMBIE----------------------------//
//----------------------------------------------------------------//

Actor* smartZombie::closestHuman(Actor* a)
{
	double min = distance(a->getX(), a->getY(), getWorld()->getPlayer()->getX(), getWorld()->getPlayer()->getY());
	Actor* dink = getWorld()->getPlayer();
	for (int k = 0; k < getWorld()->sizeOf(); k++)
	{
		//cerr << getWorld()->getActor(k)->infectionPossible() << "||" << getWorld()->getActor(k)->paralysisPossible() << endl;
		if (getWorld()->getActor(k)->infectionPossible() && getWorld()->getActor(k)->paralysisPossible())
		{
			if (min > distance(a->getX(), a->getY(), getWorld()->getActor(k)->getX(), getWorld()->getActor(k)->getY()))
			{
				min = distance(a->getX(), a->getY(), getWorld()->getActor(k)->getX(), getWorld()->getActor(k)->getY());
				dink = getWorld()->getActor(k);
			}
		}
	}
	return dink;
}

void smartZombie::runTowards(Actor* a)
{
	if (getX() == a->getX() || getY() == a->getY())
	{
		if (getX() < a->getX())
		{
			if (movement(right, 1))
			{
				decMovementPlanDistance();
				return;
			}
			else
			{
				setMovementPlanDistance(0);
				return;
			}
		}
		else if (getX() > a->getX())
		{
			if (movement(left, 1))
			{
				decMovementPlanDistance();
				return;
			}
			else
			{
				setMovementPlanDistance(0);
				return;
			}
		}
		else if (getY() < a->getY())
		{
			if (movement(up, 1))
			{
				decMovementPlanDistance();
				return;
			}
			else
			{
				setMovementPlanDistance(0);
				return;
			}
		}
		else if (getY() > a->getY())
		{
			if (movement(down, 1))
			{
				decMovementPlanDistance();
				return;
			}
			else
			{
				setMovementPlanDistance(0);
				return;
			}
		}
	}
	else
	{
		int dir_1, dir_2;
		if (getX() < a->getX())
			dir_1 = 1; //right
		else
			dir_1 = 2; //left
		if (getY() < a->getY())
			dir_2 = 1; //up
		else
			dir_2 = 2; //down
		int k = randInt(1, 2);
		if (k == 1) //x-axis
		{
			if (dir_1 == 1)
			{
				if (movement(right, 1))
				{
					decMovementPlanDistance();
					return;
				}
				else
				{
					setMovementPlanDistance(0);
					return;
				}
			}
			else
			{
				if (movement(left, 1))
				{
					decMovementPlanDistance();
					return;
				}
				else
				{
					setMovementPlanDistance(0);
					return;
				}
			}
		}
		else
		{
			if (dir_2 == 1)
			{
				if (movement(up, 1))
				{
					decMovementPlanDistance();
					return;
				}
				else
				{
					setMovementPlanDistance(0);
					return;
				}
			}
			else
			{
				if (movement(down, 1))
				{
					decMovementPlanDistance();
					return;
				}
				else
				{
					setMovementPlanDistance(0);
					return;
				}
			}
		}
	}
}

void smartZombie::doSomething()
{
	if (!isAlive())
		return;
	if (isParalyzed())
	{
		paralysisSwap();
		return;
	}
	paralysisSwap();
	if (doVomit(this))
		return;
	if (movementPlan() == 0)//check with lucas if this is okay
	{
		int rand = randInt(3, 10);
		setMovementPlanDistance(rand);
	}
	Actor* close = closestHuman(this);
	double min = distance(getX(), getY(), close->getX(), close->getY());
	if (min > 80)
	{
		int dir = randInt(1, 4);
		if (dir == 1)
			setDirection(right);
		else if (dir == 2)
			setDirection(left);
		else if (dir == 3)
			setDirection(up);
		else
			setDirection(down);
		if (movement(getDirection(), 1))
		{
			decMovementPlanDistance();
			return;
		}
		else
		{
			setMovementPlanDistance(0);
			return;
		}
	}
	else
	{
		runTowards(close);
	}
	
}

//----------------------------------------------------------------//
//-----------------------------THING------------------------------//
//----------------------------------------------------------------//


void Thing::mineFunc(Actor* a, Actor* theMine)
{
	if (a->canExplode())
		return;
	getWorld()->playSound(SOUND_LANDMINE_EXPLODE);
	/*
	if (a->paralysisPossible() && a->infectionPossible())
	{
		pointValue(-1000);
		getWorld()->playSound(SOUND_CITIZEN_DIE);
	}
	else if (a->paralysisPossible() && !a->infectionPossible())
	{
		pointValue(1000);
		getWorld()->playSound(SOUND_ZOMBIE_DIE);
	}*/
	double x_coord = theMine->getX() / SPRITE_WIDTH;
	double y_coord = theMine->getY() / SPRITE_HEIGHT;
	int dir = theMine->getDirection();
	Flame* flame = new Flame(getWorld(), x_coord, y_coord, dir);
	getWorld()->addActor(flame);
	Pit* pit = new Pit(getWorld(), x_coord, y_coord);
	getWorld()->addActor(pit);
	/*
	if (!getWorld()->flameBlock(a, 0, SPRITE_WIDTH * (x_coord + 1), SPRITE_HEIGHT* y_coord))
	{
		cerr << "asd " << endl;
		Flame* flame1 = new Flame(getWorld(), x_coord + 1, y_coord, dir);
		getWorld()->addActor(flame1);
	}
	if (!getWorld()->flameBlock(a, 0, SPRITE_WIDTH * (x_coord + 1), (y_coord + 1) * SPRITE_HEIGHT))
	{
		Flame* flame1 = new Flame(getWorld(), x_coord + 1, y_coord + 1, dir);
		getWorld()->addActor(flame1);
	}
	if (!getWorld()->flameBlock(a, 0, x_coord * SPRITE_WIDTH, (y_coord + 1) * SPRITE_HEIGHT))
	{
		Flame* flame1 = new Flame(getWorld(), x_coord, y_coord + 1, dir);
		getWorld()->addActor(flame1);
	}
	if (!getWorld()->flameBlock(a, 0, (x_coord - 1) * SPRITE_WIDTH, (y_coord + 1) * SPRITE_HEIGHT))
	{
		Flame* flame1 = new Flame(getWorld(), x_coord - 1, y_coord + 1, dir);
		getWorld()->addActor(flame1);
	}
	if (!getWorld()->flameBlock(a, 0, (x_coord - 1) * SPRITE_WIDTH, SPRITE_HEIGHT * y_coord))
	{
		Flame* flame1 = new Flame(getWorld(), x_coord - 1, y_coord, dir);
		getWorld()->addActor(flame1);
	}
	if (!getWorld()->flameBlock(a, 0, (x_coord - 1) * SPRITE_WIDTH, (y_coord - 1)* SPRITE_HEIGHT))
	{
		Flame* flame1 = new Flame(getWorld(), x_coord - 1, y_coord - 1, dir);
		getWorld()->addActor(flame1);
	}
	if (!getWorld()->flameBlock(a, 0, SPRITE_WIDTH * x_coord, (y_coord - 1)*SPRITE_HEIGHT))
	{
		Flame* flame1 = new Flame(getWorld(), x_coord, y_coord - 1, dir);
		getWorld()->addActor(flame1);
	}
	if (!getWorld()->flameBlock(a, 0, (x_coord + 1) * SPRITE_WIDTH, (y_coord - 1)*SPRITE_HEIGHT))
	{
		Flame* flame1 = new Flame(getWorld(), x_coord + 1, y_coord - 1, dir);
		getWorld()->addActor(flame1);
	}
	*/
	Flame* flame1 = new Flame(getWorld(), x_coord + 1, y_coord, up);
	getWorld()->addActor(flame1);

	Flame* flame2 = new Flame(getWorld(), x_coord + 1, y_coord + 1, up);
	getWorld()->addActor(flame2);

	Flame* flame3 = new Flame(getWorld(), x_coord, y_coord + 1, up);
	getWorld()->addActor(flame3);

	Flame* flame4 = new Flame(getWorld(), x_coord - 1, y_coord + 1, up);
	getWorld()->addActor(flame4);

	Flame* flame5 = new Flame(getWorld(), x_coord - 1, y_coord, up);
	getWorld()->addActor(flame5);

	Flame* flame6 = new Flame(getWorld(), x_coord - 1, y_coord - 1, up);
	getWorld()->addActor(flame6);

	Flame* flame7 = new Flame(getWorld(), x_coord, y_coord - 1, up);
	getWorld()->addActor(flame7);

	Flame* flame8 = new Flame(getWorld(), x_coord + 1, y_coord - 1, up);
	getWorld()->addActor(flame8);

	theMine->kill();

}

bool Thing::isOverlap(Actor* a, double x, double y, string action)
{

	if (a == nullptr)
		return false;
//	cerr << x << "||" << y << endl;
	int size = getWorld()->sizeOf();
	for (int k = 0; k < size; k++)
	{
		if (a == getWorld()->getActor(k))
			continue;
		double x2 = getWorld()->getActor(k)->getX();
		double y2 = getWorld()->getActor(k)->getY();
		Actor* temp = getWorld()->getActor(k);
		if (!temp->isAlive())
			return false;
		
		if (getWorld()->actorOverlap(x2, y2, x, y))
		{
			if (action == "fire")
			{
				if (temp->paralysisPossible() && temp->infectionPossible())
				{
					pointValue(-1000);
					getWorld()->playSound(SOUND_CITIZEN_DIE);
					temp->kill();
					return true;
				}
				else if (temp->paralysisPossible() && !temp->infectionPossible())
				{
					if (temp->isDumb())
						pointValue(1000);
					else
						pointValue(2000);
					getWorld()->playSound(SOUND_ZOMBIE_DIE);
					temp->kill();
					if (!temp->isDumb())
						return true;
					int randDir = randInt(1, 4);//right, left, up, down
					int chance = randInt(1, 10);
					if (chance != 10)
						return true;
					else
					{
						if (randDir == 1 && getWorld()->checkAllOverlap(x + SPRITE_WIDTH, y))
						{
							vaccineGoodie* vaccine = new vaccineGoodie(getWorld(), (x + SPRITE_WIDTH)/SPRITE_WIDTH, y/SPRITE_HEIGHT);
							getWorld()->addActor(vaccine);
						}
						else if (randDir == 2 && getWorld()->checkAllOverlap(x - SPRITE_WIDTH, y))
						{
							vaccineGoodie* vaccine = new vaccineGoodie(getWorld(), (x - SPRITE_WIDTH)/SPRITE_WIDTH, y/SPRITE_HEIGHT);
							getWorld()->addActor(vaccine);
						}
						else if (randDir == 3 && getWorld()->checkAllOverlap(x, y + SPRITE_HEIGHT))
						{
							vaccineGoodie* vaccine = new vaccineGoodie(getWorld(), x/SPRITE_WIDTH, (y + SPRITE_HEIGHT)/SPRITE_HEIGHT);
							getWorld()->addActor(vaccine);
						}
						else if (randDir == 4 && getWorld()->checkAllOverlap(x, y - SPRITE_HEIGHT))
						{
							vaccineGoodie* vaccine = new vaccineGoodie(getWorld(), x/SPRITE_WIDTH, (y - SPRITE_HEIGHT)/SPRITE_HEIGHT);
							getWorld()->addActor(vaccine);
						}
					}
					return true;
				}
				else if (temp->canExplode())
				{
					mineFunc(a, temp);
					return true;
				}
				else if (temp->canBurn())
				{
					temp->kill();
					return true;
				}
				
				
			}
			else if (action == "infect")
			{
				if (temp->paralysisPossible() && temp->infectionPossible())
				{
					if (!temp->infectionCheck())
						getWorld()->playSound(SOUND_CITIZEN_INFECTED);
					temp->infected();
					return true;
				}
			}
			else if (action == "mine")
			{
				if (temp->canExplode())
				{
					return false;
				}
				else if (temp->blocksFlames() && !temp->canBurn())
				{
					return false;
				}
				else
				{
					mineFunc(temp, a);
					return true;
				}
			}
		}
	}
	return false;
}

//----------------------------------------------------------------//
//-----------------------------FLAME------------------------------//
//----------------------------------------------------------------//

void Flame::doSomething()
{
	if (!isAlive())
		return;
	if (tickLife == 2)
	{
		kill();
		return;
	}
	tickLife++;
	isOverlap(this, getX(), getY(), "fire");
	if (getWorld()->actorOverlap(getX(), getY(), getWorld()->getPlayer()->getX(), getWorld()->getPlayer()->getY()))
	{
		getWorld()->getPlayer()->kill();
	}
}

//----------------------------------------------------------------//
//-----------------------------VOMIT------------------------------//
//----------------------------------------------------------------//

void Vomit::doSomething()
{
	if (!isAlive())
		return;
	if (tickLife == 2)
	{
		kill();
		return;
	}
	tickLife++;
	isOverlap(this, getX(), getY(), "infect");
	if (getWorld()->actorOverlap(getX(), getY(), getWorld()->getPlayer()->getX(), getWorld()->getPlayer()->getY()))
	{
		getWorld()->getPlayer()->infected();
	}
}


//----------------------------------------------------------------//
//---------------------------LANDMINE-----------------------------//
//----------------------------------------------------------------//

void Landmine::doSomething()
{
	if (!isAlive())
		return;
	if (safetyTick > 0)
	{
		safetyTick--;
		return;
	}
	else if (safetyTick == 0 && !active)
	{
		active = true;
		return;
	}
	if (isOverlap(this, getX(), getY(), "mine"))
		return;
	if (getWorld()->actorOverlap(getX(), getY(), getWorld()->getPlayer()->getX(), getWorld()->getPlayer()->getY()))
	{
		mineFunc(getWorld()->getPlayer(), this);
	}
}


//----------------------------------------------------------------//
//-----------------------------GOODIE-----------------------------//
//----------------------------------------------------------------//


bool Goodie::isOverlap(double x, double y)
{
	double x2 = getWorld()->getPlayer()->getX();
	double y2 = getWorld()->getPlayer()->getY();
	return getWorld()->actorOverlap(x, y, x2, y2);
}
void Goodie::doSomething()
{
	if (!isAlive())
		return;
	if (isOverlap(getX(), getY()))
	{
		pointValue(50); //adds 50 points if escape
		kill();
		getWorld()->playSound(SOUND_GOT_GOODIE);
		pickUp(getWorld()->getPlayer());
	}
}

//----------------------------------------------------------------//
//----------------------------PIT---------------------------------//
//----------------------------------------------------------------//

/*void Pit::doSomething()
{
	int size = getWorld()->sizeOf();
	for (int k = 0; k < size; k++)
	{
		Actor* temp = getWorld()->getActor(k);
		if (this == temp)
			continue;
		if (getWorld()->actorOverlap(getX(), getY(), temp->getX(), temp->getY()))
		{
			if (temp->paralysisPossible() && temp->infectionPossible())
			{
				pointValue(-1000);
				getWorld()->playSound(SOUND_CITIZEN_DIE);
			}
			else
			{
				pointValue(1000);
				getWorld()->playSound(SOUND_ZOMBIE_DIE);
			}
			temp->kill();
			return;
		}
	}
	if (getWorld()->actorOverlap(getX(), getY(), getWorld()->getPlayer()->getX(), getWorld()->getPlayer()->getY()))
	{
		getWorld()->getPlayer()->kill();
	}
}*/
void Pit::doSomething()
{
	isOverlap(this, getX(), getY(), "fire");
	if (getWorld()->actorOverlap(getX(), getY(), getWorld()->getPlayer()->getX(), getWorld()->getPlayer()->getY()))
	{
		getWorld()->getPlayer()->kill();
	}
}