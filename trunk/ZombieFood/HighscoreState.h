#ifndef HighscoreState_H
#define HighscoreState_H

#include "GameState.h"
#include "MyEventReceiver.h"

class HighscoreState : public GameState
{
public:
	void enter();
	void exit();

	void pause();
	void resume();

	void ProcessInput();

	static HighscoreState* getInstance() { return &mHighscoreState; }
protected:
	HighscoreState() { }

private:
	static HighscoreState mHighscoreState;

	MyEventReceiver theEventReceiver;
};

#endif