#include "IntroState.h"
#include "MainMenuState.h"
#include "InstructionState.h"
#include "HighscoreState.h"
#include "CreditsState.h"
#include "ZFGameState.h"
#include "WorldMapState.h"
#include "CurrentMapState.h"
#include "Q3Player.h"

ZFGameState ZFGameState::mZFGameState;
// check if zombie 1 and 2 is alive
bool alive,alive2,alive3,alive4,alive5;
// This is the movemen speed in units per second.
const f32 MOVEMENT_SPEED = 150.0f;
	int bullet = 200, clip = 5;

//declaring thae id for the buttons in the main menu
//SA IntroState.cpp, MainMenuState.cpp
enum
{

	INGAME_ID_MAP_BUTTON = 1007,
	INGAME_ID_WORLDMAP_BUTTON = 1008,
	INGAME_ID_MAINMENU_BUTTON = 1009

};

enum
{
	// I use this ISceneNode ID to indicate a scene node that is
	// not pickable by getSceneNodeAndCollisionPointFromRay()
	ID_IsNotPickable = 0,

	// I use this flag in ISceneNode IDs to indicate that the
	// scene node can be picked by ray selection.
	IDFlag_IsPickable = 1 << 0,

	// I use this flag in ISceneNode IDs to indicate that the
	// scene node can be highlighted.  In this example, the
	// homonids can be highlighted, but the level mesh can't.
	IDFlag_IsHighlightable = 1 << 1
};

void ZFGameState::enter()
{
		
	m_bEndState = false;

	m_VideoDriver = theDevice->getVideoDriver();
	m_SceneManager = theDevice->getSceneManager();
	m_GUIEnv = theDevice->getGUIEnvironment();
	theEventReceiver.Initialise();
	theDevice->setEventReceiver(&theEventReceiver);

	theAIManager = new AIManager();
	theAIManager->Initialise( m_SceneManager );



	///2d static text
	//m_GUIEnv->addStaticText(L"THIS IS GAME PAGE!!", rect<s32>(10,10,260,22), true);


	//m_GUIEnv->addButton(rect<s32>(300,350,300+60,350 + 30),
	//	0,
	//	INGAME_ID_MAP_BUTTON,
	//	L"Map",
	//	L"Shows the map of the place you are currently in");

	//m_GUIEnv->addButton(rect<s32>(450,350,450+60,350 + 30),
	//	0,
	//	INGAME_ID_WORLDMAP_BUTTON,
	//	L"WORLD MAP",
	//	L"Show the world map");

	//m_GUIEnv->addButton(rect<s32>(600,350,600+60,350 + 30),
	//	0,
	//	INGAME_ID_MAINMENU_BUTTON,
	//	L"Main menu",
	//	L"Back to main menu");


	///FPS CAMERA
	camera = m_SceneManager->addCameraSceneNodeFPS(0, 100.0f, .3f, 0, 0, 0, true, 3.f);
	camera->setPosition(core::vector3df(0,56.75,0));	
	camera->setTarget( camera->getPosition()+core::vector3df(0,0,1));

	/// disable mouse cursor
	//theDevice->getCursorControl()->setVisible(true);




	///loading the gun mesh
	IAnimatedMeshMD2* weaponMesh = (IAnimatedMeshMD2*) m_SceneManager->getMesh("../../media/gun.md2");
	if (!weaponMesh)
	{
		theDevice->drop();
		return;
	}
	///load the animation for the mesh
	IAnimatedMeshSceneNode* node = m_SceneManager->addAnimatedMeshSceneNode( weaponMesh,
		m_SceneManager->getActiveCamera(),
		10,
		vector3df( 0, 0, 0),
		vector3df(-90,-90,90)
		);
	//c8 animation[1];
	//set properties of the gun node
	node->setMaterialFlag(EMF_LIGHTING, false);
	node->setAnimationSpeed(20);
	node->setMaterialTexture(0, m_VideoDriver->getTexture( "../../media/gun.jpg"));
	
	//node->setName ( "tommi the gun man" );
	node->setMD2Animation("idle");
	//node->setFrameLoop(20,55);
	//node->setLoopMode ( false );



	//////////////////////////////////////////////////////////////////////////////////////
	// Zombie 1
	scene::IAnimatedMesh* mesh = m_SceneManager->getMesh("../../media/sydney.md2");
	if (!mesh)
	{
		theDevice->drop();
		return;
	}
	// load the animation for the mesh
	IAnimatedMeshSceneNode* anode = m_SceneManager->addAnimatedMeshSceneNode( mesh,
		0,
		10,
		vector3df( 0, 30, 400),
		vector3df(0,camera->getPosition().X+90,0)
		);

	alive = true;
	anode->setMaterialFlag(EMF_LIGHTING, false);
	anode->setAnimationSpeed(3);
	anode->setMD2Animation(scene::EMAT_RUN);
	//anode->setRotation(vector3df(0,-camera->getPosition().X,0));
	scene::ITriangleSelector * selector = m_SceneManager->createTriangleSelector(anode);
	anode->setMaterialTexture( 0, m_VideoDriver->getTexture("../../media/sydneyZ.bmp") );
    anode->setTriangleSelector(selector);
	selector->drop();
	///////////////////End of Zombie 1 declaration/////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////////////////
	// Zombie 2
	scene::IAnimatedMesh* mesh2 = m_SceneManager->getMesh("../../media/sydney.md2");
	if (!mesh2)
	{
		theDevice->drop();
		return;
	}
	IAnimatedMeshSceneNode* anode2 = m_SceneManager->addAnimatedMeshSceneNode( mesh2,
		0,
		10,
		vector3df( -120, 30, 400),
		vector3df(0,camera->getPosition().X+70,0)
		);	

	alive2 = true;
	anode2->setMaterialFlag(EMF_LIGHTING, false);
	anode2->setAnimationSpeed(3);
	anode2->setMD2Animation(scene::EMAT_RUN);
	//anode2->setRotation(vector3df(0,-camera->getPosition().X,0));
	scene::ITriangleSelector * selector2 = m_SceneManager->createTriangleSelector(anode2);
	anode2->setMaterialTexture( 0, m_VideoDriver->getTexture("../../media/sydneyZ.bmp") );
    anode2->setTriangleSelector(selector2);		
	selector2->drop();
	///////////////////End of Zombie 2 declaration/////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////////////////
	// Zombie 3
	scene::IAnimatedMesh* mesh3 = m_SceneManager->getMesh("../../media/ninja.b3d");
	if (!mesh3)
	{
		theDevice->drop();
		return;
	}
	IAnimatedMeshSceneNode* anode3 = m_SceneManager->addAnimatedMeshSceneNode( mesh3,
		0,
		10,
		vector3df( -50, 0, 600),
		vector3df(0,camera->getPosition().X+180,0)
		);	

	alive3 = true;
	anode3->setScale(vector3df(6,6,6));
	anode3->setMaterialFlag(EMF_LIGHTING, false);
	//anode3->setAnimationSpeed(3);
	anode3->setFrameLoop(0,13);
	scene::ITriangleSelector * selector3 = m_SceneManager->createTriangleSelector(anode3);
	anode3->setMaterialTexture( 0, m_VideoDriver->getTexture("../../media/copy of nskinrd.jpg") );
    anode3->setTriangleSelector(selector3);		
	selector3->drop();
	///////////////////End of Zombie 3 declaration/////////////////////////////////////////


	//////////////////////////////////////////////////////////////////////////////////////
	// Zombie 4
	scene::IAnimatedMesh* mesh4 = m_SceneManager->getMesh("../../media/sydney.md2");
	if (!mesh4)
	{
		theDevice->drop();
		return;
	}
	IAnimatedMeshSceneNode* anode4 = m_SceneManager->addAnimatedMeshSceneNode( mesh4,
		0,
		10,
		vector3df( 120, 30, 520),
		vector3df(0,camera->getPosition().X+110,0)
		);	

	alive4 = true;
	anode4->setMaterialFlag(EMF_LIGHTING, false);
	anode4->setAnimationSpeed(3);
	anode4->setMD2Animation(scene::EMAT_RUN);
	//anode2->setRotation(vector3df(0,-camera->getPosition().X,0));
	scene::ITriangleSelector * selector4 = m_SceneManager->createTriangleSelector(anode4);
	anode4->setMaterialTexture( 0, m_VideoDriver->getTexture("../../media/sydneyZ.bmp") );
    anode4->setTriangleSelector(selector4);		
	selector4->drop();
	///////////////////End of Zombie 4 declaration/////////////////////////////////////////

	//if ( theAIManager->AddAIObject("../../media/sydney.md2") == false )
	//{
	//}

	///loading the environment for level 1
	//m_SceneManager->loadScene("../../media/level1.irr");
	m_SceneManager->loadScene("../../media/test.irr");
	///triangle selector for collision detection
	scene::IMetaTriangleSelector * meta = m_SceneManager->createMetaTriangleSelector();

	/*
	Now we will find all the nodes in the scene and create triangle
	selectors for all suitable nodes.  Typically, you would want to make a
	more informed decision about which nodes to performs collision checks
	on; you could capture that information in the node name or Id.
	*/
	core::array<scene::ISceneNode *> nodes;
	m_SceneManager->getSceneNodesFromType(scene::ESNT_ANY, nodes); // Find all nodes

	for (u32 i=0; i < nodes.size(); ++i)
	{
		scene::ISceneNode * node = nodes[i];
		scene::ITriangleSelector * selector = 0;

		switch(node->getType())
		{
		case scene::ESNT_CUBE:
		case scene::ESNT_ANIMATED_MESH:
			// Because the selector won't animate with the mesh,
			// and is only being used for camera collision, we'll just use an approximate
			// bounding box instead of ((scene::IAnimatedMeshSceneNode*)node)->getMesh(0)
			node->setID( IDFlag_IsPickable | IDFlag_IsHighlightable);
			selector = m_SceneManager->createTriangleSelectorFromBoundingBox(node);
			break;

		case scene::ESNT_MESH:
		case scene::ESNT_SPHERE: // Derived from IMeshSceneNode
			node->setID( IDFlag_IsPickable );
			selector = m_SceneManager->createTriangleSelector(((scene::IMeshSceneNode*)node)->getMesh(), node);
			node->setTriangleSelector(selector);
			break;

		case scene::ESNT_TERRAIN:
			node->setID( IDFlag_IsPickable );
			selector = m_SceneManager->createTerrainTriangleSelector((scene::ITerrainSceneNode*)node);
			break;

		case scene::ESNT_OCTREE:
			node->setID( IDFlag_IsPickable | IDFlag_IsHighlightable);
			selector = m_SceneManager->createOctreeTriangleSelector(((scene::IMeshSceneNode*)node)->getMesh(), node);
			break;

		default:
			// Don't create a selector for this node type
			break;
		}

		if(selector)
		{
			// Add it to the meta selector, which will take a reference to it
			meta->addTriangleSelector(selector);
			// And drop my reference to it, so that the meta selector owns it.
			selector->drop();
		}
	}

	/*
	Now that the mesh scene nodes have had triangle selectors created and added
	to the meta selector, create a collision response animator from that meta selector.
	*/
	scene::ISceneNodeAnimator* anim = m_SceneManager->createCollisionResponseAnimator(meta, 
		camera,
		vector3df(30,10,30),
		vector3df( 0.0f, -90.0f, 0.0f ),
		vector3df(0,45,0),
		0.0f
		);
	meta->drop(); // I'm done with the meta selector now
	camera->addAnimator(anim);
	camera->addAnimator(anim); //setting the camera with the collision detection
	anim->drop(); // I'm done with the animator now

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Remember which scene node is highlighted
	scene::ISceneNode* highlightedSceneNode = 0;
	scene::ISceneCollisionManager* collMan = m_SceneManager->getSceneCollisionManager();

	// Now I create three animated characters which we can pick, a dynamic light for
	// lighting them, and a billboard for drawing where we found an intersection.

	// First, let's get rid of the mouse cursor.  We'll use a billboard to show
	// what we're looking at.
	theDevice->getCursorControl()->setVisible(false);

	// Add the billboard.
	//scene::IBillboardSceneNode * bill = m_SceneManager->addBillboardSceneNode();
	//bill->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR );
	//bill->setMaterialTexture(0, m_VideoDriver->getTexture("../../media/crosshair.png"));
	//bill->setMaterialFlag(video::EMF_LIGHTING, false);
	//bill->setMaterialFlag(video::EMF_ZBUFFER, false);
	//bill->setSize(core::dimension2d<f32>(10.0f, 20.0f));
	//bill->setID(ID_IsNotPickable); // This ensures that we don't accidentally ray-pick it

	video::SMaterial material;
	material.setTexture(0, 0);
	material.Lighting = false;
	// draw the selection triangle only as wireframe
	material.Wireframe=true;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// In order to do framerate independent movement, we have to know
	// how long it was since the last frame
	then = theDevice->getTimer()->getTime();
	
	while( theDevice->run() && (m_bEndState == false)  )
	{

		// Reset the theEventReceiver
		theEventReceiver.endEventProcess();

		int timeleft = 300-theDevice->getTimer()->getTime()/1000;
		
		if (timeleft<=0)
		{
			timeleft = 0;
			m_bEndState = true;
			GameManager::setNextState( MainMenuState::getInstance() );
		}


	int x = rand()%10-3;

	// timer hud, shows amount of timer left
	char TimerHUD[128];
	sprintf_s(TimerHUD, "Time left til dawn\n          %d ",timeleft );
	// Convert to a wchar_t*
	size_t TimerHUDsize = strlen(TimerHUD) + 3;
	const size_t newsize = 255;
	size_t convertedChars = 0;
	wchar_t wcTimerString[newsize];	
	mbstowcs_s(&convertedChars, wcTimerString, TimerHUDsize, TimerHUD, _TRUNCATE);

	// ammo hud, shows amount of ammunition left
	char ammoHUD[128];
	//sprintf_s(ammoHUD, "Ammo: %d/200 \n Clip: %d ", bullet, clip);
	sprintf_s(ammoHUD, ": %d  -  %d ", bullet, clip);
	// Convert to a wchar_t*
	size_t origsize = strlen(ammoHUD) + 3;
	wchar_t wcHUDString[newsize];
	mbstowcs_s(&convertedChars, wcHUDString, origsize, ammoHUD, _TRUNCATE);


	m_GUIEnv->clear();
	m_GUIEnv->getSkin()->setFont(m_GUIEnv->getFont("../../media/fonttest2.bmp"));
	// Set colour of the UI\
	m_GUIEnv->getSkin()->setColor((EGUI_DEFAULT_COLOR)8, irr::video::SColor(255,0,0,0));

	m_GUIEnv->addStaticText(wcTimerString, rect<s32>(	m_VideoDriver->getScreenSize().Width*0.4,
														m_VideoDriver->getScreenSize().Height*0.04 ,
														m_VideoDriver->getScreenSize().Width*0.4+200,
														m_VideoDriver->getScreenSize().Height*0.04+125),
														true );

	m_GUIEnv->addStaticText(wcHUDString, rect<s32>(		55,
														m_VideoDriver->getScreenSize().Height*0.04,
														300,
														m_VideoDriver->getScreenSize().Height*0.04+125),
														true );

	m_GUIEnv->addImage(	m_VideoDriver->getTexture("../../media/ammo.png"),
						core::position2d<s32>(m_VideoDriver->getScreenSize().Width*0.01,
						m_VideoDriver->getScreenSize().Height*0.02)); 
	

	// if zombie 1 is alive, chase player
	if (alive)
	{
		// chase player
		anode->setPosition(anode->getPosition() - oldTargetVec * 30 * frameDeltaTime);
		///////////////////////////////////////////////////////////////////////////////////////////////////////
		/////the code below was suppose to be the AI's FSM. Something wrong with the magnitude calculation.
		//anode->setPosition(anode->getPosition() - oldTargetVec * 20 * frameDeltaTime);
		//enemy chase state <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
		//calculate the magnitude of the 2 object
		//float Magnitude =  sqrt( anode->getPosition().X		*	camera->getPosition().X	 +	anode->getPosition().Y	*	camera->getPosition().Y  +	anode->getPosition().Z	*	camera->getPosition().Z ); 
		//if magnitude is greater than 5, zombie will chase the player, if zombie is within 5, it will attack
		////If zombie within range, stop chasing and start attacking
		//if (Magnitude < 20)
		//{
		//anode->setPosition(anode->getPosition() - oldTargetVec * 30 * frameDeltaTime);
		//}
		//anode->setRotation(vector3df(0,-camera->getPosition().X,0));
		//anode->setPosition(anode->getPosition() - oldTargetVec * 30 * frameDeltaTime);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	}

	// if zombie 2 is alive
	if (alive2)
	{
		//chase player
		anode2->setPosition(anode2->getPosition() - oldTargetVec * 20 * frameDeltaTime);
	}
	// if zombie 3 is alive
	if (alive3)
	{
		//chase player
		anode3->setPosition(anode3->getPosition() - oldTargetVec * 40 * frameDeltaTime);
	}

	// if zombie 4 is alive
	if (alive4)
	{
		//chase player
		anode4->setPosition(anode4->getPosition() - oldTargetVec * 50 * frameDeltaTime);
	}


		// crosshair image position scales with screen resolution
		m_GUIEnv->addImage(m_VideoDriver->getTexture("../../media/crosshair.png"),
													core::position2d<s32>(m_VideoDriver->getScreenSize().Width*0.487,
													m_VideoDriver->getScreenSize().Height*0.485)); 


		// Work out a frame delta time.
		now = theDevice->getTimer()->getTime();
		frameDeltaTime = (f32)(now - then) / 1000.f; // Time in seconds
		then = now;

		ProcessInput();

		theAIManager->run();

		m_VideoDriver->beginScene(true, true, SColor(100,50,50,50));//(a,r,g,b)
		m_SceneManager->drawAll();
		m_GUIEnv->drawAll();

		// Unlight any currently highlighted scene node    <<<dont want this feature
		//if (highlightedSceneNode)
		//{
		//	highlightedSceneNode->setMaterialFlag(video::EMF_LIGHTING, true);
		//	highlightedSceneNode = 0;
		//}

		// All intersections in this example are done with a ray cast out from the camera to
		// a distance of 1000.  You can easily modify this to check (e.g.) a bullet
		// trajectory or a sword's position, or create a ray from a mouse click position using
		// ISceneCollisionManager::getRayFromScreenCoordinates()
		core::line3d<f32> ray;
		ray.start = camera->getPosition();
		vector3df tar = camera->getTarget();
		ray.end = ray.start + (camera->getTarget() - ray.start).normalize() * 1000.0f;

		// Tracks the current intersection point with the level or a mesh
		core::vector3df intersection;
		// Used to show with triangle has been hit
		core::triangle3df hitTriangle;

		// This call is all you need to perform ray/triangle collision on every scene node
		// that has a triangle selector, including the Quake level mesh.  It finds the nearest
		// collision point/triangle, and returns the scene node containing that point.
		// Irrlicht provides other types of selection, including ray/triangle selector,
		// ray/box and ellipse/triangle selector, plus associated helpers.
		// See the methods of ISceneCollisionManager
		scene::ISceneNode * selectedSceneNode =
			collMan->getSceneNodeAndCollisionPointFromRay(
			ray,
			intersection, // This will be the position of the collision
			hitTriangle, // This will be the triangle hit in the collision
			IDFlag_IsPickable, // This ensures that only nodes that we have
			// set up to be pickable are considered
			0); // Check the entire scene (this is actually the implicit default)

		// If the ray hit anything, move the billboard to the collision position
		// and draw the triangle that was hit.
		if(selectedSceneNode)
		{
			//bill->setPosition(intersection);
//			ISceneNode* theVictim = selectedSceneNode->getParent();
//			selectedSceneNode->setVisible(!selectedSceneNode->isVisible());
			irr::s32 xxx = selectedSceneNode->getID();
			selectedSceneNode->getType();

			
//			theVictim->remove();
//			theVictim->setVisible(false);
//			irr::s32 xxx = theVictim->getReferenceCount();


			// We need to reset the transform before doing our own rendering.
			m_VideoDriver->setTransform(video::ETS_WORLD, core::matrix4());
			m_VideoDriver->setMaterial(material);
			//disable draw triangle
			//m_VideoDriver->draw3DTriangle(hitTriangle, video::SColor(0,255,0,0));

			// We can check the flags for the scene node that was hit to see if it should be
			// highlighted. The animated nodes can be highlighted, but not the Quake level mesh
			if((selectedSceneNode->getID() & IDFlag_IsHighlightable) == IDFlag_IsHighlightable)
			{
				highlightedSceneNode = selectedSceneNode;
				
				// Highlighting in this case means turning lighting OFF for this node,
				// which means that it will be drawn with full brightness.
				highlightedSceneNode->setMaterialFlag(video::EMF_LIGHTING, false);
				
			}

			if (theWeaponManager.hasPrimaryWeaponFired())
			{
					node->setMD2Animation("pow");
					
				if ((selectedSceneNode->getID() & IDFlag_IsHighlightable) == IDFlag_IsHighlightable)
				{
					//the exact frame of the animation where it plays "scene::EMAT_DEATH_FALLBACK" = 712 - 732
					//start frame and end frame
					s32 Sframe = 712, Eframe = 732; 
					//selectedSceneNode->setVisible(!selectedSceneNode->isVisible());
					//selectedSceneNode->setMD2Animation(scene::EMAT_DEATH_FALLBACK);
					if (selectedSceneNode==anode && alive)
					{
						//anode->setMD2Animation(scene::EMAT_DEATH_FALLBACK);
						anode->setFrameLoop(Sframe,Eframe);
						anode->setLoopMode(false);
						//anode->setTriangleSelector(false);
						alive=false;

					}

					if (selectedSceneNode==anode2 && alive2)
					{
						//anode->setMD2Animation(scene::EMAT_DEATH_FALLBACK);
						anode2->setFrameLoop(Sframe,Eframe);
						anode2->setLoopMode(false);
						//anode->setTriangleSelector(false);
						alive2=false;
					}

					if (selectedSceneNode==anode3 && alive3)
					{
						//anode->setMD2Animation(scene::EMAT_DEATH_FALLBACK);
						anode3->setAnimationSpeed(10);
						anode3->setFrameLoop(166,170);
						anode3->setLoopMode(false);
						//anode->setTriangleSelector(false);
						alive3=false;
					}

					if (selectedSceneNode==anode4 && alive4)
					{
						//anode->setMD2Animation(scene::EMAT_DEATH_FALLBACK);
						anode4->setFrameLoop(Sframe,Eframe);
						anode4->setLoopMode(false);
						//anode->setTriangleSelector(false);
						alive4=false;
					}
			///////////////////////////////////
			// Hide the corpse. Something wrong with the timer. suppose to hide it after 3 second
			//if (!alive)
			//{
			//	int CurrentTime = theDevice->getTimer()->getTime()/1000+3;
			//	int FadeTime = CurrentTime-theDevice->getTimer()->getTime()/1000;
			//	if (FadeTime == 0)
			//	{
			//		anode->setVisible(false);
			//	}
			//					
			//}
			/////////////////////////////////////				
				
				
				}

				// collides with wall
				vector3df out = hitTriangle.getNormal();
				out.setLength(0.03f);

				SParticleImpact imp;
				imp.when = 1;
				imp.outVector = out;
				imp.pos = intersection;

//				player->setAnim ( "pow" );
//				player->Anim[1].next += player->Anim[1].delta;

				if (imp.when)
				{
					f32 length = (f32)(intersection - camera->getPosition()).getLength();
					const f32 speed = 5.8f;
					u32 time = (u32)(length / speed);

					// create impact note
					imp.when = theDevice->getTimer()->getTime() + (time + (s32) ( ( 1.f + Noiser::get() ) * 250.f ));
					Impacts.push_back(imp);
				}
				theWeaponManager.togglePrimaryWeaponFired();
				node->setMD2Animation("idle");
			}

		}		

		createParticleImpacts ( now );
		m_VideoDriver->endScene();

		// Start the theEventReceiver
		theEventReceiver.startEventProcess();

	}

	// Clear the AIManager before leaving this state
	delete theAIManager;

	//GameManager::setNextState( MainMenuState::getInstance() );
	theDevice->getCursorControl()->setVisible(true);


}

void ZFGameState::exit()
{
	Impacts.clear();

	theDevice->setEventReceiver(0);

	m_GUIEnv->clear();
	m_GUIEnv = NULL;

	m_SceneManager->clear();
	m_SceneManager = NULL;

	m_VideoDriver = NULL;
}

void ZFGameState::pause()
{
}

void ZFGameState::resume()
{
}

void ZFGameState::ProcessInput()
{


	if(theEventReceiver.keyReleased(irr::KEY_ESCAPE))
	{
		m_bEndState = true;
		GameManager::setNextState( MainMenuState::getInstance() );
	}
	if(theEventReceiver.keyReleased(irr::KEY_RETURN))
	{
		m_bEndState = true;
		GameManager::setNextState( CurrentMapState::getInstance() );
	}
	if(theEventReceiver.keyReleased(irr::KEY_KEY_R) && clip >=1 && bullet <200)
	{
		clip--;
		bullet+=200;
		if (bullet>=200)
		{
			bullet=200;
		}
	}

	// Calculate the direction vector of the camera
	oldTargetVec   = (camera->getTarget() - camera->getPosition());
	oldTargetVec.Y = 0.0;	// We set this to 0.0, so that the camera will not move up nor down during movement.
	oldTargetVec.normalize();

	// Calculate the up vector of the camera
	upVector       = camera->getUpVector();

	// Calculate the right vector of the camera
	rightVector    = upVector.crossProduct(oldTargetVec);
	rightVector.normalize();

	// Move forward
	if(theEventReceiver.keyDown(irr::KEY_KEY_W))
	{
		camera->setPosition( camera->getPosition() + oldTargetVec * MOVEMENT_SPEED * frameDeltaTime );
	}

	// Move backward
	if(theEventReceiver.keyDown(irr::KEY_KEY_S))
		camera->setPosition( camera->getPosition() - oldTargetVec * MOVEMENT_SPEED * frameDeltaTime );

	// Strafe left
	if(theEventReceiver.keyDown(irr::KEY_KEY_A))
		camera->setPosition( camera->getPosition() - rightVector * MOVEMENT_SPEED * frameDeltaTime );

	// Strafe right
	if(theEventReceiver.keyDown(irr::KEY_KEY_D))
		camera->setPosition( camera->getPosition() + rightVector * MOVEMENT_SPEED * frameDeltaTime );




	if(theEventReceiver.leftMouseDown()==true && bullet > 0)
	{

		useItem(Player + 0 );
		bullet--;
		theWeaponManager.togglePrimaryWeaponFired();
	}

	if (theEventReceiver.IsButtonClicked())
	{
		if (theEventReceiver.GetButtonID() == INGAME_ID_MAP_BUTTON)
		{

			m_bEndState = true;
			GameManager::setNextState( CurrentMapState::getInstance() );
		}

		else if (theEventReceiver.GetButtonID() == INGAME_ID_WORLDMAP_BUTTON)
		{

			m_bEndState = true;
			GameManager::setNextState( WorldMapState::getInstance() );
		}

		else if (theEventReceiver.GetButtonID() == INGAME_ID_MAINMENU_BUTTON)
		{

			m_bEndState = true;
			GameManager::setNextState( MainMenuState::getInstance() );
		}
	}
}
/*
	useItem
*/
void ZFGameState::useItem(Q3Player * player)
{
	ISceneManager* m_SceneManager = theDevice->getSceneManager();
	ICameraSceneNode* camera = m_SceneManager->getActiveCamera();

	if (!camera)
		return;

	SParticleImpact imp;
	imp.when = 0;

	// get line of camera

	vector3df start = camera->getPosition();



	vector3df end = (camera->getTarget() - start);
	end.normalize();
	start += end*20.0f;

   	end = start + (end * camera->getFarValue());

	triangle3df triangle;
	line3d<f32> line(start, end);

	// get intersection point with map
	const scene::ISceneNode* hitNode;
	if (m_SceneManager->getSceneCollisionManager()->getCollisionPoint(
		line, Meta, end, triangle,hitNode))
	{
		// collides with wall
		vector3df out = triangle.getNormal();
		out.setLength(0.03f);

		imp.when = 1;
		imp.outVector = out;
		imp.pos = end;

		player->setAnim ( "pow" );
		player->Anim[1].next += player->Anim[1].delta;

	}
	else
	{
		// doesnt collide with wall
		vector3df start = camera->getPosition();


		vector3df end = (camera->getTarget() - start);
		end.normalize();
		start += end*20.0f;
		end = start + (end * camera->getFarValue());
	}

	// create fire ball
	ISceneNode* node = 0;
	node = m_SceneManager->addBillboardSceneNode( BulletParent,dimension2d<f32>(10,10), start);

	node->setMaterialFlag(EMF_LIGHTING, false);
	node->setMaterialTexture(0, theDevice->getVideoDriver()->getTexture("../../media/fireball.bmp"));
	node->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
	node->setMaterialType(EMT_TRANSPARENT_ADD_COLOR);

	f32 length = (f32)(end - start).getLength();
	const f32 speed = 5.8f;//5.8f;
	u32 time = (u32)(length / speed);

	ISceneNodeAnimator* anim = 0;

	// set flight line

	anim = m_SceneManager->createFlyStraightAnimator(start, end, time);
	node->addAnimator(anim);
	anim->drop();

	snprintf ( buf, 64, "bullet: %s on %.1f,%1.f,%1.f",
				imp.when ? "hit" : "nohit", end.X, end.Y, end.Z );
	node->setName ( buf );

	anim = m_SceneManager->createDeleteAnimator(time);
	node->addAnimator(anim);
	anim->drop();
	

	if (imp.when)
	{
		// create impact note
		imp.when = theDevice->getTimer()->getTime() +
			(time + (s32) ( ( 1.f + Noiser::get() ) * 250.f ));
		Impacts.push_back(imp);
	}

	// play sound
}
// rendered when bullets hit something
void ZFGameState::createParticleImpacts( u32 now )
{
//	ISceneManager* sm = Game->Device->getSceneManager();

	struct smokeLayer
	{
		const c8 * texture;
		f32 scale;
		f32 minparticleSize;
		f32 maxparticleSize;
		f32 boxSize;
		u32 minParticle;
		u32 maxParticle;
		u32 fadeout;
		u32 lifetime;
	};

	smokeLayer smoke[] =
	{
		{ "../../media/smoke2.jpg", 1.3f, 1.5f, 10.0f, 2.f, 1, 10, 0, 800 },
		{ "../../media/smoke3.jpg", 1.3f, 1.5f, 10.0f, 2.f, 1, 10, 0, 800 }
	};


	u32 i;
	u32 g;
	s32 factor = 1;
	for ( g = 0; g != 2; ++g )
	{
		smoke[g].minParticle *= factor;
		smoke[g].maxParticle *= factor;
		smoke[g].lifetime *= factor;
		smoke[g].boxSize *= Noiser::get() * 0.5f;
	}

	for ( i=0; i < Impacts.size(); ++i)
	{
		if (now < Impacts[i].when)
			continue;

		// create smoke particle system
		IParticleSystemSceneNode* pas = 0;

		for ( g = 0; g != 2; ++g )
		{
			pas = m_SceneManager->addParticleSystemSceneNode(false, BulletParent, -1, Impacts[i].pos);

			snprintf ( buf, 64, "bullet impact smoke at %.1f,%.1f,%1.f", Impacts[i].pos.X,Impacts[i].pos.Y,Impacts[i].pos.Z);
			pas->setName ( buf );

			// create a flat smoke
			vector3df direction = Impacts[i].outVector;
			direction *= smoke[g].scale;
			IParticleEmitter* em = pas->createBoxEmitter(
				aabbox3d<f32>(-4.f,0.f,-4.f,0.0f,smoke[g].minparticleSize,0.0f),
				direction,smoke[g].minParticle, smoke[g].maxParticle,
				video::SColor(0,0,0,0),video::SColor(0,128,128,128),
				250,4000, 60);

			em->setMinStartSize (dimension2d<f32>( smoke[g].minparticleSize, smoke[g].minparticleSize));
			em->setMaxStartSize (dimension2d<f32>( smoke[g].maxparticleSize, smoke[g].maxparticleSize));

			pas->setEmitter(em);
			em->drop();

			// particles get invisible
			IParticleAffector* paf = pas->createFadeOutParticleAffector(
				video::SColor ( 0, 0, 0, 0 ), smoke[g].fadeout);
			pas->addAffector(paf);
			paf->drop();

			// particle system life time
			ISceneNodeAnimator* anim = m_SceneManager->createDeleteAnimator( smoke[g].lifetime);
			pas->addAnimator(anim);
			anim->drop();

			pas->setMaterialFlag(video::EMF_LIGHTING, false);
			pas->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
			pas->setMaterialType(video::EMT_TRANSPARENT_VERTEX_ALPHA );
			pas->setMaterialTexture(0, m_VideoDriver->getTexture( smoke[g].texture ));
		}


		// play impact sound
		#ifdef USE_IRRKLANG
/*
		if (irrKlang)
		{
			audio::ISound* sound =
				irrKlang->play3D(impactSound, Impacts[i].pos, false, false, true);

			if (sound)
			{
				// adjust max value a bit to make to sound of an impact louder
				sound->setMinDistance(400);
				sound->drop();
			}
		}
*/
		#endif


		// delete entry
		Impacts.erase(i);
		i--;
	}
}
