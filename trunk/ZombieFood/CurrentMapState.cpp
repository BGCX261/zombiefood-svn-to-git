#include "IntroState.h"
#include "MainMenuState.h"
#include "InstructionState.h"
#include "HighscoreState.h"
#include "CreditsState.h"
#include "ZFGameState.h"
#include "WorldMapState.h"
#include "CurrentMapState.h"
#include "Q3Player.h"

int TotalHours = 12;
int HoursRemaining, RepairHours = 0, SearchHours = 0;
bool shit;
CurrentMapState CurrentMapState::mCurrentMapState;
enum
{

	CURRENTMAP_ID_ACCEPT_BUTTON = 1011,
	CURRENTMAP_ID_SEARCHPLUS_BUTTON = 1012,
	CURRENTMAP_ID_SEARCHMINUS_BUTTON = 1013,
	CURRENTMAP_ID_REPAIRPLUS_BUTTON = 1014,
	CURRENTMAP_ID_REPAIRMINUS_BUTTON = 1015

};

void CurrentMapState::enter()
{

	m_bEndState = false;

	m_VideoDriver = theDevice->getVideoDriver();
	m_SceneManager = theDevice->getSceneManager();
	m_GUIEnv = theDevice->getGUIEnvironment();
	theEventReceiver.Initialise();
	theDevice->setEventReceiver(&theEventReceiver);

	



//	m_GUIEnv->addStaticText(L"THIS IS CurrentMap PAGE!!", rect<s32>(10,10,260,22), true);
 
		int SurvivorsFound = rand()%3;
		int AmmoFoodFound = rand()%3;

	m_SceneManager->addCameraSceneNode(0, vector3df(0,30,-40), vector3df(0,5,0));

	while( theDevice->run() && (m_bEndState == false) )
	{

		// Reset the theEventReceiver
		theEventReceiver.endEventProcess();

		//if (RepairHours>0 && RepairHours<12 && SearchHours>0 && SearchHours <12)
		//{
		HoursRemaining = TotalHours - RepairHours -SearchHours;
		//}



		char HR_HUD[128];
		char RH_HUD[128];
		char SH_HUD[128];
		char TH_HUD[128];
		sprintf_s(HR_HUD, "Hours Remaining: \n\n        %d", HoursRemaining);
		sprintf_s(RH_HUD, "Repair Hours: \n\n        %d", RepairHours);
		sprintf_s(SH_HUD, "Search Hours: \n\n        %d", SearchHours);
		sprintf_s(TH_HUD, "Total Hours Available: \n\n        %d", TotalHours);
		//sprintf_s(ammoHUD, "Hours Remaining: %d \n", RepairHours);
		//sprintf_s(ammoHUD, "Hours Remaining: %d \n", SearchHours);
		// Convert to a wchar_t*
		size_t origsize = strlen(HR_HUD) + 3;
		const size_t newsize = 255;
		size_t convertedChars = 0;
		wchar_t wcstring[newsize];
		mbstowcs_s(&convertedChars, wcstring, origsize, HR_HUD, _TRUNCATE);

		size_t RH_origsize = strlen(RH_HUD) + 3;
		//const size_t newsize = 255;
		//size_t convertedChars = 0;
		wchar_t RH_wcstring[newsize];
		mbstowcs_s(&convertedChars, RH_wcstring, RH_origsize, RH_HUD, _TRUNCATE);

		size_t SH_origsize = strlen(SH_HUD) + 3;
		//const size_t newsize = 255;
		//size_t convertedChars = 0;
		wchar_t SH_wcstring[newsize];
		mbstowcs_s(&convertedChars, SH_wcstring, SH_origsize, SH_HUD, _TRUNCATE);

		size_t TH_origsize = strlen(TH_HUD) + 3;
		//const size_t newsize = 255;
		//size_t convertedChars = 0;
		wchar_t TH_wcstring[newsize];
		mbstowcs_s(&convertedChars, TH_wcstring, TH_origsize, TH_HUD, _TRUNCATE);

		m_GUIEnv->clear();
			m_GUIEnv->addImage(m_VideoDriver->getTexture("../../media/map1.jpg"),core::position2d<s32>(0,0)); //2d texture UI
		m_GUIEnv->addStaticText(wcstring, rect<s32>(900,190,1100,400), true);
		m_GUIEnv->addStaticText(RH_wcstring, rect<s32>(900,460,1100,850), true);
		m_GUIEnv->addStaticText(SH_wcstring, rect<s32>(900,330,1100,650), true);
		m_GUIEnv->addStaticText(TH_wcstring, rect<s32>(900,50,1200,300), true);



		if(shit)
		{

		
		int AmmountRepaired = RepairHours*10;


		char ThH_HUD[128];
		sprintf_s(ThH_HUD, "Survivors found: %d \nAmmo and Food Supplies found: %d \nBarricade health repaired: %d", SurvivorsFound, AmmoFoodFound, AmmountRepaired);
		size_t ThH_origsize = strlen(ThH_HUD) + 3;
		//const size_t newsize = 255;
		//size_t convertedChars = 0;
		wchar_t ThH_wcstring[newsize];
		mbstowcs_s(&convertedChars, ThH_wcstring, ThH_origsize, ThH_HUD, _TRUNCATE);
		m_GUIEnv->addStaticText(ThH_wcstring, rect<s32>(810,650,1200,800), true);
		}
		

	m_GUIEnv->addButton(rect<s32>(400,600,700,900), 0, CURRENTMAP_ID_ACCEPT_BUTTON,L"Press Enter to accept ");
	

	//m_GUIEnv->addButton(rect<s32>(350,110,350+200,110 + 30), 0, CURRENTMAP_ID_SEARCHPLUS_BUTTON,L">", L"Increase searching time");
	//m_GUIEnv->addButton(rect<s32>(200,110,200+200,110 + 30), 0, CURRENTMAP_ID_SEARCHMINUS_BUTTON,L"<", L"Decrease searching time");

	//m_GUIEnv->addButton(rect<s32>(350,220,350+200,220 + 30), 0, CURRENTMAP_ID_REPAIRPLUS_BUTTON,L">>", L"Increase repairing time");
	//m_GUIEnv->addButton(rect<s32>(200,220,200+200,220 + 30), 0, CURRENTMAP_ID_REPAIRMINUS_BUTTON,L"<<", L"Decrease repairing time");



		ProcessInput();
		m_VideoDriver->beginScene(true, true, SColor(100,222,222,222));//(a,r,g,b)
		m_SceneManager->drawAll();
		m_GUIEnv->drawAll();
		m_VideoDriver->endScene();

		// Start the theEventReceiver
		theEventReceiver.startEventProcess();



	}

	GameManager::setNextState( ZFGameState::getInstance() );
	
}

void CurrentMapState::exit()
{
	theDevice->setEventReceiver(0);

	m_GUIEnv->clear();
	m_GUIEnv = NULL;

	m_SceneManager->clear();
	m_SceneManager = NULL;

	m_VideoDriver = NULL;
	shit = false;
}

void CurrentMapState::pause()
{
}

void CurrentMapState::resume()
{
}

void CurrentMapState::ProcessInput()
{
	if(theEventReceiver.keyPressed(irr::KEY_ESCAPE))
	{
		m_bEndState = true;
		//GameManager::setNextState( ZFGameState::getInstance() );
	}

		if(theEventReceiver.keyPressed(irr::KEY_RIGHT) && HoursRemaining >0 && SearchHours<12)
	{
		SearchHours++;

	}
	if(theEventReceiver.keyPressed(irr::KEY_LEFT)&& HoursRemaining <12 && SearchHours>0)
	{
		SearchHours--;

	}

	if(theEventReceiver.keyPressed(irr::KEY_UP)&& HoursRemaining >0 && RepairHours<12)
	{
		RepairHours++;

	}
	if(theEventReceiver.keyPressed(irr::KEY_DOWN)&& HoursRemaining <12 && RepairHours>0)
	{
		RepairHours--;

	}
		if(theEventReceiver.keyPressed(irr::KEY_RETURN) && HoursRemaining == 0)
	{
shit = true;
		
	}


	/////////////////////////////////////////////////////////////////////////////////////////////
	//	if (theEventReceiver.IsButtonClicked())
	//{
	//	if (theEventReceiver.GetButtonID() == CURRENTMAP_ID_ACCEPT_BUTTON)
	//	{
	//		m_bEndState = true;
	//		//GameManager::setNextState( ZFGameState::getInstance() );
	//	}

	//	if (theEventReceiver.GetButtonID() == CURRENTMAP_ID_SEARCHPLUS_BUTTON)
	//	{
	//		SearchHours++;	
	//	}

	//	if (theEventReceiver.GetButtonID() == CURRENTMAP_ID_SEARCHMINUS_BUTTON)
	//	{
	//		SearchHours--;			
	//	}

	//	if (theEventReceiver.GetButtonID() == CURRENTMAP_ID_REPAIRPLUS_BUTTON)
	//	{
	//		RepairHours++;
	//	}

	//	if (theEventReceiver.GetButtonID() == CURRENTMAP_ID_REPAIRMINUS_BUTTON)
	//	{
	//		RepairHours--;	
	//	}
	//}
	/////////////////////////////////////////////////////////////////////////////////////////////	

}