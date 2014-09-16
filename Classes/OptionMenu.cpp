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
    
    /* Variable Initialization */
    selectedMenu = 0;
    _total = 0;
    container = Node::create();
    
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
    btnBack->setPosition(Point(origin.x + visibleSize.width*0.15, origin.y + visibleSize.height*MENU_HEIGHT ));
    
    
    auto menu = Menu::create(btnBack,NULL);
    menu->setPosition(Point(0,0));
    this->addChild(menu);
    
    

    
    auto radioSound = Radio::create("Sound Effects");
    radioSound->setPosition(Point(origin.x + visibleSize.width*(0.85), origin.y + visibleSize.height*0.60));
    radioSound->setCallback(CC_CALLBACK_1(OptionMenu::soundCallback, this));
    auto valS = UserDefault::getInstance()->getBoolForKey("sound", true);
    radioSound->setSelectedIndex(!valS); //bug resolved
    
    auto radioMusic = Radio::create("Music");
    radioMusic->setPosition(Point(origin.x + visibleSize.width*(0.85), origin.y + visibleSize.height*0.50));
    radioMusic->setCallback(CC_CALLBACK_1(OptionMenu::musicCallback, this));
    auto valM = UserDefault::getInstance()->getBoolForKey("music", true);
    radioMusic->setSelectedIndex(!valM); //bug resolved

    auto radioIAP = Radio::create("Remove Ads");
    radioIAP->setPosition(Point(origin.x + visibleSize.width*(0.85), origin.y + visibleSize.height*0.40));
    
    auto radioLevels = Radio::create("Reset Game Progress");
    radioLevels->setPosition(Point(origin.x + visibleSize.width*(0.85), origin.y + visibleSize.height*0.30));

    
    auto menuSetting = Menu::create(radioMusic,radioIAP,radioLevels,radioSound, NULL);
    menuSetting->setPosition(Point(0,0));
    container->addChild(menuSetting);
    menuNames.push_back("Options");

    
    auto val = UserDefault::getInstance()->getStringForKey("language", "Base");
    
    auto radioEnglish = Radio::create("English");
    radioEnglish->setPosition(Point(origin.x + visibleSize.width*(0.85), origin.y + visibleSize.height*0.60));
    radioEnglish->setCallback(CC_CALLBACK_1(OptionMenu::languageCallback, this));
    radioEnglish->setUserData((void*)"en.lproj");
    radioEnglish->setSelectedIndex(val.compare("en.lproj") ? 1 : 0);
    
    auto radioJap = Radio::create("Japanese");
    radioJap->setPosition(Point(origin.x + visibleSize.width*(0.85), origin.y + visibleSize.height*0.50));
    radioJap->setCallback(CC_CALLBACK_1(OptionMenu::languageCallback, this));
    radioJap->setUserData((void*)"ja.lproj");
    radioJap->setSelectedIndex(val.compare("ja.lproj") ? 1 : 0);
    
    auto radioFrench = Radio::create("French");
    radioFrench->setPosition(Point(origin.x + visibleSize.width*(0.85), origin.y + visibleSize.height*0.40));
    radioFrench->setCallback(CC_CALLBACK_1(OptionMenu::languageCallback, this));
    radioFrench->setUserData((void*)"fr.lproj");
    radioFrench->setSelectedIndex(val.compare("fr.lproj") ? 1 : 0);
    
    auto radioGerman = Radio::create("German");
    radioGerman->setPosition(Point(origin.x + visibleSize.width*(0.85), origin.y + visibleSize.height*0.30));
    radioGerman->setCallback(CC_CALLBACK_1(OptionMenu::languageCallback, this));
    radioGerman->setUserData((void*)"de.lproj");
    radioGerman->setSelectedIndex(val.compare("de.lproj") ? 1 : 0);
    
    
    auto menuLang = Menu::create(radioEnglish,radioJap,radioFrench,radioGerman, NULL);
    menuLang->setPosition(Point(0,0));
    container->addChild(menuLang);
    menuNames.push_back("Language");
    

    
    auto lblText = Label::createWithTTF("We took a shot at a puzzle, let us now if you liked it!", Constants::fontName, Constants::fontSize*0.70);
    lblText->setColor(RGB_COLOR5);
    lblText->setMaxLineWidth(visibleSize.width*0.80);
    lblText->setHorizontalAlignment(TextHAlignment::CENTER);
    auto itemText = MenuItemLabel::create(lblText, nullptr);
    itemText->setEnabled(false);
    itemText->setPosition(Point(origin.x + visibleSize.width*(0.5), origin.y + visibleSize.height*0.70));
    
    auto itemSanchitPhoto = MenuItemImage::create(IMG_SANCHIT, IMG_SANCHIT);
    itemSanchitPhoto->setScale(Util::getScreenRatio(itemSanchitPhoto)*0.2);
    itemSanchitPhoto->setPosition(Point(origin.x + visibleSize.width*(0.2), origin.y + visibleSize.height*0.50));
    
    auto textSanchit = Roundles::create("Game By","Sanchit Gulati");
    textSanchit->setPosition(Point(origin.x + visibleSize.width*(0.6), origin.y + visibleSize.height*0.50));
    textSanchit->setCallback(CC_CALLBACK_1(OptionMenu::menuCallback, this));
    textSanchit->setTag(666);
    
    auto itemRadhikaPhoto = MenuItemImage::create(IMG_RADHIKA, IMG_RADHIKA);
    itemRadhikaPhoto->setScale(Util::getScreenRatio(itemRadhikaPhoto)*0.2);
    itemRadhikaPhoto->setPosition(Point(origin.x + visibleSize.width*(0.2), origin.y + visibleSize.height*0.30));
    
    auto textRadhika = Roundles::create("UI/UX By","Radhika Dutt");
    textRadhika->setPosition(Point(origin.x + visibleSize.width*(0.6), origin.y + visibleSize.height*0.30));
    textRadhika->setCallback(CC_CALLBACK_1(OptionMenu::menuCallback, this));
    textRadhika->setTag(696);
    
    auto menuCredits = Menu::create(itemText,itemSanchitPhoto,itemRadhikaPhoto,textSanchit,textRadhika,NULL);
    menuCredits->setPosition(Point(0,0));
    container->addChild(menuCredits);
    menuNames.push_back("Credits");
    
    
    
    menuLang->setPositionX(1*visibleSize.width);
    menuCredits->setPositionX(2*visibleSize.width);
    
    
    
    //Testing
    menuSetting->setTag(101);
    menuCredits->setTag(102);
    
    auto swipeMessage = Message::create("<< swipe to see more >>");
    swipeMessage->setPosition(Point(origin.x + visibleSize.width*(0.5), origin.y + visibleSize.height*0.15));
    this->addChild(swipeMessage);
    
    _total = static_cast<int>(container->getChildrenCount());
    
    
    refreshHeader();
    
    
    //schedule update
    this->addChild(container);
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
            break;
        }
        case 666:
        {
            log("Open Twitter");
            break;
        }
        case 696:
        {
            log("Open Twitter");
            break;
        }
            
    }
}




void OptionMenu::soundCallback(cocos2d::Ref *pSender)
{
    auto item = dynamic_cast<Radio *>(pSender);
    switch (item->getSelectedIndex()) {
        case 0: //on
            CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(SOUND_MAX);
            UserDefault::getInstance()->setBoolForKey("sound", true);
            break;
        case 1: //off
            CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(0.0f);
            UserDefault::getInstance()->setBoolForKey("sound", false);
            break;
        default:
            break;
    }
}

void OptionMenu::musicCallback(cocos2d::Ref *pSender)
{
    auto item = dynamic_cast<Radio *>(pSender);
    switch (item->getSelectedIndex()) {
        case 0: //on
            CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(MUSIC_MAX);
            UserDefault::getInstance()->setBoolForKey("music", true);
            break;
        case 1: //off
            CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.0f);
            UserDefault::getInstance()->setBoolForKey("music", false);
            break;
        default:
            break;
    }
}
void OptionMenu::languageCallback(cocos2d::Ref *pSender)
{
    auto element = dynamic_cast<Node *>(pSender);
    UserDefault::getInstance()->setStringForKey("language", static_cast<char *>(element->getUserData()));
    log("Language set to %s",element->getUserData());
    UserDefault::getInstance()->flush();
    auto s = (Scene*)OptionMenu::create();
    Director::getInstance()->replaceScene(TransitionFade::create(0.5f, s,RGB_COLOR1));
}


void OptionMenu::refreshHeader()
{
    if(_header)
        _header->removeFromParentAndCleanup(true);
    
    
    _header = Header::create(menuNames.at(selectedMenu));
    _header->setEnabled(false);
    _header->setPosition(Point(origin.x + visibleSize.width*(1-0.15), origin.y + visibleSize.height*MENU_HEIGHT ));
    _header->setOpacity(0);
    _header->runAction(FadeIn::create(VFX_CONSTANT));
    this->addChild(_header);
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
    if(container->getNumberOfRunningActions() != 0)
    return;
    
    bool noMore = false;
    if(selectedMenu == _total-1)
    {
        noMore = true;
        selectedMenu = 0;
    }
    else
    selectedMenu++;
    
    auto moveOne = MoveTo::create(VFX_CONSTANT, Point(-1*selectedMenu*visibleSize.width,0));
    auto moveFailed = MoveBy::create(VFX_CONSTANT*noMore*0.50, Point(-1*noMore*visibleSize.width*0.50, 0));
    container->runAction(Sequence::create(moveFailed,moveOne, NULL));
    
    refreshHeader();
    
}
void OptionMenu::swipeRight()
{
    if(container->getNumberOfRunningActions() != 0)
    return;
    
    bool noMore = false;
    if(selectedMenu == 0)
    {
        selectedMenu = _total-1;
        noMore = true;
    }
    else
    selectedMenu--;
    
    
    auto moveOne = MoveTo::create(VFX_CONSTANT, Point(-1*selectedMenu*visibleSize.width,0));
    auto moveFailed = MoveBy::create(VFX_CONSTANT*noMore*0.50, Point(1*noMore*visibleSize.width*0.50, 0));
    container->runAction(Sequence::create(moveFailed,moveOne, NULL));
    
    refreshHeader();
}
void OptionMenu::swipeUp()
{log("up");}
void OptionMenu::swipeDown()
{log("down");}



