#include "WorldScene.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocos2d::ui;

static PhysicsBody* createBody(PhysicsShape* shape, bool dynamic, bool enableGravity, int categoryMask, int contactTestMask, int collisionMask)
{
    auto body = PhysicsBody::create();
    body->addShape(shape);
    body->setDynamic(dynamic);
    body->setLinearDamping(0.0f);
    body->setGravityEnable(enableGravity);
    body->setCategoryBitmask(categoryMask);
    body->setContactTestBitmask(contactTestMask);
    body->setCollisionBitmask(collisionMask);

    return body;
}

Scene* WorldScene::create()
{
    auto scene = new (std::nothrow) WorldScene();
    if (scene && scene->init())
    {
        scene->autorelease();
        return scene;
    }
    CC_SAFE_DELETE(scene);
    return nullptr;
}

bool WorldScene::init()
{
    if (!Scene::initWithPhysics())
        return false;

    getPhysicsWorld()->setDebugDrawMask(0xffff);
    getPhysicsWorld()->setGravity(Vect(0, -900));

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //Add background
    auto background = Sprite::createWithSpriteFrameName("background_day.png");
    // position the background on the center of the screen
    background->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    // add the background as a child to this layer
    addChild(background, 0);

    //Add ground
    _ground[0] = Sprite::createWithSpriteFrameName("ground.png");
    _ground[1] = Sprite::createWithSpriteFrameName("ground.png");

    _ground[0]->setAnchorPoint(Point::ZERO);
    _ground[1]->setAnchorPoint(Point::ZERO);

    _ground[0]->setPhysicsBody(createBody(PhysicsShapeBox::create(_ground[0]->getContentSize()),
                                          false, false, GROUND_BIT, BIRD_BIT, BIRD_BIT));
    _ground[1]->setPhysicsBody(createBody(PhysicsShapeBox::create(_ground[1]->getContentSize()),
                                          false, false, GROUND_BIT, BIRD_BIT, BIRD_BIT));

    _ground[0]->setPosition(Point::ZERO);
    _ground[1]->setPosition(Vec2(_ground[0]->getContentSize().width, 0));

    addChild(_ground[0], 1);
    addChild(_ground[1], 1);

    _instruction = Sprite::createWithSpriteFrameName("instructions.png");
    _instruction->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    addChild(_instruction);

    addPipes();
    addBird();

    //Schedule update to be called per frame
    scheduleUpdate();

    _state = GameState::INIT;

    _touchOneByOneListenr = EventListenerTouchOneByOne::create();
    _touchOneByOneListenr->setSwallowTouches(false);
    _touchOneByOneListenr->onTouchBegan = CC_CALLBACK_2(WorldScene::onTouchBegan, this);

    getEventDispatcher()->addEventListenerWithSceneGraphPriority(_touchOneByOneListenr, this);
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(WorldScene::onPhysicsContactBegin, this);
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
         
    return true;
}

void WorldScene::addPipes()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    int x = visibleSize.width + PIPE_HORIZONTAL_GAP;

    for (int i=0; i<PIPE_COUNT; i++) {
        _pipes[i] = Pipes::create();
        _pipes[i]->setPosition(Vec2(x, getRandomPipeY()));

        auto shape = PhysicsShapeBox::create(_pipes[i]->getTopPipe()->getContentSize());
        _pipes[i]->getTopPipe()->setPhysicsBody(createBody(shape, false, false, PIPE_BIT, BIRD_BIT, BIRD_BIT));

        shape = PhysicsShapeBox::create(_pipes[i]->getBottomPipe()->getContentSize());
        _pipes[i]->getBottomPipe()->setPhysicsBody(createBody(shape, false, false, PIPE_BIT, BIRD_BIT, BIRD_BIT));

        addChild(_pipes[i]);
        x = x + _pipes[i]->getTopPipe()->getContentSize().width + PIPE_HORIZONTAL_GAP;
    }
}

void WorldScene::addBird()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    _bird = Bird::create();

    auto shape = PhysicsShapeCircle::create(BIRD_RADIUS);
    _bird->setPhysicsBody(createBody(shape, true, false, BIRD_BIT, GROUND_BIT | PIPE_BIT, GROUND_BIT));
    _bird->setPosition(Vec2(visibleSize.width/2 + origin.x - 30, visibleSize.height/2 + origin.y));
    _bird->idle();

    addChild(_bird);
}

int WorldScene::getRandomPipeY()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    int startY = _ground[0]->getContentSize().height + PIPE_VERTICAL_GAP/2.0f + PIPE_BOTTOM_MARGIN;
    int endY = visibleSize.height - PIPE_VERTICAL_GAP/2.0f - PIPE_TOP_MARGIN;

    return  cocos2d::RandomHelper::random_int(startY, endY);
}

bool WorldScene::onTouchBegan(Touch* touch, Event* event)
{
    switch(_state) {
        case GameState::INIT:
            _state = GameState::RUNNING;
            _bird->getPhysicsBody()->setGravityEnable(true);
            _instruction->setVisible(false);
        case GameState::RUNNING:
            _bird->fly();
            _bird->getPhysicsBody()->setVelocity(Vec2(0, 300));
            _bird->getPhysicsBody()->setAngularVelocity(3);
            break;
    }
    return true;
}

bool WorldScene::onPhysicsContactBegin(const PhysicsContact &contact)
{
    PhysicsBody* birdBody = contact.getShapeA()->getBody();
    PhysicsBody* otherBody = contact.getShapeB()->getBody();

    if (birdBody->getCategoryBitmask() != BIRD_BIT) {
        std::swap(birdBody, otherBody);
    }

    auto body = _bird->getPhysicsBody();
    if (otherBody->getCategoryBitmask() == PIPE_BIT) {
        body->setAngularVelocity(-1.5);                     //Let it fall to ground with some angular velocity
    } else {
        body->setAngularVelocity(0);                        //Bird hit the ground set angular velocity to 0
        body->setVelocity(Vec2::ZERO);                      //Bird hit the gorund set zero velocity
    }

    _bird->stop();

    if (_state != GameState::OVER) {
        _state = GameState::OVER;
        onGameOver();
    }

    return true;
}

void WorldScene::update(float dt)
{
    auto body = _bird->getPhysicsBody();

    if (_state == GameState::OVER) {
        if (_bird->getRotation() > 30) {
            body->setAngularVelocity(0);
            body->setRotationEnable(false);
            _bird->setRotation(30);
        }
        return;
    }

    float groundWidth = _ground[0]->getContentSize().width;
    for (int i=0; i<2; i++) {
        _ground[i]->setPositionX(_ground[i]->getPositionX() - 2.0f);

        if (_ground[i]->getPositionX() < -groundWidth)
            _ground[i]->setPositionX(_ground[i]->getPositionX() + 2*groundWidth);
    }

    if (_state != GameState::RUNNING)
        return;

    if (_bird->getRotation() < -30) {
        body->setAngularVelocity(0);
        body->setRotationEnable(false);
        _bird->setRotation(-30);
    }

    if (body->getVelocity().y < 0) {
        body->setAngularVelocity(-1.5);
        _bird->stop();
    }

    for (int i=0; i<PIPE_COUNT; i++) {
        _pipes[i]->setPositionX(_pipes[i]->getPositionX() - 2.0f);

        if (_pipes[i]->getPositionX() < -_pipes[i]->getTopPipe()->getContentSize().width - 3) {
            _pipes[i]->setPosition(Vec2(_pipes[i]->getPositionX() + PIPE_COUNT*(_pipes[i]->getTopPipe()->getContentSize().width + PIPE_HORIZONTAL_GAP), getRandomPipeY()));
        }
    }
}

void WorldScene::onGameOver()
{
}
