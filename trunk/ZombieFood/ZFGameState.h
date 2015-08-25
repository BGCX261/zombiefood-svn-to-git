#ifndef ZFGameState_H
#define ZFGameState_H

#include "GameState.h"
#include "MyEventReceiver.h"
#include "AIManager.h"
#include "Q3Player.h"
#include "ProjectileInfo.h"
#include "WeaponManager.h"

/*
struct GameData
{
	GameData ( const path &startupDir) :
		retVal(0), StartupDir(startupDir), createExDevice(0), Device(0)
	{
		setDefault ();
	}

	void setDefault ();
	s32 save ( const path &filename );
	s32 load ( const path &filename );

	s32 debugState;
	s32 gravityState;
	s32 flyTroughState;
	s32 wireFrame;
	s32 guiActive;
	s32 guiInputActive;
	f32 GammaValue;
	s32 retVal;
	s32 sound;

	path StartupDir;
	stringw CurrentMapName;
	array<path> CurrentArchiveList;

	vector3df PlayerPosition;
	vector3df PlayerRotation;


	SIrrlichtCreationParameters deviceParam;
	funcptr_createDeviceEx createExDevice;
	IrrlichtDevice *Device;
};
*/
// random noise [-1;1]
struct Noiser
{
	static f32 get ()
	{
		static u32 RandomSeed = 0x69666966;
		RandomSeed = (RandomSeed * 3631 + 1);

		f32 value = ( (f32) (RandomSeed & 0x7FFF ) * (1.0f / (f32)(0x7FFF >> 1) ) ) - 1.f;
		return value;
	}
};
class ZFGameState : public GameState
{
public:
//	ZFGameState( GameData *gameData );
	void enter();
	void exit();

	void pause();
	void resume();

	void ProcessInput();
	void createParticleImpacts( u32 );

	static ZFGameState* getInstance() { return &mZFGameState; }

	void Animate();
	Q3Player *GetPlayer ( u32 index ) { return &Player[index]; }
protected:
	ZFGameState() { }

private:
	ISceneNode* BulletParent;
	c8 buf[256];
	Q3Player Player[2];
	struct SParticleImpact
	{
		u32 when;
		vector3df pos;
		vector3df outVector;
	};

	array<SParticleImpact> Impacts;
	static ZFGameState mZFGameState;
	scene::ICameraSceneNode* camera;	
	IMetaTriangleSelector *Meta;
	void createTextures ();
	//void useItem(  );
	void useItem( Q3Player * player);
	// In order to do framerate independent movement, we have to know
	// how long it was since the last frame
    u32 then;
	u32 now;
	f32 frameDeltaTime;
	
	// Weapon Management
	WeaponManager theWeaponManager;

	// Vectors for calculating camera movement
	vector3df oldTargetVec;
	vector3df upVector;
	vector3df rightVector;

	MyEventReceiver theEventReceiver;
	
	AIManager* theAIManager;
};



#endif