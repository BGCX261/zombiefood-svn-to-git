#ifndef CurrentMapState_H
#define CurrentMapState_H

#include "GameState.h"
#include "MyEventReceiver.h"

class CurrentMapState : public GameState
{
public:
	void enter();
	void exit();

	void pause();
	void resume();

	void ProcessInput();

	static CurrentMapState* getInstance() { return &mCurrentMapState; }
protected:
	CurrentMapState() { }

private:
	static CurrentMapState mCurrentMapState;

	MyEventReceiver theEventReceiver;

};

#endif