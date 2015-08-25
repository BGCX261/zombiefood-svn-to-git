#ifndef ProjectileInfo_H
#define ProjectileInfo_H

#include <irrlicht.h>

using namespace irr;

//! internal Animation
enum eTimeFireFlag
{
	FIRED = 1,
};

struct TimeFire
{
	u32 flags;
	u32 next;
	u32 delta;
};

void setTimeFire ( TimeFire *t, u32 delta, u32 flags = 0 );
void checkTimeFire ( TimeFire *t, u32 listSize, u32 now );

#endif