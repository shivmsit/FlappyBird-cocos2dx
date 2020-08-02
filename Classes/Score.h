#ifndef __SCORE_H__
#define __SCORE_H__

#include "cocos2d.h"

USING_NS_CC;

class Score: public Node
{
public:
    static Score* create();
    virtual bool init();
    void addScore();
    int getScore();
    void reset();
    void updateScore();
    int getTopScore();
CC_CONSTRUCTOR_ACCESS:
    Score();
    ~Score();
private:
    int _score;
    Label* _scoreLabel;
};

#endif //__SCORE_H__
