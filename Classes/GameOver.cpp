#include "GameOver.h"
#include "ui/CocosGUI.h"

using namespace cocos2d::ui;

GameOver* GameOver::create()
{
    GameOver* gameOver = new (std::nothrow) GameOver();
    if (gameOver && gameOver->init())
    {
        gameOver->autorelease();
        return gameOver;
    }
    CC_SAFE_DELETE(gameOver);
    return nullptr;
}

bool GameOver::init()
{
    if (!Node::init())
        return false;

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    auto gameOver = Sprite::createWithSpriteFrameName("label_game_over.png");
    gameOver->setOpacity(0);
    gameOver->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height*5.0/6 + origin.y));

    FadeIn* fadeIn = FadeIn::create(0.3f);
    gameOver->runAction(fadeIn);

    addChild(gameOver, 2);

    auto play = Button::create("button_play_normal.png", "button_play_pressed.png", "", Widget::TextureResType::PLIST);
    play->setVisible(false);
    play->setPosition(Vec2(visibleSize.width/2 - play->getContentSize().width/2 - 8 + origin.x, visibleSize.height/3 + origin.y));
    play->addClickEventListener([=](Ref* sender) {
        EventCustom event("game_restart");
        getEventDispatcher()->dispatchEvent(&event);
        this->removeFromParentAndCleanup(true);
    });
    addChild(play, 2);

    auto score = Button::create("button_score_normal.png", "button_score_pressed.png", "", Widget::TextureResType::PLIST);
    score->setVisible(false);
    score->setPosition(Vec2(visibleSize.width/2 + play->getContentSize().width/2 + 8 + origin.x, visibleSize.height/3 + origin.y));
    addChild(score, 2);

    auto scorePanel = Sprite::createWithSpriteFrameName("panel_score.png");
    Vec2 endPos(visibleSize.width/2 + origin.x, visibleSize.height*3.5/6 + origin.y);
    Vec2 startPos(visibleSize.width/2 + origin.x, -scorePanel->getContentSize().height/2 + origin.y);
    auto moveTo = MoveTo::create(0.3f, endPos);
    auto moveFinished = CallFunc::create([=]() {
        score->setVisible(true);
        play->setVisible(true);
    });

    auto seq = Sequence::create(moveTo, moveFinished, nullptr);
    scorePanel->runAction(seq);
    scorePanel->setPosition(startPos);

    addChild(scorePanel, 2);

    return true;
}

GameOver::GameOver() { }
GameOver::~GameOver() { }
