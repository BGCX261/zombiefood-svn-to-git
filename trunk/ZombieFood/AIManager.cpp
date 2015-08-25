#include "AIManager.h"

using namespace irr;
using namespace irr::core;
using namespace irr::video;

AIManager::AIManager(void)
: m_SceneManager(NULL)
{
	theAIObjectList.clear();
}

AIManager::~AIManager(void)
{
	for (u32 i=0; i < theAIObjectList.size(); ++i)
	{
		delete ((AIObject*)theAIObjectList[i]);
	}

	theAIObjectList.clear();
	m_SceneManager = NULL;
}

// Initialise the AI Manager
bool AIManager::Initialise(irr::scene::ISceneManager* m_SceneManager)
{
	this->m_SceneManager = m_SceneManager;

	if (this->m_SceneManager == NULL)
		return false;
	else
		return true;
}

// Add an AI Object
bool AIManager::AddAIObject(const irr::io::path &filename)
{

	scene::IAnimatedMesh* mesh = m_SceneManager->getMesh("../../media/sydney.md2");

	if (!mesh)
		return false;

	//load the animation for the mesh
	AIObject* anAIObject = new AIObject();
	anAIObject->SetAIObject(	m_SceneManager->addAnimatedMeshSceneNode( mesh,
																		  0, 
																		  10, 
																		  vector3df( 0, 0, 200), 
																		  vector3df(0,0,0) ) );

	theAIObjectList.push_back( anAIObject );

	return true;
}

// Run through all the AI objects available
void AIManager::run(void)
{
	AIObject* anAIObject = NULL;
	
	for (u32 i=0; i < theAIObjectList.size(); ++i)
	{
		anAIObject = (AIObject*)theAIObjectList[i];
		
		anAIObject->Move();
	}
}
