#ifndef __GAME_OVER_H__
#define __GAME_OVER_H__

#include "cocos2d.h"

USING_NS_CC;

class GameOver: public Node
{
public:
    static GameOver* create();
    virtual bool init();
CC_CONSTRUCTOR_ACCESS:
    GameOver();
    ~GameOver();
};

#endif //__GAME_OVER_H__
