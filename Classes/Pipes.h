#ifndef __PIPES_H__
#define __PIPES_H__

#include "cocos2d.h"

USING_NS_CC;

class Pipes: public Node
{
public:
    static Pipes* create();
    virtual bool init();
    Sprite* getTopPipe() { return _top; }
    Sprite* getBottomPipe() { return _bottom; }
    void setCoinPhysicsEnabled(bool enable);
    void setPhysicsEnabled(bool enable);
    void setTag(int tag);

private:
    Sprite* _top;
    Sprite* _bottom;
    PhysicsBody* _coin;

CC_CONSTRUCTOR_ACCESS:
    Pipes();
    ~Pipes();
};

#endif //__PIPES_H__
