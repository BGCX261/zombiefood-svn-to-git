#pragma once
#include "GameState.h"
#include "MyEventReceiver.h"

class MainMenuState :
	public GameState
{
public:
	void enter();
	void exit();

	void pause();
	void resume();

	void ProcessInput();

	static MainMenuState* getInstance() { return &mMainMenuState; }
protected:
	MainMenuState() { }

private:
	static MainMenuState mMainMenuState;

	MyEventReceiver theEventReceiver;
};
