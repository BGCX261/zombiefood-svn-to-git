#include "IntroState.h"
#include "MainMenuState.h"
#include "InstructionState.h"
#include "HighscoreState.h"
#include "CreditsState.h"
#include "ZFGameState.h"
#include "WorldMapState.h"
#include "CurrentMapState.h"
#include "Q3Player.h"

IntroState IntroState::mIntroState;

// Define some values that we'll use to identify individual IntroScreen controls.
enum
{
	INTROSCREEN_ID_CONTINUE_BUTTON = 1001
};

void IntroState::enter()
{
	m_bEndState = false;

	m_VideoDriver = theDevice->getVideoDriver();
	m_SceneManager = theDevice->getSceneManager();
	m_GUIEnv = theDevice->getGUIEnvironment();
	theEventReceiver.Initialise();
	theDevice->setEventReceiver(&theEventReceiver);
	m_GUIEnv->getSkin()->setFont(m_GUIEnv->getFont("../../media/fonthaettenschweiler.bmp"));

    video::ITexture* images = m_VideoDriver->getTexture("../../media/zombiefood.png"); //method 1
    m_VideoDriver->makeColorKeyTexture(images, core::position2d<s32>(0,0));

	//method 2
//	m_VideoDriver->draw2DImage(m_VideoDriver->getTexture("../../media/zombiefood.png"), core::rect<s32>(10,10,108,108),	core::rect<s32>(10,10,120,120));

	//method 3
	//m_GUIEnv->addImage(m_VideoDriver->getTexture("../../media/zombiefood.png"),core::position2d<s32>(0,0)); //2d texture UI


	//m_GUIEnv->addStaticText(	L"THIS IS INTRODUCTION SCREEN!!", 
	//							rect<s32>(10,10,260,22), 
	//							true);
	//adding button to intro screen, made the button scale according to screen size with getScreenSize
	m_GUIEnv->addButton(	rect<s32>( m_VideoDriver->getScreenSize().Width*0.35 , m_VideoDriver->getScreenSize().Height*0.85 , m_VideoDriver->getScreenSize().Width*0.35+m_VideoDriver->getScreenSize().Width*0.33		 ,		m_VideoDriver->getScreenSize().Height*0.85 + m_VideoDriver->getScreenSize().Height*0.065),
							0, 
							INTROSCREEN_ID_CONTINUE_BUTTON,
							L"Press this button to continue ...", 
							L"continue to main menu");

	m_SceneManager->addCameraSceneNode(	0, 
										vector3df(0,30,-40), 
										vector3df(0,5,0));

	while( theDevice->run() && (m_bEndState == false) )
	{
		ProcessInput();

		m_VideoDriver->beginScene(true, true, SColor(100,100,100,100));//(a,r,g,b)
		//m_VideoDriver->getScreenSize().Height;
		//m_VideoDriver->getScreenSize().Width;

		m_VideoDriver->draw2DImage(images, core::position2d<s32>(0,0),
		core::rect<s32>(0,0,m_VideoDriver->getScreenSize().Width,m_VideoDriver->getScreenSize().Height));//, 0, video::SColor(255,255,255,255), true);

		m_SceneManager->drawAll();
		m_GUIEnv->drawAll();

		m_VideoDriver->endScene();

	}

	GameManager::setNextState( MainMenuState::getInstance() );
}

void IntroState::exit()
{
	theDevice->setEventReceiver(0);

	m_GUIEnv->clear();
	m_GUIEnv = NULL;

	m_SceneManager->clear();
	m_SceneManager = NULL;

	m_VideoDriver = NULL;
}

void IntroState::pause()
{
}

void IntroState::resume()
{
}

void IntroState::ProcessInput()
{
	if(theEventReceiver.keyPressed(irr::KEY_RETURN))
	{
		//m_bEndState = true;
	}
	if (theEventReceiver.IsButtonClicked())
	{
		if (theEventReceiver.GetButtonID() == INTROSCREEN_ID_CONTINUE_BUTTON)
			m_bEndState = true;
	}
}
