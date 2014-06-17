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

enum{zSingle,zPlayer}; //zPlayer to be last

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
    float scale = 0.5f;
    int gridSize = (LevelXML::getGridSizeX() > LevelXML::getGridSizeY() ? LevelXML::getGridSizeX() : LevelXML::getGridSizeY());
    switch (gridSize) {
        case 3:
            scale = 0.16f;
            break;
        case 4:
            scale = 0.15f;
            break;
        case 5:
            scale = 0.14f;
            break;
        case 6:
            scale = 0.13f;
            break;
        case 7:
            scale = 0.12f;
            break;
        case 8:
            scale = 0.11f;
            break;
        case 9:
            scale = 0.10f;
            break;
        case 10:
            scale = 0.9f;
            break;
        default:
            log("Invalid Grid Size, using default 0.5f");
            return false;
            break;
    }
    scaleSprite->setScale(Util::getScreenRatio(scaleSprite)*scale);
    _size = scaleSprite->getBoundingBox().size.width*1.4f;
    
    levelNode = Node::create();
    /* Load Up Level */
    level = LevelXML::getCurrentLevel();
    std::vector<LevelElement>::iterator toDel;
    for (std::vector<LevelElement>::iterator it = level.begin() ; it != level.end(); ++it)
    {
        switch (it->type) {
            case eStart:
            {
                
                player = Player::create(IMG_CIRCLE_WHITE);
                player->x = it->x;
                player->y = it->y;
                player->setPosition(getScreenCoordinates(it->x, it->y));
                player->setScale(scale);
                player->setTotalElements(static_cast<int>(level.size())); // to be changed with diffrent element types
                player->setLocalZOrder(zPlayer);
                levelNode->addChild(player);
                toDel = it;
                break;
            }
            case eSingle:
            {
                auto element = Single::create(IMG_CIRCLE_WHITE);
                element->setScale(scale);
                element->setPosition(getScreenCoordinates(it->x, it->y));
                element->setLocalZOrder(zSingle);
                it->ccElement = element;
                levelNode->addChild(element);
                break;
            }
            default:
                break;
        }
    }
    level.erase(toDel); //Delete Player from Level Vector
    
    log("level size with %d height %d into %f",LevelXML::getGridSizeX(),LevelXML::getGridSizeY(),_size);
    levelNode->setContentSize(Size(Point(LevelXML::getGridSizeX()*_size,LevelXML::getGridSizeY()*_size)));
    levelNode->setAnchorPoint(Point(0.5, 0.5));
    levelNode->setPosition(Point(origin.x + visibleSize.width*(0.50), origin.y + visibleSize.height*0.35 ));
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
    for(int i = player->x - 1; i >= 0; i--)
    {
        auto ret = captureElementAndAnimate(i,player->y);
        if(ret)
            return;
    }
}
void GameScene::swipeRight()
{
    for(int i = player->x + 1; i <= LevelXML::getGridSizeX(); i++)
    {
        auto ret = captureElementAndAnimate(i,player->y);
        if(ret)
            return;
    }
}
void GameScene::swipeUp()
{
    for(int i = player->y + 1; i <= LevelXML::getGridSizeY(); i++)
    {
        auto ret = captureElementAndAnimate(player->x,i);
        if(ret)
            return;
    }
}
void GameScene::swipeDown()
{
    for(int i = player->y - 1; i >= 0; i--)
    {
        auto ret = captureElementAndAnimate(player->x,i);
        if(ret)
            return;
    }
}



/* ---------------------- Util -----------------------*/

Point GameScene::getScreenCoordinates(int x, int y)
{
    return Point(x*_size,y*_size);
}

LevelElement GameScene::getLevelElementAt(int x, int y,bool del)
{
    LevelElement element = LevelElement();
    element.type = eNull;
    for (std::vector<LevelElement>::iterator it = level.begin() ; it != level.end(); ++it)
    {
        if(it->x == x && it->y == y)
        {
            element = static_cast<LevelElement>(*it);
            if(del == true)
            {
                it = level.erase(it);
                break;
            }
        }
    }
    return element;
}

void GameScene::checkMoves(int x,int y)
{
    auto element = getLevelElementAt(x,y,true);
    if(element.type != eNull);
}

bool GameScene::captureElementAndAnimate(int x,int y)
{
    auto element = getLevelElementAt(x,y,true);
    if(element.type != eNull)
    {
        auto deltaX = abs(player->x - x) ;
        auto deltaY = abs(player->y - y) ;
        
        float animationDelta = (deltaX > deltaY ? deltaX : deltaY) * 0.10; // 0.10 is constant
     
        
        player->x = x;
        player->y = y;
        
        
        player->capture(element.type,animationDelta);
        
        auto move = MoveTo::create(animationDelta, getScreenCoordinates(x,y));
        auto move_ease_in = EaseBounceInOut::create(move->clone() );
        player->runAction(Sequence::create(move_ease_in, NULL));
        
        auto callFunc = CallFuncN::create(CC_CALLBACK_1(GameScene::deleteCCElementFromLevelNode,this, true));
        auto delay = DelayTime::create(animationDelta); //relative to move to of player
        element.ccElement->runAction(Sequence::create(delay,callFunc,NULL));
        return true;
    }
    return false;
}

void GameScene::deleteCCElementFromLevelNode(Node * sender,bool cleanup)
{
    sender->removeAllChildrenWithCleanup(cleanup);
}