#include "IntroState.h"
#include "MainMenuState.h"
#include "InstructionState.h"
#include "HighscoreState.h"
#include "CreditsState.h"
#include "ZFGameState.h"
#include "WorldMapState.h"
#include "CurrentMapState.h"


WorldMapState WorldMapState::mWorldMapState;
enum
{
	WORLDMAP_ID_BACK_BUTTON = 1010
};
void WorldMapState::enter()
{

;
	m_bEndState = false;

	m_VideoDriver = theDevice->getVideoDriver();
	m_SceneManager = theDevice->getSceneManager();
	m_GUIEnv = theDevice->getGUIEnvironment();
	theEventReceiver.Initialise();
	theDevice->setEventReceiver(&theEventReceiver);



       


	IGUIImage* map = m_GUIEnv->addImage(m_VideoDriver->getTexture("../../media/Last Stand 2 2Dmap1.png"),core::position2d<s32>(0,5)); //2d texture UI

	//m_GUIEnv->addStaticText(L"THIS IS WorldMap PAGE!!", rect<s32>(10,10,260,22), false);



					m_GUIEnv->addStaticText(L"Please close me",
						rect<s32>(35,35,140,50),
						true, // border?
						false, // wordwrap?
						map);

	m_GUIEnv->addButton(rect<s32>(250,400,250+100,400 + 30), map, WORLDMAP_ID_BACK_BUTTON,L"Back", L"Back to game");

	m_SceneManager->addCameraSceneNode(0, vector3df(0,30,-40), vector3df(0,5,0));

	while( theDevice->run() && (m_bEndState == false) )
	{

		ProcessInput();

		m_VideoDriver->beginScene(true, true, SColor(100,222,222,222));//(a,r,g,b)

		m_SceneManager->drawAll();
		m_GUIEnv->drawAll();

		m_VideoDriver->endScene();

	}

	GameManager::setNextState( ZFGameState::getInstance() );
	
}

void WorldMapState::exit()
{
	theDevice->setEventReceiver(0);

	m_GUIEnv->clear();
	m_GUIEnv = NULL;

	m_SceneManager->clear();
	m_SceneManager = NULL;

	m_VideoDriver = NULL;
}

void WorldMapState::pause()
{
}

void WorldMapState::resume()
{
}

void WorldMapState::ProcessInput()
{
	if(theEventReceiver.keyPressed(irr::KEY_ESCAPE))
	{
		m_bEndState = true;
		//GameManager::setNextState( ZFGameState::getInstance() );
	}
	if (theEventReceiver.IsButtonClicked())
	{
		if (theEventReceiver.GetButtonID() == WORLDMAP_ID_BACK_BUTTON)
			m_bEndState = true;
		//GameManager::setNextState( ZFGameState::getInstance() );
	}
}