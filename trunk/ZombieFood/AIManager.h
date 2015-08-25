#pragma once

#include <irrlicht.h>

using namespace irr;
using namespace irr::scene;

#include "AIObject.h"

class AIManager
{
public:
	AIManager(void);
	~AIManager(void);

	// Initialise the AI Manager
	bool Initialise(irr::scene::ISceneManager* m_SceneManager);
	// Add an AI Object
	bool AddAIObject(const irr::io::path &filename);
	// Run through all the AI objects available
	void run(void);
private:
	// Handler to the scene manager
	irr::scene::ISceneManager* m_SceneManager;
	irr::core::array<AIObject*> theAIObjectList;
};
