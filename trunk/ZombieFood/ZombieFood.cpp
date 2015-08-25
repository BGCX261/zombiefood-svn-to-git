#include "GameManager.h"
#include "IntroState.h"
#include "Q3Player.h"

int main()
{
	GameManager* game = new GameManager();

	if (game->initialise() == false)
		return 0;

	// initialize the game and switch to the first state
	game->setNextState(IntroState::getInstance());
	game->start();

	delete game;

	return 0;
}
