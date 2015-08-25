#ifndef InstructionState_H
#define InstructionState_H

#include "GameState.h"
#include "MyEventReceiver.h"

class InstructionState : public GameState
{
public:
	void enter();
	void exit();

	void pause();
	void resume();

	void ProcessInput();

	static InstructionState* getInstance() { return &mInstructionState; }
protected:
	InstructionState() { }

private:
	static InstructionState mInstructionState;

	MyEventReceiver theEventReceiver;
};

#endif