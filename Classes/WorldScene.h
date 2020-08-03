#ifndef __WORLD_SCENE_H__
#define __WORLD_SCENE_H__

#include "cocos2d.h"
#include "Settings.h"
#include "Pipes.h"
#include "Bird.h"
#include "Score.h"

USING_NS_CC;

enum GameState
{
    INIT = 0,
    RUNNING,
    HIT,
    GROUNDED,
    PAUSE,
    OVER
};

class WorldScene : public cocos2d::Scene
{
public:
    // implement the "static create()" method manually
    static cocos2d::Scene* create();
    virtual bool init();
    virtual void update(float dt);

private:
    void addPipes();
    void addBird();
    int getRandomPipeY();
    bool onTouchBegan(Touch* touch, Event* event);
    bool onPhysicsContactBegin(const PhysicsContact &contact);
    void onGameOver();
    void restartGame();

private:
    Sprite* _ground[2];
    Sprite* _instruction;
    Sprite* _readyLabel;
    Score* _score;
    Bird* _bird;
    Pipes* _pipes[PIPE_COUNT];
    GameState _state;
    EventListenerTouchOneByOne * _touchOneByOneListenr;
};

#endif // __WORLD_SCENE_H__
