#ifndef CreditsState_H
#define CreditsState_H

#include "GameState.h"
#include "MyEventReceiver.h"

class CreditsState : public GameState
{
public:
	void enter();
	void exit();

	void pause();
	void resume();

	void ProcessInput();

	static CreditsState* getInstance() { return &mCreditsState; }
protected:
	CreditsState() { }

private:
	static CreditsState mCreditsState;

	MyEventReceiver theEventReceiver;

};

#endif