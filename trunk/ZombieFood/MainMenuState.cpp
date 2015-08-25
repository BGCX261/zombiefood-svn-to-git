#include "IntroState.h"
#include "MainMenuState.h"
#include "InstructionState.h"
#include "HighscoreState.h"
#include "CreditsState.h"
#include "ZFGameState.h"
#include "WorldMapState.h"
#include "CurrentMapState.h"


MainMenuState MainMenuState::mMainMenuState;

//declaring the id for the buttons in the main menu
//SA IntroState.cpp
enum
{

	MENUSCREEN_ID_START_BUTTON = 1002,
	MENUSCREEN_ID_INSTRUCTION_BUTTON = 1003,
	MENUSCREEN_ID_HIGHSCORE_BUTTON = 1004,
	MENUSCREEN_ID_CREDITS_BUTTON = 1005,
	MENUSCREEN_ID_QUIT_BUTTON = 1006
};

void MainMenuState::enter()
{
	m_bEndState = false;

	m_VideoDriver = theDevice->getVideoDriver();
	m_SceneManager = theDevice->getSceneManager();
	m_GUIEnv = theDevice->getGUIEnvironment();
	theEventReceiver.Initialise();
	theDevice->setEventReceiver(&theEventReceiver);//(MyEventReceiver*) theDevice->getEventReceiver();                          //int width = 600; int height = 480;
	m_GUIEnv->getSkin()->setFont(m_GUIEnv->getFont("../../media/fonthaettenschweiler.bmp"));

	///Change the button colour to transparent (alpha channel)
	m_GUIEnv->getSkin()->setColor((EGUI_DEFAULT_COLOR)0, irr::video::SColor(0,0,0,0));
	m_GUIEnv->getSkin()->setColor((EGUI_DEFAULT_COLOR)1, irr::video::SColor(0,0,0,0));
	m_GUIEnv->getSkin()->setColor((EGUI_DEFAULT_COLOR)2, irr::video::SColor(0,0,0,0));
	m_GUIEnv->getSkin()->setColor((EGUI_DEFAULT_COLOR)3, irr::video::SColor(0,0,0,0));
	m_GUIEnv->getSkin()->setColor((EGUI_DEFAULT_COLOR)8, irr::video::SColor(255,120,120,120));


	//m_GUIEnv->addStaticText(L"THIS IS MAIN MENU SCREEN!", rect<s32>(10,10,260,22), true);
	///start button scale with screensize, ID: MENUSCREEN_ID_START_BUTTON
	m_GUIEnv->addButton(	rect<s32>(m_VideoDriver->getScreenSize().Width*0.8,		m_VideoDriver->getScreenSize().Height*0.4,		m_VideoDriver->getScreenSize().Width*0.8 + m_VideoDriver->getScreenSize().Width*0.116,		m_VideoDriver->getScreenSize().Height*0.4 + m_VideoDriver->getScreenSize().Height*0.066	),
							0,
							MENUSCREEN_ID_START_BUTTON,
							L"Start",
							L"Starts the game!");

	///instruction menu button scale with screensize, ID: MENUSCREEN_ID_INSTRUCTION_BUTTON
	m_GUIEnv->addButton(	rect<s32>(m_VideoDriver->getScreenSize().Width*0.8,		m_VideoDriver->getScreenSize().Height*0.5,		m_VideoDriver->getScreenSize().Width*0.8 + m_VideoDriver->getScreenSize().Width*0.116,		m_VideoDriver->getScreenSize().Height*0.5 + m_VideoDriver->getScreenSize().Height*0.066	), 
							0,
							MENUSCREEN_ID_INSTRUCTION_BUTTON,
							L"Instructions",
							L"Go to instruction page");

	///highscore button scale with screensize, ID: MENUSCREEN_ID_HIGHSCORE_BUTTON
	m_GUIEnv->addButton(	rect<s32>(m_VideoDriver->getScreenSize().Width*0.8,		m_VideoDriver->getScreenSize().Height*0.6,		m_VideoDriver->getScreenSize().Width*0.8+m_VideoDriver->getScreenSize().Width*0.116,		m_VideoDriver->getScreenSize().Height*0.6 + m_VideoDriver->getScreenSize().Height*0.066	),
							0, 
							MENUSCREEN_ID_HIGHSCORE_BUTTON,
							L"Highscore",
							L"Go to Highscore page");
	///credits button scale with screensize, ID: MENUSCREEN_ID_CREDITS_BUTTON
	m_GUIEnv->addButton(	rect<s32>(m_VideoDriver->getScreenSize().Width*0.8,		m_VideoDriver->getScreenSize().Height*0.7,		m_VideoDriver->getScreenSize().Width*0.8+m_VideoDriver->getScreenSize().Width*0.116,		m_VideoDriver->getScreenSize().Height*0.7 + m_VideoDriver->getScreenSize().Height*0.066	),
							0, 
							MENUSCREEN_ID_CREDITS_BUTTON,
							L"Credits",
							L"Roll credits");

	///quit button scale with screensize, ID: MENUSCREEN_ID_QUIT_BUTTON
	m_GUIEnv->addButton(	rect<s32>(m_VideoDriver->getScreenSize().Width*0.8,		m_VideoDriver->getScreenSize().Height*0.8,		m_VideoDriver->getScreenSize().Width*0.8+m_VideoDriver->getScreenSize().Width*0.116,		m_VideoDriver->getScreenSize().Height*0.8 + m_VideoDriver->getScreenSize().Height*0.066	),
							0, 
							MENUSCREEN_ID_QUIT_BUTTON,
							L"Quit",
							L"Exits program");


	///load the mesh of the zombie for mainmenu
	IAnimatedMesh* mesh = m_SceneManager->getMesh("../../media/sydney.md2");
	if (!mesh)
	{
		theDevice->drop();
		return;
	}
	///load the animation for the mesh
	IAnimatedMeshSceneNode* node = m_SceneManager->addAnimatedMeshSceneNode( mesh );
	if (node)
	{
		
		node->setMaterialFlag(EMF_LIGHTING, false);
		//node->setAnimationSpeed(0.01);
		node->setMD2Animation(scene::EMAT_STAND);
		//node->setMD2Animation(scene::EMAT_BOOM);
		//node->setMD2Animation(scene::EMAT_COUNT);
		node->setMaterialTexture( 0, m_VideoDriver->getTexture("../../media/sydney.bmp") );
	}



	///set camera position and lookat
	//m_SceneManager->addCameraSceneNode(0, vector3df(70,15,-20), vector3df(0,0,0));


	///set camera rotation and positon and lookat
	scene::ICameraSceneNode* cam = m_SceneManager->addCameraSceneNode(0, vector3df(70,15,-20), vector3df(0,5,0));
	//cam->setTarget(core::vector3df(0,0,0));
	scene::ISceneNodeAnimator* anim = m_SceneManager->createFlyCircleAnimator(core::vector3df(0,15,0), 50.0f);
	cam->addAnimator(anim);



	///while programme is running and quit is false draw the main menu-
	while( theDevice->run() && (m_bEndState == false) )
	{
		ProcessInput();

		m_VideoDriver->beginScene(true, true, SColor(255,70,50,50));

		m_SceneManager->drawAll();
		m_GUIEnv->drawAll();

		m_VideoDriver->endScene();

	}
	//GameManager::setNextState( NULL );

}

void MainMenuState::exit()
{
	theDevice->setEventReceiver(0);

	m_GUIEnv->clear();
	m_GUIEnv = NULL;

	m_SceneManager->clear();
	m_SceneManager = NULL;

	m_VideoDriver = NULL;
}

void MainMenuState::pause()
{
}

void MainMenuState::resume()
{
}

void MainMenuState::ProcessInput()
{
	///if user press enter key
	if(theEventReceiver.keyPressed(irr::KEY_ESCAPE))
	{
		m_bEndState = true;
		GameManager::setNextState( NULL );
	}

	///if user press start button with mouse
	if (theEventReceiver.IsButtonClicked())
	{
		if (theEventReceiver.GetButtonID() == MENUSCREEN_ID_START_BUTTON)
		{
			m_bEndState = true;
			GameManager::setNextState( ZFGameState::getInstance() );
		}	

		///if user press instruction button with mouse
		else if (theEventReceiver.GetButtonID() == MENUSCREEN_ID_INSTRUCTION_BUTTON)
		{
			m_bEndState = true;
			GameManager::setNextState( InstructionState::getInstance() );
		}

		///if user press highscore button with mouse
		else if (theEventReceiver.GetButtonID() == MENUSCREEN_ID_HIGHSCORE_BUTTON)
		{
			m_bEndState = true;
			GameManager::setNextState( HighscoreState::getInstance() );
		}
	
		///if user press credits button with mouse
		else if (theEventReceiver.GetButtonID() == MENUSCREEN_ID_CREDITS_BUTTON)
		{
			m_bEndState = true;
			GameManager::setNextState( CreditsState::getInstance() );
		}

		///if user press quit button with mouse
		else if (theEventReceiver.GetButtonID() == MENUSCREEN_ID_QUIT_BUTTON)
		{
			m_bEndState = true;
			GameManager::setNextState( NULL );
		}


	}
}
