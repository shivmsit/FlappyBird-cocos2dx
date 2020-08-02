#ifndef __GAME_OVER_H__
#define __GAME_OVER_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocos2d::ui;

class GameOver: public Node
{
public:
    static GameOver* create(int score);
    virtual bool init(int score);
CC_CONSTRUCTOR_ACCESS:
    GameOver();
    ~GameOver();

private:
    void onAnimationFinished();
    void randomizeSparkle();

private:
    Button* _playButton;
    Button* _scoreButton;
    Sprite* _sparkle;
    Label* _bestScoreLabel;
    int _score;
};

#endif //__GAME_OVER_H__
