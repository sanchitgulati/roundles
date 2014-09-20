#include "MainMenuScene.h"
#include "OptionMenu.h"
#include "LevelMenu.h"

#include "SimpleAudioEngine.h"

USING_NS_CC;

enum btnId
{
    bSetting,
    bTutorial,
    bPlay
};

Scene* MainMenu::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainMenu::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainMenu::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    /*Making Varibles Zero */
    selectedBundle = LevelXML::curBundleNumber;
    LevelXML::setCurrentBundleId(LevelXML::curBundleNumber);
    
    
    /* Touch Dispatcher */
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(MainMenu::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(MainMenu::onTouchEnded, this);
    listener->onTouchMoved = CC_CALLBACK_2(MainMenu::onTouchMoved, this);
    listener->onTouchCancelled = CC_CALLBACK_2(MainMenu::onTouchCancelled, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    /* End */

    visibleSize = Director::getInstance()->getVisibleSize();
    winSize = Director::getInstance()->getWinSize();
    origin = Director::getInstance()->getVisibleOrigin();
    fontSize = Constants::defaultFontSize*(winSize.width/480);
    Constants::fontSize = this->fontSize;
    Constants::vEdgeMargin = winSize.width/20.0f;
    
    
    
    /*Initiations Of Array */
    arrBundle = new ccArray;
    
    /* Initiation Of Variables */
    lbackground = LayerColor::create(RGBA_COLOR1, visibleSize.width, visibleSize.height);
    this->addChild(lbackground,zBg);
    
    
    
    auto btnSetting = Button::create("Setting",IMG_BUTTON_MENU,RGB_COLOR2);
    btnSetting->setPosition(Point(origin.x + visibleSize.width*0.15, origin.y + visibleSize.height*MENU_HEIGHT ));
    btnSetting->setCallback(CC_CALLBACK_1(MainMenu::menuCallback, this));
    btnSetting->setTag(bSetting);
    
    
    auto btnTutorial = Button::create("Tutorial",IMG_BUTTON_TUTORIAL,RGB_COLOR2);
    btnTutorial->setCallback(CC_CALLBACK_1(MainMenu::menuCallback, this));
    btnTutorial->setPosition(Point(origin.x + visibleSize.width*(1-0.15), origin.y + visibleSize.height*MENU_HEIGHT ));
    btnTutorial->setTag(bTutorial);
    
    /* Object Placement and other settings */
    
    lblGameName = Label::createWithBMFont(Constants::bitmapFontName,"PONDERING");
    auto gameTitle = MenuItemLabel::create(lblGameName, CC_CALLBACK_1(MainMenu::menuCallback, this));
    
    
    gameTitle->setEnabled(false);
    gameTitle->setColor(RGB_COLOR6);
    gameTitle->setScale(Util::getScreenRatio(gameTitle)*0.4);
    gameTitle->setPosition(Point(origin.x + visibleSize.width*(0.50), origin.y + visibleSize.height*MENU_HEIGHT ));
    for(int i = 0; i < lblGameName->getStringLength(); i++)
    {
        
        lblGameName->getLetter(i)->setColor(RGB_COLOR5);
        
        if(i == 1) // 1 is hardcored for "O"
        {
            //Add Compicated Animation Here
            auto delay = DelayTime::create(3.0);
            auto delaySmall = DelayTime::create(0.1f);
            
            auto moveBy = MoveBy::create(0.3f, Point(0,10));
            auto seq = Sequence::create(moveBy,moveBy->reverse(),delaySmall, NULL);
            auto sequence = Sequence::create(delay,seq,seq, NULL);
            lblGameName->getLetter(i)->runAction(RepeatForever::create(sequence));
            lblGameName->getLetter(i)->setColor(LevelXML::getBundleColorInnerAt(selectedBundle));
        }
    }
    
    //Read XML and draw Bundle Circle
    const int bundleSize = LevelXML::getTotalBundlesSize();
    
    int r = winSize.width*0.45;
    step = 2*PI/bundleSize;
    float theta= PI*0.5;
    cocos2d::Vector<MenuItem*> list;
    
    for(int i=0; i < bundleSize;i++,theta+=step)
    {
        auto txt = cocos2d::StringUtils::format("%s",LevelXML::getBundleNameAt(i).c_str());
        auto img = cocos2d::StringUtils::format("images/%s",LevelXML::getBundleImageAt(i).c_str());
        auto val = LevelXML::isUnlockedBundleAt(i);
        auto bundle = Rotator::create(img,LevelXML::getBundleColorAt(i), txt, 50.0f,!val);
        bundle->setCallback(CC_CALLBACK_1(MainMenu::menuCallback, this));
        bundle->setTag(bPlay);
        float x = r*cos(theta);
        float y = r*sin(theta);
        /* End */
        
        
        //Transferring Values
        bundle->setPosition(Point(x,y));
        list.pushBack(bundle);
    }
    //End
    
    bundleNode = Menu::createWithArray(list);
    bundleNode->setAnchorPoint(Point(0.0,0.0));
    bundleNode->setPosition(Point(origin.x + visibleSize.width*(0.50),origin.y + visibleSize.height*0.20 ));
    bundleNode->setRotation(selectedBundle*step*(180.0/PI));
    auto& children = bundleNode->getChildren();
    for(const auto &child : children)
    {
        child->setRotation(-1*selectedBundle*step*(180.0/PI));
    }
    this->addChild(bundleNode,zReloader);
    
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(btnSetting,btnTutorial,gameTitle, NULL);

    menu->setPosition(Point::ZERO);
    this->addChild(menu, zMenu);

    
    //schedule update
    this->scheduleUpdate();
    return true;
}

void MainMenu::update(float dt)
{
    
}


void MainMenu::menuCallback(Ref* pSender)
{
    //Reached Callback Notification
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(SFX_BTN_CLICKED);
    
    auto obj = (Node*)pSender;
    log("Reached menuCallback from %d",obj->getTag());
    
    switch (obj->getTag()) {
        case bPlay:
        {
            UserDefault::getInstance()->flush();
            auto s = (Scene*)LevelMenu::create();
            Director::getInstance()->replaceScene(TransitionFade::create(0.5f, s,RGB_COLOR1));
        }
            break;
        case bSetting:
        {
            auto s = (Scene*)OptionMenu::create();
            Director::getInstance()->replaceScene(TransitionFade::create(0.5f, s,RGB_COLOR1));
        }
            break;
        case bTutorial:
        {
            
        }
            break;
        default:
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
            exit(0);
#endif
            Director::getInstance()->end();
            break;
    }


}


bool MainMenu::onTouchBegan(cocos2d::Touch *touch,cocos2d::Event *event)
{
    touchStart = touch->getLocation();
    return true;
};

void MainMenu::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event)
{
    
    auto location = touch->getLocation();
    if(touchStart != Point::ZERO)
    {
        //right left
        if( touchStart.x - location.x  > SWIPE_THRESHOLD)
        {swipeLeft(location);touchStart = Point::ZERO;}
        else if(location.x - touchStart.x > SWIPE_THRESHOLD)
        {swipeRight(location);touchStart = Point::ZERO;}
        //up down
        else if(touchStart.y - location.y > SWIPE_THRESHOLD)
        {swipeDown(location);touchStart = Point::ZERO;}
        else if (location.y - touchStart.y > SWIPE_THRESHOLD)
        {swipeUp(location);touchStart = Point::ZERO;}
    }
}

void MainMenu::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
    touchStart = Point::ZERO;
}

void MainMenu::onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *event)
{
    touchStart = Point::ZERO;
}

void MainMenu::swipeLeft(Point location)
{
    //Swipe accepted, Audio feedback
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(SFX_BTN_CLICKED);
    
    int multipler = (location.y > bundleNode->getPositionY() ? 1 : -1);
    if(bundleNode->getNumberOfRunningActions() == 0 )
    {
        selectedBundle--;
        if(selectedBundle == -1)
            selectedBundle = LevelXML::getTotalBundlesSize()-1;
        changeGameNameLetterColor();
        
        
        bundleNode->runAction(Sequence::create(RotateBy::create(VFX_CONSTANT, -1*multipler*step*(180.0/PI)),DelayTime::create(0.2),NULL));
        
        auto& children = bundleNode->getChildren();
        for(const auto &child : children)
        {
            static_cast<Rotator *>(child)->animateRotation(1*multipler*step*(180.0/PI),VFX_CONSTANT+0.2); //reverse of top
        }
        
    }
    log("left");
}
void MainMenu::swipeRight(Point location)
{
    //Swipe accepted, Audio feedback
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(SFX_BTN_CLICKED);
    
    
    int multipler = (location.y > bundleNode->getPositionY() ? 1 : -1);
    if(bundleNode->getNumberOfRunningActions() == 0 )
    {
        selectedBundle++;
        if(selectedBundle == LevelXML::getTotalBundlesSize())
            selectedBundle = 0;
        changeGameNameLetterColor();
        
        bundleNode->runAction(Sequence::create(RotateBy::create(VFX_CONSTANT, 1*multipler*step*(180.0/PI)),DelayTime::create(0.2),NULL));
        
        auto& children = bundleNode->getChildren();
        for(const auto &child : children)
        {
            static_cast<Rotator *>(child)->animateRotation(-1*multipler*step*(180.0/PI),VFX_CONSTANT+0.2); //reverse of top
        }
    }
    
    
    log("right");
}
void MainMenu::swipeUp(Point location)
{log("up");}
void MainMenu::swipeDown(Point location)
{
    auto temp = Dialog::create("I am bored, are you ?");
    temp->setPosition(visibleSize.width/2, visibleSize.height/2);
    this->addChild(temp,zGameFront);
    log("down");
}


void MainMenu::changeGameNameLetterColor()
{
    LevelXML::setCurrentBundleId(selectedBundle);
    UserDefault::getInstance()->setIntegerForKey("curBundleNumber", selectedBundle);
    
    auto c = LevelXML::getBundleColorInnerAt(selectedBundle);
    lblGameName->getLetter(1)->runAction(TintTo::create(0.3f, c.r, c.g, c.b));
    
    Color4F colorInner = Color4F(LevelXML::getBundleColorInnerAt(selectedBundle));
    colorInner.a = 0.3;
}

void MainMenu::changePlayRecttonText()
{
    
}
