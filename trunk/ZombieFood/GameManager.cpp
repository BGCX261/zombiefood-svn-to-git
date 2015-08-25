#include "GameManager.h"
#include "GameState.h"
#include <cassert>

GameManager* ms_Singleton = 0;
GameState* m_NextState = 0;
int width = 1200;
int height = 900;
GameManager::GameManager()
{
	device = NULL;
	driver = NULL;
	smgr   = NULL;
	guienv = NULL;

	m_bContinue = true;
	m_NextState = NULL;
}

GameManager::~GameManager()
{
	// clean up all the states
	while (!mStates.empty()) {
		mStates.back()->exit();
		mStates.pop_back();
	}

	device->drop();
}

bool GameManager::initialise(void)
{
	// Initialise the GUI.
	device = createDevice( video::EDT_OPENGL, dimension2d<u32>(width, height), 16, false, false, false, 0);
	if (!device)
		return false;

	device->setWindowCaption(L"Zombie Food");

	return true;
}

void GameManager::start()//GameState* state)
{
	if (!configure()) 
		return;	
        
	setupResources();

	while (m_bContinue)
	{
		if (m_NextState != NULL)
		{
			m_NextState->setDevice( device );
			changeState(m_NextState);
		}
		else
			m_bContinue = false;
	}
}

void GameManager::setNextState(GameState* state)
{
	m_NextState = state;
}

void GameManager::changeState(GameState* state)
{
	// cleanup the current state
	if ( !mStates.empty() ) {
		mStates.back()->exit();
		mStates.pop_back();
	}

	// store and init the new state
	mStates.push_back(state);
	mStates.back()->enter();
}

void GameManager::pushState(GameState* state)
{
	// pause current state
	if ( !mStates.empty() ) {
		mStates.back()->pause();
	}

	// store and init the new state
	mStates.push_back(state);
	mStates.back()->enter();
}

void GameManager::popState()
{
	// cleanup the current state
	if ( !mStates.empty() ) {
		mStates.back()->exit();
		mStates.pop_back();
	}

	// resume previous state
	if ( !mStates.empty() ) {
		mStates.back()->resume();
	}
}

void GameManager::setupResources(void)
{
	/*
	// load resource paths from config file
	ConfigFile cf;
	cf.load("resources.cfg");

	// go through all settings in the file
	ConfigFile::SectionIterator seci = cf.getSectionIterator();

	String secName, typeName, archName;
	while (seci.hasMoreElements())
	{
		secName = seci.peekNextKey();
		ConfigFile::SettingsMultiMap *settings = seci.getNext();
		ConfigFile::SettingsMultiMap::iterator i;
		for (i = settings->begin() ; i != settings->end() ; ++i)
		{
			typeName = i->first;
			archName = i->second;
			ResourceGroupManager::getSingleton().addResourceLocation(
				archName, typeName, secName);
		}
	}
	*/
}

bool GameManager::configure(void)
{
	/*
	// load config settings from ogre.cfg
	if (!mRoot->restoreConfig())
	{
		// if there is no config file, show the configuration dialog
		if (!mRoot->showConfigDialog())
		{
			return false;
		}
	}
	*/

	// initialise and create a default rendering window
	//mRenderWindow = mRoot->initialise(true);


	return true;
}

GameManager* GameManager::getSingletonPtr(void)
{
	return ms_Singleton;
}

GameManager& GameManager::getSingleton(void)
{  
	assert(ms_Singleton);
	return *ms_Singleton;
}
