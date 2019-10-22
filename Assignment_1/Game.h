
#ifndef GAME_INCLUDED
#define GAME_INCLUDED

class Arena;

int decodeDirection(char dir);

class Game
{
public:
	// Constructor/destructor
	Game(int rows, int cols, int nZombies);
	~Game();

	// Mutators
	void play();

private:
	Arena* m_arena;
};

#endif //GAME_INCLUDED