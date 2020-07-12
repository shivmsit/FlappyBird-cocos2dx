#include "Bird.h"

Bird* Bird::create()
{
    Bird* bird = new (std::nothrow) Bird();
    if (bird && bird->init())
    {
        bird->autorelease();
        return bird;
    }
    CC_SAFE_DELETE(bird);
    return nullptr;
}

bool Bird::init()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto spritecache = SpriteFrameCache::getInstance();

    const char* type[] = { "blue", "orange", "red" };
    int color = cocos2d::RandomHelper::random_int(0, 2);
    char birdname[32];
    Vector<SpriteFrame*> animFrames(3);
    for(int i=0; i<3; i++) {
        sprintf(birdname, "bird_%s_%d.png", type[color], i);
        auto frame = spritecache->getSpriteFrameByName(birdname);
        animFrames.pushBack(frame);
    }

    if (!initWithSpriteFrame(animFrames.front()))
        return false;

    //create flap action
    auto flapAnim = Animation::createWithSpriteFrames(animFrames, 1.0f/10);
    auto flapAction = Animate::create(flapAnim);
    _idle = RepeatForever::create(Sequence::create(flapAction, DelayTime::create(.2f), NULL));

    _fly = RepeatForever::create(Animate::create(flapAnim));
    _fly->retain();

    //create the swing action
    auto moveUp = MoveBy::create(.3f, Vec2(0, 6));
    auto moveDown = MoveBy::create(.2f, Vec2(0, -6));
    _swing = RepeatForever::create(Sequence::create(moveUp, moveDown, NULL));

    return true;
}

void Bird::idle()
{
    runAction(_idle);
    runAction(_swing);
}

void Bird::stop()
{
    stopAllActions();
}

void Bird::fly()
{
    stopAllActions();
    runAction(_fly);
}

Bird::Bird() { }
Bird::~Bird() { _fly->release(); }
