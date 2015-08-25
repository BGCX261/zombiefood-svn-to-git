#pragma once

#include <irrlicht.h>

using namespace irr;
using namespace irr::scene;

class AIObject
{
public:
	AIObject(void);
	~AIObject(void);

	// Set the AI object to this class
	void SetAIObject(IAnimatedMeshSceneNode* theAIObject);

	// Get the position of the AI Object
	const core::vector3df& getPosition() const;

	//move our hero towards the specified point(vector)
	void Move(core::vector3df in_pos);

	//continue moving our hero to previously sprecified point(vector)
	void Move();

	//make our her turn towards his target
	core::vector3df FaceTarget(core::vector3df in_targetpos);

	//private function for moving our hero towards his target at some specified velrocity(vector)
	void MoveTo(core::vector3df in_vel);

private:
	IAnimatedMeshSceneNode* theAIObject;
	core::vector3df			target;
	core::aabbox3df			fBoundingBox;
	f32						fRepelDistance;
};
