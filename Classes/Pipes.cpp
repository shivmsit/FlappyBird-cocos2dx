#include "Pipes.h"
#include "Settings.h"
#include "PhysicsHelper.h"

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

    auto shape = PhysicsShapeBox::create(_top->getContentSize());

    _top->setPhysicsBody(createBody(shape, false, false, PIPE_BIT, BIRD_BIT, BIRD_BIT));
    _top->setPosition(Vec2(0, _top->getContentSize().height/2.0f +  PIPE_VERTICAL_GAP/2.0f));

    _bottom = Sprite::createWithSpriteFrameName("pipe_green_bottom.png");

    shape = PhysicsShapeBox::create(_bottom->getContentSize());

    _bottom->setPhysicsBody(createBody(shape, false, false, PIPE_BIT, BIRD_BIT, BIRD_BIT));
    _bottom->setPosition(Vec2(0, -_bottom->getContentSize().height/2.0f - PIPE_VERTICAL_GAP/2.0f));

    // add these sprite as a child to this layer
    addChild(_top, 0);
    addChild(_bottom, 0);

    //Add physics body to detect if bird has crossed the pipe and add score
    auto node = Node::create();

    auto edgeSegment = PhysicsShapeEdgeSegment::create(Vec2(0, PIPE_VERTICAL_GAP/2.0f), Vec2(0, -PIPE_VERTICAL_GAP/2.0f));
    auto body = createBody(edgeSegment, false, false, COIN_BIT, BIRD_BIT, BIRD_BIT);

    //node->addComponent(body);
    node->setPhysicsBody(body);

    addChild(node);

    return true;
}

Pipes::Pipes() { }
Pipes::~Pipes() { }
