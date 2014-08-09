//
//  OptionMenu.cpp
//  roundels
//
//  Created by Sanchit Gulati on 08/06/14.
//
//

#include "LevelMenu.h"
#include "MainMenuScene.h"
#include "SimpleAudioEngine.h"

enum btnId
{
    bBack,
};

USING_NS_CC;

Scene* LevelMenu::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = LevelMenu::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool LevelMenu::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    /* Touch Dispatcher */
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(LevelMenu::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(LevelMenu::onTouchEnded, this);
    listener->onTouchMoved = CC_CALLBACK_2(LevelMenu::onTouchMoved, this);
    listener->onTouchCancelled = CC_CALLBACK_2(LevelMenu::onTouchCancelled, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    /* End */
    
    visibleSize = Director::getInstance()->getVisibleSize();
    winSize = Director::getInstance()->getWinSize();
    origin = Director::getInstance()->getVisibleOrigin();
    
    
    /* Initiation Of Variables */
    lbackground = LayerColor::create(RGBA_COLOR1, visibleSize.width, visibleSize.height);
    this->addChild(lbackground,zBg);
    
    
    auto btnBack = Button::create("Back", IMG_BUTTON_BACK, RGB_COLOR2);
    btnBack->setCallback(CC_CALLBACK_1(LevelMenu::menuCallback, this));
    btnBack->setTag(bBack);
    btnBack->setPosition(Point(origin.x + visibleSize.width*0.15, origin.y + visibleSize.height*MENU_HEIGHT ));
    
    auto heading = Header::create("Levels");
    heading->setPosition(Point(origin.x + visibleSize.width*(1-0.15), origin.y + visibleSize.height*MENU_HEIGHT ));
    this->addChild(heading);
    
    auto tblLevel = TableLevel::create();
    auto val = tblLevel->getCellSize();
    tblLevel->setPosition(Point(visibleSize.width/2  - val.width/2 ,0));
    this->addChild(tblLevel);
    
    
    
    auto menu = Menu::create(btnBack,NULL);
    menu->setPosition(Point(0,0));
    this->addChild(menu);
    
    
    //schedule update
    this->scheduleUpdate();
    return true;
}

void LevelMenu::update(float dt)
{
    
}


void LevelMenu::menuCallback(Ref* pSender)
{
    //Reached Callback Notification
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(SFX_BTN_CLICKED);
    
    auto obj = (Node*)pSender;
    switch (obj->getTag()) {
        case bBack:
        {
            auto s = (Scene*)MainMenu::create();
            Director::getInstance()->replaceScene(TransitionFade::create(0.5f, s,RGB_COLOR1));
            
        }
            break;
            default:
            Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
            exit(0);
            break;
#endif
    }
}


bool LevelMenu::onTouchBegan(cocos2d::Touch *touch,cocos2d::Event *event)
{
    touchStart = touch->getLocation();
    return true;
};

void LevelMenu::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event)
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

void LevelMenu::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
    touchStart = Point::ZERO;
}

void LevelMenu::onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *event)
{
    touchStart = Point::ZERO;
}

void LevelMenu::swipeLeft()
{
    log("left");
}
void LevelMenu::swipeRight()
{log("right");}
void LevelMenu::swipeUp()
{log("up");}
void LevelMenu::swipeDown()
{log("down");}

