//
//  GameScene.cpp
//  roundels
//
//  Created by Sanchit Gulati on 15/06/14.
//
//

#include "GameScene.h"

#include "LevelMenu.h"
#include "MainMenuScene.h"
#include "SimpleAudioEngine.h"

enum{bBack,bHint,bRestart};

USING_NS_CC;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    /* Touch Dispatcher */
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
    listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
    listener->onTouchCancelled = CC_CALLBACK_2(GameScene::onTouchCancelled, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    /* End */
    
    visibleSize = Director::getInstance()->getVisibleSize();
    winSize = Director::getInstance()->getWinSize();
    origin = Director::getInstance()->getVisibleOrigin();
    fontSize = Constants::defaultFontSize*(winSize.width/480);
    
    /* Initiation Of Variables */
    lbackground = LayerColor::create(RGBA_COLOR1, visibleSize.width, visibleSize.height);
    this->addChild(lbackground,zBg);
    
    auto btnBack = Button::create("Back",IMG_BUTTON_BACK,RGB_COLOR2);
    btnBack->setPosition(Point(origin.x + visibleSize.width*0.15, origin.y + visibleSize.height*0.85 ));
    btnBack->setCallback(CC_CALLBACK_1(GameScene::menuCallback, this));
    btnBack->setTag(bBack);
    
    auto btnHint = Button::create("Hint",IMG_BUTTON_HINT,RGB_COLOR2);
    btnHint->setPosition(Point(origin.x + visibleSize.width*0.50, origin.y + visibleSize.height*0.85 ));
    btnHint->setCallback(CC_CALLBACK_1(GameScene::menuCallback, this));
    btnHint->setTag(bHint);
    
    
    auto btnRestart = Button::create("Restart",IMG_BUTTON_RESTART,RGB_COLOR2);
    btnRestart->setPosition(Point(origin.x + visibleSize.width*(1-0.15), origin.y + visibleSize.height*0.85 ));
    btnRestart->setCallback(CC_CALLBACK_1(GameScene::menuCallback, this));
    btnRestart->setTag(bRestart);
    
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(btnBack, btnHint,btnRestart, NULL);
    
    
    //That Circle in the backgroud
    auto backgroundCircle = Sprite::create(IMG_CIRCLE_WHITE);
    backgroundCircle->setScale(Util::getScreenRatioWidth(backgroundCircle)*1.2);
    backgroundCircle->setColor(LevelXML::getBundleColorInnerAt(LevelXML::curBundleNumber));
    backgroundCircle->setPosition(Point(origin.x + visibleSize.width*(0.50), origin.y + visibleSize.height*0.35 ));
    this->addChild(backgroundCircle);
    
    /*Getting Scale For Future Use */
    auto scaleSprite = Sprite::create(IMG_CIRCLE_WHITE);
    scaleSprite->setScale(Util::getScreenRatio(scaleSprite)*0.14);
    auto scale = scaleSprite->getScale();
    auto size = scaleSprite->getBoundingBox().size.width + 16;
    
    auto levelNode = Node::create();
    /* Load Up Level */
    level = LevelXML::getCurrentLevel();
    
    std::vector<Node*> gridStatus;
    for(int i = 0; i < LevelXML::getGridSizeX()*LevelXML::getGridSizeY();i++ )
    {
        gridStatus.push_back(Node::create());
    }
    
    player = Player::create(IMG_CIRCLE_WHITE);
    for (std::vector<LevelElement>::iterator it = level.begin() ; it != level.end(); ++it)
    {
        switch (it->type) {
            case eStart:
            {
                player->x = it->x;
                player->y = it->y;
                player->setPosition(it->x*size, it->y*size);
                player->setScale(scale);
                player->setTotalElements(static_cast<int>(level.size()));
                levelNode->addChild(player);
            }
                break;
            case eSingle:
            {
                auto element = Single::create(IMG_CIRCLE_WHITE);
                element->setScale(scale);
                element->setPosition(it->x*size, it->y*size);
                levelNode->addChild(element);
//                gridStatus[it->x*LevelXML::getGridSizeX()+it->y] = element;
            }
            default:
                break;
        }
    }
    
    levelNode->setPosition(Point(Constants::vEdgeMargin + 32, Constants::vEdgeMargin + 128));
    this->addChild(levelNode);
    
    menu->setPosition(Point::ZERO);
    this->addChild(menu, zMenu);
 
    //schedule update
    this->scheduleUpdate();
    return true;
}

void GameScene::update(float dt)
{
    
}


void GameScene::menuCallback(Ref* pSender)
{
    //Reached Callback Notification
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(SFX_BTN_CLICKED);
    
    auto obj = (Node*)pSender;
    switch (obj->getTag()) {
        case bBack:
        {
            auto s = (Scene*)LevelMenu::create();
            Director::getInstance()->replaceScene(TransitionFade::create(0.5f, s,RGB_COLOR1));
            break;
        }
        case bRestart:
        {
            auto s = (Scene*)GameScene::create();
            Director::getInstance()->replaceScene(TransitionFade::create(0.5f, s,RGB_COLOR1));
            break;
        }
        case bHint:
        {
            break;
        }
        default:
            Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
            exit(0);
            break;
#endif
    }
}


bool GameScene::onTouchBegan(cocos2d::Touch *touch,cocos2d::Event *event)
{
    touchStart = touch->getLocation();
    return true;
};

void GameScene::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event)
{
    auto location = touch->getLocation();
    if(touchStart != Point::ZERO)
    {
        //right left
        if( touchStart.x - location.x  > SWIPE_THRESHOLD)
        {swipeLeft();touchStart = Point::ZERO;}
        else if(location.x - touchStart.x > SWIPE_THRESHOLD)
        {swipeRight();touchStart = Point::ZERO;}
        //up down
        else if(touchStart.y - location.y > SWIPE_THRESHOLD)
        {swipeDown();touchStart = Point::ZERO;}
        else if (location.y - touchStart.y > SWIPE_THRESHOLD)
        {swipeUp();touchStart = Point::ZERO;}
    }
}

void GameScene::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
    touchStart = Point::ZERO;
}

void GameScene::onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *event)
{
    touchStart = Point::ZERO;
}

void GameScene::swipeLeft()
{
    for(int i = player->x; i >= 0; i++)
    {
    }
}
void GameScene::swipeRight()
{log("right");}
void GameScene::swipeUp()
{log("up");}
void GameScene::swipeDown()
{log("down");}
