#include "Q3Player.h"
#include "IntroState.h"
#include "MainMenuState.h"
#include "InstructionState.h"
#include "HighscoreState.h"
#include "CreditsState.h"
#include "ZFGameState.h"
#include "WorldMapState.h"
#include "CurrentMapState.h"


ISceneNodeAnimatorCollisionResponse* camCollisionResponse( IrrlichtDevice * device )
{
	ICameraSceneNode *camera = device->getSceneManager()->getActiveCamera();
	ISceneNodeAnimatorCollisionResponse *a = 0;

	list<ISceneNodeAnimator*>::ConstIterator it = camera->getAnimators().begin();
	for (; it != camera->getAnimators().end(); ++it)
	{
		a = (ISceneNodeAnimatorCollisionResponse*) (*it);
		if ( a->getType() == ESNAT_COLLISION_RESPONSE )
			return a;
	}

	return 0;
}

/* set the Animation of the player and weapon
*/
void Q3Player::setAnim ( const c8 *name )
{
	if ( name )
	{
		snprintf ( animation, 64, "%s", name );
		if ( WeaponNode )
		{
			WeaponNode->setAnimationEndCallback ( this );
			WeaponNode->setMD2Animation ( animation );
		}
	}
	else
	{
		animation[0] = 0;
		if ( WeaponNode )
		{
			WeaponNode->setAnimationEndCallback ( 0 );
		}
	}
}

// Callback
void Q3Player::OnAnimationEnd(IAnimatedMeshSceneNode* node)
{
	setAnim ( 0 );
}
