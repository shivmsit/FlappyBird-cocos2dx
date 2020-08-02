#ifndef __PHYSICS_HELPER_H__
#define __PHYSICS_HELPER_H__

#include "cocos2d.h"

USING_NS_CC;

PhysicsBody* createBody(PhysicsShape* shape, bool dynamic, bool enableGravity, int categoryMask, int contactTestMask, int collisionMask);

#endif //__PHYSICS_HELPER_H__
