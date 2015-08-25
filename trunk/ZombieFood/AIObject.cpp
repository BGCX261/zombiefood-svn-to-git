#include "AIObject.h"

const f32 fSpeed = 0.1f;


AIObject::AIObject(void)
: theAIObject(NULL)
, fRepelDistance(4.0)
{
}

AIObject::~AIObject(void)
{
	this->theAIObject = NULL;
}

// Set the AI object to this class
void AIObject::SetAIObject(IAnimatedMeshSceneNode* theAIObject)
{
	if (theAIObject)
	{
		this->theAIObject = theAIObject;

		this->theAIObject->setMaterialFlag(irr::video::EMF_LIGHTING, false);
		//node->setAnimationSpeed(0.01);
		this->theAIObject->setMD2Animation(irr::scene::EMAT_RUN);
		this->theAIObject->setAnimationSpeed(50);

		//node->setMD2Animation(scene::EMAT_BOOM);
		//node->setMD2Animation(scene::EMAT_COUNT);
		//anode->setMaterialTexture( 0, m_VideoDriver->getTexture("../../media/dwarf.jpg") );

		fBoundingBox = theAIObject->getBoundingBox();

		// Set the repel distance to be the longest part of the bounding box
		irr::core::vector3df fBoundingBoxExtent = fBoundingBox.getExtent();
		fRepelDistance =  fBoundingBoxExtent.Z / 2.0;
		if (fBoundingBoxExtent.X > fRepelDistance)
			fRepelDistance =  fBoundingBoxExtent.X / 2.0;
		if (fBoundingBoxExtent.Y > fRepelDistance)
			fRepelDistance =  fBoundingBoxExtent.Y / 2.0;
	}
}

// Get the position of the AI Object
const core::vector3df& AIObject::getPosition() const
{
	return theAIObject->getPosition();
}

//move our hero towards the specified point(vector)
void AIObject::Move(core::vector3df in_pos)
{
	this->target = in_pos;   //set hero's target

	//if hero's distance from target is less than 4, don't move
	if (theAIObject->getPosition().getDistanceFrom(this->target) < fRepelDistance){
		return;
	}
	else{
		//set hero's rotation so he faces target
		theAIObject->setRotation(FaceTarget(this->target));
		//move hero towards his target at some speed(vector)
		MoveTo(core::vector3df(0,0,fSpeed));
	}
}

//continue moving our hero to previously sprecified point(vector)
void AIObject::Move()
{
	//the same as previous except we don't set target couse he already has one
	if (theAIObject->getPosition().getDistanceFrom(this->target) < fRepelDistance){
		target.set( theAIObject->getPosition() );
		return;
	}
	else{
//		theAIObject->setRotation(FaceTarget(this->target));
		MoveTo(core::vector3df(0,0,fSpeed));
	}
}

//make our her turn towards his target
core::vector3df AIObject::FaceTarget(core::vector3df in_targetpos)
{
	//subtract hero from target vector and you get the vector pointing from hero to
	//his target (trigonometry) and that's our way
	core::vector3df posDiff = in_targetpos - theAIObject->getPosition();
	f32 degree = theAIObject->getPosition().Y; //keep current rotation if nothing to do
	posDiff.normalize();   //we need only direction, not exact value

	//if we are not aligned with the target
	if (posDiff.X != 0.0f || posDiff.Z != 0.0f)
		//calculate degree difference with arcustangens(atan)
		degree = atan2(posDiff.X,posDiff.Z) * core::RADTODEG;

	//rotate our her along the Y axis for the calculated difference
	return core::vector3df(0,degree,0);
}

//private function for moving our hero towards his target at some specified velocity(vector)
void AIObject::MoveTo(core::vector3df in_vel)
{
	core::matrix4 m;
	//create rotation matrix of our hero
	m.setRotationDegrees(theAIObject->getRotation());
	//move the velrocity vector so he's aligned with our hero
	m.transformVect(in_vel);
	//move hero
	theAIObject->setPosition(theAIObject->getPosition() - in_vel);
	//update his position in regard to his parent
	theAIObject->updateAbsolutePosition();
} 