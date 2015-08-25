#ifndef GameManager_H
#define GameManager_H

#include <vector>
#include <irrlicht.h>

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

class GameState;

class GameManager
{
public:
	GameManager();
	~GameManager();
	bool initialise(void);
	void start();//GameState* state);

	static void setNextState(GameState* state);
	void changeState(GameState* state);
	void pushState(GameState* state);
	void popState();
	static GameManager& getSingleton(void);
	static GameManager* getSingletonPtr(void);

protected:
	IrrlichtDevice *device;
	IVideoDriver* driver;
	ISceneManager* smgr;
	IGUIEnvironment* guienv;

	void setupResources(void);
	bool configure(void);

	bool m_bContinue;

private:
	std::vector<GameState*> mStates;
};

#endif