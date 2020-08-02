#include "PhysicsHelper.h"

PhysicsBody* createBody(PhysicsShape* shape, bool dynamic, bool enableGravity, int categoryMask, int contactTestMask, int collisionMask)
{
    auto body = PhysicsBody::create();
    body->addShape(shape);
    body->setDynamic(dynamic);
    body->setLinearDamping(0.0f);
    body->setGravityEnable(enableGravity);
    body->setCategoryBitmask(categoryMask);
    body->setContactTestBitmask(contactTestMask);
    body->setCollisionBitmask(collisionMask);

    return body;
}
