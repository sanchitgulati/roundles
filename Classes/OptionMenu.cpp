//
//  OptionMenu.cpp
//  roundels
//
//  Created by Sanchit Gulati on 08/06/14.
//
//

#include "OptionMenu.h"
#include "MainMenuScene.h"

enum btnId
{
    bBack,
};

USING_NS_CC;

Scene* OptionMenu::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = OptionMenu::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool OptionMenu::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    /* Touch Dispatcher */
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(OptionMenu::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(OptionMenu::onTouchEnded, this);
    listener->onTouchMoved = CC_CALLBACK_2(OptionMenu::onTouchMoved, this);
    listener->onTouchCancelled = CC_CALLBACK_2(OptionMenu::onTouchCancelled, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    /* End */
    
    visibleSize = Director::getInstance()->getVisibleSize();
    winSize = Director::getInstance()->getWinSize();
    origin = Director::getInstance()->getVisibleOrigin();
    fontSize = Constants::defaultFontSize*(winSize.width/480);
    Constants::fontSize = this->fontSize;
    Constants::vEdgeMargin = winSize.width/20.0f;
    
    
    /* Initiation Of Variables */
    lbackground = LayerColor::create(Color4B(BG_RGBA), visibleSize.width, visibleSize.height);
    this->addChild(lbackground,zBg);
    
    
    auto btnBack = Button::create("Back", IMG_BUTTON_BACK, Color3B(LOGO_RGB));
    btnBack->setCallback(CC_CALLBACK_1(OptionMenu::menuCallback, this));
    btnBack->setTag(bBack);
    btnBack->setPosition(Point(origin.x + visibleSize.width*0.15, origin.y + visibleSize.height*0.85 ));
    
    auto header = Header::create("Options",IMG_BUTTON_OPTION, Color3B(INNER_LOGO_RGB));
    header->setEnabled(false);
    header->setPosition(Point(origin.x + visibleSize.width*(1-0.15), origin.y + visibleSize.height*0.85 ));
    this->addChild(header);
    
    auto radioSound = Radio::create("Sound Effects");
    radioSound->setPosition(Point(origin.x + visibleSize.width*(0.5), origin.y + visibleSize.height*0.60));
    
    auto radioMusic = Radio::create("Music");
    radioMusic->setPosition(Point(origin.x + visibleSize.width*(0.5), origin.y + visibleSize.height*0.50));
    
    auto radioIAP = Radio::create("Manage Purchases");
    radioIAP->setPosition(Point(origin.x + visibleSize.width*(0.5), origin.y + visibleSize.height*0.40));
    
    auto radioLevels = Radio::create("Reset Levels");
    radioLevels->setPosition(Point(origin.x + visibleSize.width*(0.5), origin.y + visibleSize.height*0.30));
    
    auto menu = Menu::create(btnBack,radioMusic,radioIAP,radioLevels,radioSound, NULL);
    menu->setPosition(Point(0,0));
    this->addChild(menu);
    
    
    //schedule update
    this->scheduleUpdate();
    return true;
}

void OptionMenu::update(float dt)
{
    
}


void OptionMenu::menuCallback(Ref* pSender)
{
    auto obj = (Node*)pSender;
    switch (obj->getTag()) {
            case bBack:
            Director::getInstance()->replaceScene((Scene*)MainMenu::create());
            break;
            default:
            Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
            exit(0);
            break;
#endif
    }
}


bool OptionMenu::onTouchBegan(cocos2d::Touch *touch,cocos2d::Event *event)
{
    touchStart = touch->getLocation();
    return true;
};

void OptionMenu::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event)
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

void OptionMenu::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
    touchStart = Point::ZERO;
}

void OptionMenu::onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *event)
{
    touchStart = Point::ZERO;
}

void OptionMenu::swipeLeft()
{
    log("left");
}
void OptionMenu::swipeRight()
{log("right");}
void OptionMenu::swipeUp()
{log("up");}
void OptionMenu::swipeDown()
{log("down");}

