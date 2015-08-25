#ifndef WorldMapState_H
#define WorldMapState_H

#include "GameState.h"
#include "MyEventReceiver.h"

class WorldMapState : public GameState
{
public:
	void enter();
	void exit();

	void pause();
	void resume();

	void ProcessInput();

	static WorldMapState* getInstance() { return &mWorldMapState; }
protected:
	WorldMapState() { }

private:
	static WorldMapState mWorldMapState;

	MyEventReceiver theEventReceiver;

};

#endif