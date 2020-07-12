#ifndef __WELCOME_SCENE_H__
#define __WELCOME_SCENE_H__

#include "cocos2d.h"
#include "Settings.h"
#include "Pipes.h"
#include "Bird.h"

USING_NS_CC;

class WelcomeScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* create();
    virtual bool init();
    virtual void update(float dt);

private:
    Sprite* _ground[2];
};

#endif // __WELCOME_SCENE_H__
