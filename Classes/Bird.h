#ifndef __BIRD_H__
#define __BIRD_H__

#include "cocos2d.h"

USING_NS_CC;

class Bird: public Sprite
{
private:
    Action* _idle;
    Action* _swing;
    Action* _fly;

public:
    static Bird* create();
    virtual bool init();
    void idle();
    void stop();
    void fly();
CC_CONSTRUCTOR_ACCESS:
    Bird();
    ~Bird();
};

#endif //__BIRD_H__
