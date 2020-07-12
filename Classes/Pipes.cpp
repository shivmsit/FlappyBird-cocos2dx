#include "Pipes.h"
#include "Settings.h"

Pipes* Pipes::create()
{
    Pipes* pipes = new (std::nothrow) Pipes();
    if (pipes && pipes->init())
    {
        pipes->autorelease();
        return pipes;
    }
    CC_SAFE_DELETE(pipes);
    return nullptr;
}

bool Pipes::init()
{
    if (!Node::init())
        return false;

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    _top = Sprite::createWithSpriteFrameName("pipe_green_top.png");
    _bottom = Sprite::createWithSpriteFrameName("pipe_green_bottom.png");

    _top->setPosition(Vec2(0, _top->getContentSize().height/2.0f +  PIPE_VERTICAL_GAP/2.0f));
    _bottom->setPosition(Vec2(0, -_bottom->getContentSize().height/2.0f - PIPE_VERTICAL_GAP/2.0f));

    // add these sprite as a child to this layer
    addChild(_top, 0);
    addChild(_bottom, 0);

    return true;
}

Pipes::Pipes() { }
Pipes::~Pipes() { }
