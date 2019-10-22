#include "StudentWorld.h"


GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath)
{
	m_player = nullptr;
}

StudentWorld::~StudentWorld()
{
	cleanUp();
}

Actor* StudentWorld::getActor(int k)
{
	return actorList[k];
}

bool StudentWorld::actorBlock(Actor* a, int depth, double x, double y) //determines if an actor exists on this panel
{
	for (int k = 0; k < sizeOf(); k++)
	{
		if (actorList[k] == a)
			continue;
		if (actorList[k]->depth() > depth)
			continue;
		if (actorList[k]->canOverlap())
			continue;
		if (actorList[k]->getX() + SPRITE_WIDTH - 1 >= x && actorList[k]->getX() - SPRITE_WIDTH + 1 <= x && actorList[k]->getY() + SPRITE_HEIGHT - 1 >= y && actorList[k]->getY() - SPRITE_HEIGHT + 1 <= y)
			return true;
		if (a == getPlayer())
			continue;
		if (getPlayer()->getX() + SPRITE_WIDTH - 1 >= x && getPlayer()->getX() - SPRITE_WIDTH + 1 <= x && getPlayer()->getY() + SPRITE_HEIGHT - 1 >= y && getPlayer()->getY() - SPRITE_HEIGHT + 1 <= y)
			return true;
	}
	return false;
}

bool StudentWorld::flameBlock(Actor* a, int depth, double x, double y)
{
	for (int k = 0; k < sizeOf(); k++)
	{
		if (a == actorList[k])
			continue;
		//if(a ==)
		if (actorList[k]->getX() + SPRITE_WIDTH - 1 >= x && actorList[k]->getX() - SPRITE_WIDTH + 1 <= x && actorList[k]->getY() + SPRITE_HEIGHT - 1 >= y && actorList[k]->getY() - SPRITE_HEIGHT + 1 <= y && !actorList[k]->canBurn() && actorList[k]->blocksFlames())
			return true;
		//if (getPlayer()->getX() + SPRITE_WIDTH - 1 >= x && getPlayer()->getX() - SPRITE_WIDTH + 1 <= x && getPlayer()->getY() + SPRITE_HEIGHT - 1 >= y && getPlayer()->getY() - SPRITE_HEIGHT + 1 <= y && !actorList[k]->canBurn() && actorList[k]->blocksFlames())
			//return true;
	}
	return false;
}

bool StudentWorld::actorOverlap(double x1, double y1, double x2, double y2)
{
	double x_difference = x1 - x2;
	double y_difference = y1 - y2;
	if (x_difference*x_difference + y_difference*y_difference <= 100)
		return true;
	else
		return false;
}

bool StudentWorld::checkAllOverlap(double x, double y)
{
	for (int k = 0; k < sizeOf(); k++)
	{
		Actor* temp = actorList[k];
		if (actorOverlap(x, y, temp->getX(), temp->getY()))
			return false;

	}
	return true;
}

int StudentWorld::sizeOf()
{
	return actorList.size();
}


void StudentWorld::addActor(Actor* a)
{
	actorList.push_back(a);
}

int StudentWorld::exitFunc(double x, double y)
{
	for (int k = 0; k < sizeOf(); k++)
	{
		if (actorOverlap(actorList[k]->getX(), actorList[k]->getY(), x, y) && actorList[k]->paralysisPossible() && actorList[k]->infectionPossible())
		{
			actorList[k]->kill();
			return 1;
		}
	}
	return 0;
}

bool StudentWorld::isEveryoneDead()
{
	for (int k = 0; k < sizeOf(); k++)
	{
		//cerr << actorList[k]->paralysisPossible() << "||" << actorList[k]->infectionPossible() << endl;
		if (actorList[k]->depth() == 0 && actorList[k]->paralysisPossible() && actorList[k]->infectionPossible())
		{
			return false;
		}
	}
	return true;
}

int StudentWorld::init()
{
	ostringstream oss;
	//int leve = getLevel();
	int leve = 3;
	oss.fill('0');
	oss << "level" << setw(2) << leve << ".txt";
	string s = oss.str();
	Level lev(assetPath());
	Level::LoadResult result = lev.loadLevel(s);
	if (result == Level::load_fail_file_not_found || getLevel() > 99)
	{
		return GWSTATUS_PLAYER_WON;
		cerr << "Cannot find " << s << "data file" << endl;
	}
	else if (result == Level::load_fail_bad_format)
	{
		return GWSTATUS_LEVEL_ERROR;
		cerr << "Your level was improperly formatted" << endl;
	}
	else if (result == Level::load_success)
	{
		cerr << "Successfully loaded level" << endl;
		for (int k = LEVEL_WIDTH - 1; k >= 0; k--)
		{
			for (int j = 0; j < LEVEL_HEIGHT; j++)
			{
				Level::MazeEntry ge = lev.getContentsOf(j, k);
				switch (ge)
				{
				case Level::empty:
				{

					break;
				}
				case Level::player:
				{
					m_player = new Penelope(this, j, k);

					break;
				}
				case Level::wall:
				{
					Wall* wall = new Wall(this, j, k);
					actorList.push_back(wall);

					break;
				}
				case Level::exit:
				{
					Exit* exit = new Exit(this, j, k);
					actorList.push_back(exit);
					break;
				}
				case Level::citizen:
				{
					Citizen* citizen = new Citizen(this, j, k);
					actorList.push_back(citizen);
					break;
				}
				
				case Level::dumb_zombie:
				{
					dumbZombie* dumbzombie = new dumbZombie(this, j, k);
					actorList.push_back(dumbzombie);
					break;
				}

				case Level::smart_zombie:
				{
					smartZombie* smartzombie = new smartZombie(this, j, k);
					actorList.push_back(smartzombie);
					break;
				}

				case Level::vaccine_goodie:
				{
					vaccineGoodie* vaccinegoodie = new vaccineGoodie(this, j, k);
					actorList.push_back(vaccinegoodie);
					break;
				}

				case Level::gas_can_goodie:
				{
					gasGoodie* gasgoodie = new gasGoodie(this, j, k);
					actorList.push_back(gasgoodie);
					break;
				}
				
				case Level::landmine_goodie:
				{
					landmineGoodie* landminegoodie = new landmineGoodie(this, j, k);
					actorList.push_back(landminegoodie);
					break;
				}
				
				case Level::pit:
				{
					Pit* pit = new Pit(this, j, k);
					actorList.push_back(pit);
					break;
				}
				default:
					break;
				}
			}
		}
	}


    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you hit enter.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
	ostringstream oss;
	oss.fill('0');
	oss << "Score: "; //use stringstream to do score (000000)
	if (getScore() >= 0)
		oss << setw(6) << getScore();
	else
		oss << "-" << setw(5) << (-1 * getScore());
	oss << "  Level: " << getLevel() << "  Lives: " << getLives() << "  Vaccines: " << getPlayer()->daVaccine() << "  Flames: " << getPlayer()->daGas() << "  Mines: " << getPlayer()->daMines() << "  Infected: " << getPlayer()->getInfection();
	string s = oss.str();
	setGameStatText(s);
	int size = sizeOf();
	m_player->doSomething();
	for (int k = 0; k < size; k++)
	{
		if (actorList[k]->isAlive())
		{
			
			actorList[k]->doSomething();
			
			if (!m_player->isAlive())
			{
				decLives();
				playSound(SOUND_PLAYER_DIE);
				return GWSTATUS_PLAYER_DIED;
			}

			if (m_player->completionCheck())
			{
				playSound(SOUND_LEVEL_FINISHED);
				return GWSTATUS_FINISHED_LEVEL;
			}
		}
	}

	for (std::vector<Actor*>::iterator it = actorList.begin(); it != actorList.end();)
	{
		if (!((*it)->isAlive()))
		{
			delete (*it);
			it = actorList.erase(it);
		}
		else
		{
			it++;
		}
	}

	//update the game status line
	return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
	for (std::vector<Actor*>::iterator it = actorList.begin(); it != actorList.end();)
	{
		delete (*it);
		it = actorList.erase(it);
	}
	//actorList.clear();
	cerr << actorList.size() << endl;
	if(m_player != nullptr)
		delete m_player;
	m_player = nullptr;
}
