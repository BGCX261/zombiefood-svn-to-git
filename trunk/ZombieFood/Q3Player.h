#ifndef Q3Player_H
#define Q3Player_H

#include <irrlicht.h>
#include "ProjectileInfo.h"
#include "GameState.h"
#include "MyEventReceiver.h"

using namespace irr;
using namespace scene;
using namespace core;

class Q3Player : public IAnimationEndCallBack
{
public:
	Q3Player ()
	: Device(0), MapParent(0), Mesh(0), WeaponNode(0), StartPositionCurrent(0)
	{
		animation[0] = 0;
		memset(Anim, 0, sizeof(TimeFire)*4);
	}

	virtual void OnAnimationEnd(IAnimatedMeshSceneNode* node);

	void create (	IrrlichtDevice *device,
					IQ3LevelMesh* mesh,
					ISceneNode *mapNode,
					IMetaTriangleSelector *meta
				);
	void shutdown ();
	void setAnim ( const c8 *name );
	void respawn ();
	void setpos ( const vector3df &pos, const vector3df& rotation );

	friend ISceneNodeAnimatorCollisionResponse* camCollisionResponse( IrrlichtDevice * device );
	ISceneNodeAnimatorCollisionResponse * cam() { return camCollisionResponse ( Device ); }

	IrrlichtDevice *Device;
	ISceneNode* MapParent;
	IQ3LevelMesh* Mesh;
	IAnimatedMeshSceneNode* WeaponNode;
	s32 StartPositionCurrent;
	TimeFire Anim[4];
	c8 animation[64];
	c8 buf[64];
};

#endif