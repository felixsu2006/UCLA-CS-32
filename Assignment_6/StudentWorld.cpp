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

bool StudentWorld::actorExist(double x, double y) //determines if an actor exists on this panel
{
	for (int k = 0; k < sizeOf(); k++)
	{
		if (actorList[k]->getX() + SPRITE_WIDTH - 1 >= x && actorList[k]->getX() - SPRITE_WIDTH + 1 <= x && actorList[k]->getY() + SPRITE_HEIGHT - 1 >= y && actorList[k]->getY() - SPRITE_HEIGHT + 1 <= y)
			return true;
	}
	return false;
}

int StudentWorld::sizeOf()
{
	return actorList.size();
}
int StudentWorld::init()
{
	Level lev(assetPath());
	Level::LoadResult result = lev.loadLevel("level01.txt");
	if (result == Level::load_fail_file_not_found)
		cerr << "Cannot find level01.txt data file" << endl;
	else if (result == Level::load_fail_bad_format)
		cerr << "Your level was improperly formatted" << endl;
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
	for (int k = 0; k < sizeOf(); k++)
	{
		if (actorList[k]->isAlive())
		{
			actorList[k]->doSomething();
			m_player->doSomething();
		}
	}
	return GWSTATUS_PLAYER_DIED;
	//return GWSTATUS_CONTINUE_GAME;
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
	delete m_player;
}
