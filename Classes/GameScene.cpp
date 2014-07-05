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

enum{bMenu,bBack,bHint,bRestart,bUndo};

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
    isAnimation = false;
    
    /* Initiation Of Variables */
    lbackground = LayerColor::create(RGBA_COLOR1, visibleSize.width, visibleSize.height);
    this->addChild(lbackground,zBg);
    
    
    auto emitter = ParticleSystemQuad::create("particleTexture.plist");
    Util::loadParticleDefaults(emitter);
    this->addChild(emitter,zBg);
    
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
    
    
    
    btnUndo = Sideton::create("Undo",IMG_BUTTON_UNDO,RGB_COLOR2);
    btnUndo->setPosition(Point(origin.x + visibleSize.width*.50, origin.y + visibleSize.height*.10 ));
    btnUndo->setCallback(CC_CALLBACK_1(GameScene::menuCallback, this));
    btnUndo->setTag(bUndo);
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(btnBack, btnHint,btnRestart,btnUndo, NULL);
    menu->setTag(bMenu);
    
    
    //That Circle in the backgroud
    auto backgroundCircle = Sprite::create(IMG_CIRCLE_WHITE);
    backgroundCircle->setScale(Util::getScreenRatioWidth(backgroundCircle)*1.2);
    backgroundCircle->setColor(LevelXML::getBundleColorInnerAt(LevelXML::curBundleNumber));
    backgroundCircle->setPosition(Point(origin.x + visibleSize.width*(0.50), origin.y + visibleSize.height*0.35 ));
    _topCircle = backgroundCircle->getPosition().y + backgroundCircle->getBoundingBox().size.height/2.0;
    this->addChild(backgroundCircle);
    
    
    auto ret = loadLevel();
    if(!ret)
        return false;
    
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

bool GameScene::loadLevel(bool reset)
{
    
    /*Getting Scale For Future Use */
    scaleSprite = Sprite::create(IMG_CIRCLE_WHITE);
    scaleSprite->retain(); //TODO: del on ~GameScene
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
            log("Invalid Grid Size, raising exception!");
            return false;
            break;
    }
    scaleSprite->setScale(Util::getScreenRatio(scaleSprite)*scale);
    _size = scaleSprite->getBoundingBox().size.width*1.4f;
    
    if(levelNode)
        levelNode->removeAllChildrenWithCleanup(true);
    else
        levelNode = Node::create();
    
    /* Load Up Level */
    level = LevelXML::getCurrentLevel();
    solution = LevelXML::getSolutionLevel();
    int totalElements = 0;
    
    std::vector<LevelElement>::iterator toDel;
    for (std::vector<LevelElement>::iterator it = level.begin() ; it != level.end(); ++it)
    {
        switch (it->type) {
            case eStart:
            {
                
                player = Player::create(IMG_CIRCLE_WHITE);
                player->x = it->x;
                player->y = it->y;
                player->setHead(it->head);
                player->setPosition(getScreenCoordinates(it->x, it->y));
                player->setScale(scaleSprite->getScale());
                player->setLocalZOrder(zPlayer);
                levelNode->addChild(player);
                moves.push_back(static_cast<LevelElement>(*it));
                toDel = it;
                break;
            }
            case eSingle:
            {
                auto temp = static_cast<LevelElement>(*it);
                it->ccElement = createElement(temp);
                totalElements+=1;
                break;
            }
            case eDingle:
            {
                auto temp = static_cast<LevelElement>(*it);
                it->ccElement = createElement(temp);
                totalElements+=2; // Because use have move over it twice
                break;
            }
        }
    }
    level.erase(toDel); //Delete Player from Level Vector
    player->setTotalElements(totalElements); // to be changed with diffrent element types
    
    //Start Load
    updateGame();
    
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
//            auto s = (Scene*)GameScene::create();
//            Director::getInstance()->replaceScene(TransitionFade::create(0.5f, s,RGB_COLOR1));
            loadLevel(true);
            break;
        }
        case bHint:
        {
            int i = 0;
            for (std::vector<int>::iterator it = solution.begin() ; it != solution.end(); ++it)
            {
                auto element = Label::create("", Constants::fontName, Constants::fontSize);
                switch ((int)*it) {
                    case dTop:
                        element->setString("Up");
                        break;
                    case dBottom:
                        element->setString("Down");
                        break;
                    case dLeft:
                        element->setString("Left");
                        break;
                    case dRight:
                        element->setString("Right");
                        break;
                    default:
                        element->setString("i dont know , lol");
                        break;
                }
                this->addChild(element,zGameFront);
                element->setOpacity(0);
                element->setAnchorPoint(Point(0.5f, 0.0));
                element->setColor(Color3B(RGB_COLOR7));
                element->setPosition(Point(origin.x + visibleSize.width*0.5, _topCircle));
                auto callFunc = CallFuncN::create(CC_CALLBACK_1(GameScene::delCocos,this));
                auto delay = DelayTime::create(i*0.5f);
                auto fadein = FadeIn::create(0.2f);
                auto delaySmall = DelayTime::create(0.3f);
                element->runAction(Sequence::create(delay,fadein,delaySmall,callFunc, NULL));
                i++;
            }
            
            break;
        }
        case bUndo:
        {
            if(moves.size() == 1)
                break;
            
            auto lastElement = moves.back();
            moves.pop_back();
            
            
            auto playerElement = moves.back();
            lastElement.ccElement = createElement(lastElement);
            level.push_back(lastElement);
            
            int head = playerElement.head;   //TODO: Implement direction logic.
            auto deltaX = abs(playerElement.x - player->x) ;
            auto deltaY = abs(playerElement.x - player->x) ;
            
            float animationDelta = (deltaX > deltaY ? deltaX : deltaY) * 0.10; // 0.10 is constant
            
            player->x = playerElement.x;
            player->y = playerElement.y;
            
            
            player->capture(playerElement.type,head,animationDelta,true);
            
            auto move = MoveTo::create(animationDelta, getScreenCoordinates(playerElement.x,playerElement.y));
            auto move_ease_in = EaseBounceInOut::create(move->clone() );
            player->runAction(Sequence::create(move_ease_in, NULL));
            player->undo(animationDelta); //to make center small
            
            
            //TODO:
            //make it's center smaller
            
            
            log("Undo Pressed");
            break;
        }
        default:
            Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
            exit(0);
            break;
#endif
    }
    updateGame();
}

Node* GameScene::createElement(LevelElement element)
{
    switch (element.type) {
        case eStart:
        {
            break;
        }
        case eSingle:
        {
            auto CCElement = Single::create(IMG_CIRCLE_WHITE);
            CCElement->setScale(scaleSprite->getScale());
            CCElement->setPosition(getScreenCoordinates(element.x, element.y));
            CCElement->setLocalZOrder(zSingle);
            levelNode->addChild(CCElement);
            return CCElement;
            break;
        }
        case eDingle:
        {
            auto CCElement = Dingle::create(IMG_CIRCLE_WHITE);
            CCElement->setScale(scaleSprite->getScale());
            CCElement->setPosition(getScreenCoordinates(element.x, element.y));
            CCElement->setLocalZOrder(zSingle);
            levelNode->addChild(CCElement);
            return CCElement;
            break;
        }
        default:
            break;
    }
    return Node::create();
}

void GameScene::delCocos(cocos2d::Node *node)
{
    node->removeFromParentAndCleanup(true);
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
        {swipeLeft();updateGame();touchStart = Point::ZERO;}
        else if(location.x - touchStart.x > SWIPE_THRESHOLD)
        {swipeRight();updateGame();touchStart = Point::ZERO;}
        //up down
        else if(touchStart.y - location.y > SWIPE_THRESHOLD)
        {swipeDown();updateGame();touchStart = Point::ZERO;}
        else if (location.y - touchStart.y > SWIPE_THRESHOLD)
        {swipeUp();updateGame();touchStart = Point::ZERO;}
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
    if(player->head == dRight)
    {
        log("Head is at Right,can't go Left");
        return;
    }
    for(int i = player->x - 1; i >= 0; i--)
    {
        auto ret = captureElementAndAnimate(i,player->y,dLeft);
        if(ret)
            return;
    }
}
void GameScene::swipeRight()
{
    if(player->head == dLeft)
    {
        log("Head is at Left, can't go Right");
        return;
    }
    for(int i = player->x + 1; i <= LevelXML::getGridSizeX(); i++)
    {
        auto ret = captureElementAndAnimate(i,player->y,dRight);
        if(ret)
            return;
    }
}
void GameScene::swipeUp()
{
    if(player->head == dBottom)
    {
        log("Head is at bottom, can't go Up");
        return;
    }
    for(int i = player->y + 1; i <= LevelXML::getGridSizeY(); i++)
    {
        auto ret = captureElementAndAnimate(player->x,i,dTop);
        if(ret)
            return;
    }
}
void GameScene::swipeDown()
{
    if(player->head == dTop)
    {
        log("Head is at Top, can't go Down");
        return;
    }
    for(int i = player->y - 1; i >= 0; i--)
    {
        auto ret = captureElementAndAnimate(player->x,i,dBottom);
        if(ret)
            return;
    }
}

void GameScene::updateGame()
{
    //Disable/Enable Undo Button
    if(moves.size() == 1lu )
    {
        btnUndo->setEnabled(false);
    }
    else
    {
        btnUndo->setEnabled(true);
    }
    if(level.size() == 0lu)
    {
        log("You Win");
        //Animation
        //TODO: Animations
        LevelXML::setLevelCompletedAt(LevelXML::curLevelNumber);
    }
    else
    {
        auto ret = checkMoves();
        if(!ret)
            log("You Lose");
    }
    
}

/* ---------------------- Util -----------------------*/

Point GameScene::getScreenCoordinates(int x, int y)
{
    return Point(x*_size,y*_size);
}

LevelElement GameScene::getLevelElementAt(int x, int y,bool del,int head)
{
    LevelElement element = LevelElement();
    element.type = eNull;
    for (std::vector<LevelElement>::iterator it = level.begin() ; it != level.end(); ++it)
    {
        if(it->x == x && it->y == y)
        {
            element = static_cast<LevelElement>(*it);
            if(del == true && head != -1)
            {
                element.head = head; // changing the head so we can so undo correctly
                moves.push_back(element);
                it = level.erase(it);
                break;
            }
        }
    }
    return element;
}

bool GameScene::checkMove(int x, int y)
{
    auto element = getLevelElementAt(x,y,false);
    if(element.type == eNull)
        return false;
    else
        return true;
}

bool GameScene::checkMoves()
{
    for(int i = player->x - 1; i >= 0; i--)
    {
        auto ret = checkMove(i, player->y);
        if(ret)
            return true;
    }
    for(int i = player->x + 1; i <= LevelXML::getGridSizeX(); i++)
    {
        auto ret = checkMove(i,player->y);
        if(ret)
            return true;
    }
    for(int i = player->y + 1; i <= LevelXML::getGridSizeY(); i++)
    {
        auto ret = checkMove(player->x,i);
        if(ret)
            return true;
    }
    for(int i = player->y - 1; i >= 0; i--)
    {
        auto ret = checkMove(player->x,i);
        if(ret)
            return true;
    }
    return false;
}

bool GameScene::captureElementAndAnimate(int x,int y,int direction)
{
    if(isAnimation)
        return false;
    
    auto element = getLevelElementAt(x,y,true,direction);
    if(element.type == eNull)
        return false;
    
    isAnimation = true;
    
    auto deltaX = abs(player->x - x) ;
    auto deltaY = abs(player->y - y) ;
    
    float animationDelta = (deltaX > deltaY ? deltaX : deltaY) * 0.10; // 0.10 is constant
    
    
    player->x = x;
    player->y = y;
    
    //TODO: move below code to getLevelElementAt
    
    auto toDel = true;
//
//    switch (element.type) {
//        case eNull:
//            break;
//        case eStart:
//            break;
//        case eSingle:
//            break;
//        case eDingle:
//            if(element.ccElement->getHP() == 0)
//                toDel = true;
//            toDel = false;
//            break;
//        default:
//            break;
//    }
    
    player->capture(element.type,direction,animationDelta);
    
    auto move = MoveTo::create(animationDelta, getScreenCoordinates(x,y));
    auto move_ease_in = EaseBounceInOut::create(move->clone() );
    player->runAction(Sequence::create(move_ease_in, NULL));
    
    if(toDel)
    {
        auto callFunc = CallFuncN::create(CC_CALLBACK_1(GameScene::deleteCCElementFromLevelNode,this, true));
        auto delay = DelayTime::create(animationDelta); //relative to move to of player
        element.ccElement->runAction(Sequence::create(delay,callFunc,NULL));
    }
    return true;
}

void GameScene::deleteCCElementFromLevelNode(Node * sender,bool cleanup)
{
    sender->removeAllChildrenWithCleanup(cleanup);
    isAnimation = false;
}