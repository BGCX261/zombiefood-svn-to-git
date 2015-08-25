#include "IntroState.h"
#include "MainMenuState.h"
#include "InstructionState.h"
#include "HighscoreState.h"
#include "CreditsState.h"
#include "ZFGameState.h"
#include "WorldMapState.h"
#include "CurrentMapState.h"
#include "Q3Player.h"

CreditsState CreditsState::mCreditsState;

void CreditsState::enter()
{

	m_bEndState = false;

	m_VideoDriver = theDevice->getVideoDriver();
	m_SceneManager = theDevice->getSceneManager();
	m_GUIEnv = theDevice->getGUIEnvironment();
	theEventReceiver.Initialise();
	theDevice->setEventReceiver(&theEventReceiver);


	m_GUIEnv->addImage(m_VideoDriver->getTexture("../../media/credits.jpg"),core::position2d<s32>(0,0)); //2d texture UI

	//m_GUIEnv->addStaticText(L"THIS IS Credits PAGE!!", rect<s32>(10,10,260,22), true);

	//m_GUIEnv->addButton(rect<s32>(190,350,190+200,350 + 30), 0, true,L"Back", L"Back to main menu");

	m_SceneManager->addCameraSceneNode(0, vector3df(0,30,-40), vector3df(0,5,0));

	while( theDevice->run() && (m_bEndState == false) )
	{
		ProcessInput();

		m_VideoDriver->beginScene(true, true, SColor(100,22,0,50));//(a,r,g,b)

		m_SceneManager->drawAll();
		m_GUIEnv->drawAll();

		m_VideoDriver->endScene();

	}

	GameManager::setNextState( MainMenuState::getInstance() );
	
}

void CreditsState::exit()
{
	theDevice->setEventReceiver(0);

	m_GUIEnv->clear();
	m_GUIEnv = NULL;

	m_SceneManager->clear();
	m_SceneManager = NULL;

	m_VideoDriver = NULL;
}

void CreditsState::pause()
{
}

void CreditsState::resume()
{
}

void CreditsState::ProcessInput()
{
	if(theEventReceiver.keyPressed(irr::KEY_ESCAPE))
	{
		m_bEndState = true;
		GameManager::setNextState( MainMenuState::getInstance() );
	}
}