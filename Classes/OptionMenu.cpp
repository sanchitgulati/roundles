//
//  OptionMenu.cpp
//  roundels
//
//  Created by Sanchit Gulati on 08/06/14.
//
//

#include "OptionMenu.h"
#include "MainMenuScene.h"
#include "SimpleAudioEngine.h"

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
    lbackground = LayerColor::create(RGBA_COLOR1, visibleSize.width, visibleSize.height);
    this->addChild(lbackground,zBg);
    
    
    auto btnBack = Button::create("Back", IMG_BUTTON_BACK, RGB_COLOR2);
    btnBack->setCallback(CC_CALLBACK_1(OptionMenu::menuCallback, this));
    btnBack->setTag(bBack);
    btnBack->setPosition(Point(origin.x + visibleSize.width*0.15, origin.y + visibleSize.height*0.85 ));
    
    
    auto menu = Menu::create(btnBack,NULL);
    menu->setPosition(Point(0,0));
    this->addChild(menu);
    
    auto header = Header::create("Options",IMG_BUTTON_OPTION, RGB_COLOR3);
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

    
    auto group1 = Layer::create();
    auto menu1 = Menu::create(radioMusic,radioIAP,radioLevels,radioSound, NULL);
    group1->addChild(menu1);
    menu1->setPosition(Point(0,0));
    group1->setPosition(Point(0,0));
    this->addChild(group1);
    
    
    auto radioSanchit = Radio::create("SG");
    radioSanchit->setPosition(Point(origin.x + visibleSize.width*(0.5), origin.y + visibleSize.height*0.60));
    
    auto radioRadhika = Radio::create("RD");
    radioRadhika->setPosition(Point(origin.x + visibleSize.width*(0.5), origin.y + visibleSize.height*0.50));
    
    
    auto group2 = Layer::create();
    auto menu2 = Menu::create(radioSanchit,radioRadhika,NULL);
    group2->addChild(menu2);
    menu2->setPosition(Point(0,0));
    group2->setPosition(Point(0,0));
    this->addChild(group2);
    
    
    menu2->setVisible(false);
    
    
    //Testing
    menu1->setTag(101);
    menu2->setTag(102);
    group1->setTag(101);
    group2->setTag(102);
    
    auto swipeMessage = Message::create("<< swipe to see more >>");
    swipeMessage->setPosition(Point(origin.x + visibleSize.width*(0.5), origin.y + visibleSize.height*0.15));
    this->addChild(swipeMessage);
    
    //schedule update
    this->scheduleUpdate();
    return true;
}

void OptionMenu::update(float dt)
{
    
}


void OptionMenu::menuCallback(Ref* pSender)
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
    auto g1 = this->getChildByTag(101)->getChildByTag(101);
    auto g2 = this->getChildByTag(102)->getChildByTag(102);
    if(g1->getUserData())
    {
        g1->setUserData((bool*)false);
        g1->setVisible(false);
        g2->setVisible(true);
    }
    else
    {
        g1->setUserData((bool*)true);
        g2->setVisible(false);
        g1->setVisible(true);
    }
    
    
}
void OptionMenu::swipeRight()
{log("right");swipeLeft();}
void OptionMenu::swipeUp()
{log("up");}
void OptionMenu::swipeDown()
{log("down");}

