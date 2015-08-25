#ifndef IntroState_H
#define IntroState_H

#include "GameState.h"
#include "MyEventReceiver.h"

class IntroState : public GameState
{
public:
	void enter();
	void exit();

	void pause();
	void resume();

	void ProcessInput();

	static IntroState* getInstance() { return &mIntroState; }
protected:
	IntroState() { }

private:
	static IntroState mIntroState;

	MyEventReceiver theEventReceiver;
};

#endif