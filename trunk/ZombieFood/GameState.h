#pragma once

//#include <Ogre.h>
//#include <OIS/OIS.h>
//#include <CEGUI/CEGUI.h>
//#include <CEGUI/RendererModules/Ogre/CEGUIOgreRenderer.h>

#include "GameManager.h"
#include <irrlicht.h>



class GameState
{
public:
	virtual void enter() = 0;
	virtual void exit() = 0;

	virtual void pause() = 0;
	virtual void resume() = 0;
	virtual void ProcessInput() = 0;

	void setDevice( IrrlichtDevice *device ) { theDevice = device; }

	void changeState(GameState* state) { GameManager::getSingletonPtr()->changeState(state); }
	void pushState(GameState* state) { GameManager::getSingletonPtr()->pushState(state); }
	void popState() { GameManager::getSingletonPtr()->popState(); }
protected:
	GameState() { }
	
	
	IVideoDriver* m_VideoDriver;
	ISceneManager* m_SceneManager;
	IGUIEnvironment* m_GUIEnv;

	IrrlichtDevice *theDevice;
	bool m_bEndState;
};
