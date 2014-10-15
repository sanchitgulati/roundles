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

enum{bMenu,bBack,bHint,bTitle,bPrev,bNext,bRestart,bSetting,bUndo};

enum{zSingle,zDingle,zPlayer}; //z_player to be last

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
    btnBack->setPosition(Point(origin.x + visibleSize.width*0.15, origin.y + visibleSize.height*MENU_HEIGHT ));
    btnBack->setCallback(CC_CALLBACK_1(GameScene::menuCallback, this));
    btnBack->setTag(bBack);
    
    
    auto btnLevelTitle = Header::create(LevelXML::getLevelNameAt(LevelXML::curLevelNumber));
    btnLevelTitle->setPosition(Point(origin.x + visibleSize.width*(1-0.15), origin.y + visibleSize.height*MENU_HEIGHT ));
    btnLevelTitle->setCallback(CC_CALLBACK_1(GameScene::menuCallback, this));
    btnLevelTitle->setTag(bTitle);
    
    auto btnSetting = Button::create("Setting",IMG_BUTTON_MENU,RGB_COLOR2);
    btnSetting->setPosition(Point(origin.x + visibleSize.width*(1-0.15), origin.y + visibleSize.height*0.10 ));
    btnSetting->setCallback(CC_CALLBACK_1(GameScene::menuCallback, this));
    btnSetting->setTag(bSetting);
    
    auto btnPrev = Button::create("Prev",IMG_BUTTON_RESTART,RGB_COLOR2);
    btnPrev->setPosition(Point(origin.x + visibleSize.width*(0.15*1), origin.y + visibleSize.height*0.10 ));
    btnPrev->setCallback(CC_CALLBACK_1(GameScene::menuCallback, this));
    btnPrev->setTag(bPrev);
    
    auto btnNext = Button::create("Next",IMG_BUTTON_RESTART,RGB_COLOR2);
    btnNext->setPosition(Point(origin.x + visibleSize.width*(0.15*3), origin.y + visibleSize.height*0.10 ));
    btnNext->setCallback(CC_CALLBACK_1(GameScene::menuCallback, this));
    btnNext->setTag(bNext);
    
    auto btnRestart = Button::create("Restart",IMG_BUTTON_RESTART,RGB_COLOR2);
    btnRestart->setPosition(Point(origin.x + visibleSize.width*(0.15*2), origin.y + visibleSize.height*0.10 ));
    btnRestart->setCallback(CC_CALLBACK_1(GameScene::menuCallback, this));
    btnRestart->setTag(bRestart);
    
    
    auto btnHint = Button::create("Hint",IMG_BUTTON_HINT,RGB_COLOR2);
    btnHint->setPosition(Point(origin.x + visibleSize.width*(0.15 * 4), origin.y + visibleSize.height*(1-MENU_HEIGHT) ));
    btnHint->setCallback(CC_CALLBACK_1(GameScene::menuCallback, this));
    btnHint->setTag(bHint);
    
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(btnBack, btnHint,btnLevelTitle,btnSetting,btnRestart, NULL); //,btnPrev,btnNext
    menu->setTag(bMenu);
    
    
    levelNode = nullptr; //CrossPlatform Shit
    
    auto ret = loadLevel();
    if(!ret)
        return false;
    
    this->addChild(levelNode);
    
    
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, zMenu);
 
    //schedule update
    this->scheduleUpdate();
    return true;
}

bool GameScene::loadLevel(bool reset)
{
    if(reset)
    {
        moves.clear();
    }
    
    
    if(levelNode != nullptr || reset == true)
        levelNode->removeAllChildrenWithCleanup(true);
    else
        levelNode = Node::create();
    
    auto totalPixelsPerBlock = visibleSize.width/LevelXML::getGridSizeX();
    _desiredWidth = totalPixelsPerBlock*0.75;
    _margin = totalPixelsPerBlock*0.25;
    
    levelNode->setAnchorPoint(Vec2(0.0,0.5));
    levelNode->setPosition(Vec2(0,visibleSize.height*0.40));
    levelNode->setContentSize(Size(visibleSize.width, _desiredWidth*LevelXML::getGridSizeY()));
    
    
    /* Load Up Level */
    level = LevelXML::getCurrentLevel();
    solution = LevelXML::getSolutionLevel(); //TODO: make it like grid numbers
    
    for(int i = 0; i < LevelXML::getGridSizeX(); i++)
    {
        for(int j =0;j < LevelXML::getGridSizeX(); j++)
        {
            auto grid = Sprite::create(IMG_CIRCLE_WHITE);
            grid->setScale(_desiredWidth/grid->getBoundingBox().size.width);
            levelNode->addChild(grid);
            grid->setPosition(getScreenCoordinates(i, j));
            grid->setAnchorPoint(Vec2::ZERO);
        }
    }
    
    
    
    int totalElements = 0;
    std::vector<LevelElement>::iterator toDel;
    for (std::vector<LevelElement>::iterator it = level.begin() ; it != level.end(); ++it)
    {
        switch (it->type) {
            case eStart:
            {
                
                _player = Player::create(IMG_RABBIT);
                _player->setGridPosition(it->x, it->y);
                _player->setHead(it->head);
                _player->setPosition(getScreenCoordinates(it->x, it->y));
                _player->setScale(_desiredWidth/_player->getBoundingBox().size.width);
                _player->setLocalZOrder(zPlayer);
                levelNode->addChild(_player,99);
                moves.push_back(static_cast<LevelElement>(*it));
                toDel = it;
                break;
            }
            case eSingle:
            {
                auto temp = static_cast<LevelElement>(*it);
                it->ccElement = createCCElement(temp);
                it->dots = 1;
                totalElements+=it->dots;
                break;
            }
            case eDingle:
            {
                auto temp = static_cast<LevelElement>(*it);
                it->ccElement = createCCElement(temp);
                it->dots = 2;
                totalElements += it->dots; // Because use have move over it twice
                break;
            }
            case eTurner:
            {
                auto temp = static_cast<LevelElement>(*it);
                it->ccElement = createCCElement(temp);
                it->dots = 1;
                totalElements += it->dots;
                break;
            }
            case eIce:
            {
                auto temp = static_cast<LevelElement>(*it);
                it->ccElement = createCCElement(temp);
                it->dots = 1;
                totalElements += it->dots;
                break;
            }
            case eNull:
                break;
        }
    }
    level.erase(toDel); //Delete _player from Level Vector
    _player->setTotalElements(totalElements); // to be changed with diffrent element types
    
    //Start Load
    updateGame(true);
    
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
            loadLevel(true); //with reset flag
            break;
        }
        case bHint:
        {
            int i = 0;
            for (std::vector<int>::iterator it = solution.begin() ; it != solution.end(); ++it)
            {
                auto element = Label::createWithTTF("", Constants::fontName, Constants::fontSize);
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
                element->setPosition(Point(origin.x + visibleSize.width*0.5, visibleSize.height*0.75));
                auto callFunc = CallFuncN::create(CC_CALLBACK_1(GameScene::delCocos,this));
                auto delay = DelayTime::create(i*0.5f);
                auto fadein = FadeIn::create(0.2f);
                auto delaySmall = DelayTime::create(0.3f);
                element->runAction(Sequence::create(delay,fadein,delaySmall,callFunc, NULL));
                i++;
            }
            
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

Node* GameScene::createCCElement(LevelElement element)
{
    switch (element.type) {
        case eSingle:
        {
            auto CCElement = Single::create();
            CCElement->setScale(_desiredWidth/CCElement->getBoundingBox().size.width);
            CCElement->setPosition(getScreenCoordinates(element.x, element.y));
            CCElement->setLocalZOrder(zSingle);
            levelNode->addChild(CCElement);
            return CCElement;
            break;
        }
        case eDingle:
        {
            auto CCElement = Dingle::create();
            CCElement->setScale(_desiredWidth/CCElement->getBoundingBox().size.width);
            CCElement->setPosition(getScreenCoordinates(element.x, element.y));
            CCElement->setLocalZOrder(zDingle);
            levelNode->addChild(CCElement);
            return CCElement;
            break;
        }
        case eTurner:
        {
            auto CCElement = Turner::create();
            CCElement->setScale(_desiredWidth/CCElement->getBoundingBox().size.width);
            CCElement->setPosition(getScreenCoordinates(element.x, element.y));
            CCElement->setLocalZOrder(zDingle);
            levelNode->addChild(CCElement);
            return CCElement;
            break;
        }
        case eIce:
        {
            auto CCElement = Ice::create();
            CCElement->setScale(_desiredWidth/CCElement->getBoundingBox().size.width);
            CCElement->setPosition(getScreenCoordinates(element.x, element.y));
            CCElement->setLocalZOrder(zDingle);
            levelNode->addChild(CCElement);
            return CCElement;
            break;
        }
        default:
            break;
    }
    return nullptr;
}

void GameScene::toggleVisible(cocos2d::Node *node,bool value)
{
    node->setVisible(value);
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
    if(_player->canMove(dLeft) && hasMoves())
    {
        for(int i = _player->getX() - 1; i >= 0; i--)
        {
            auto type = validMove(i, _player->getY());
            if(type != eNull)
            {
                auto head = dLeft;
                handleMove(i, _player->getY(),head);
                break;
            }
        }
    }
    else
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(SFX_NEGATIVE);
    }
}
void GameScene::swipeRight()
{
    if(_player->canMove(dRight) && hasMoves())
    {
        for(int i = _player->getX() + 1; i < LevelXML::getGridSizeX(); i++)
        {
            auto type = validMove(i, _player->getY());
            if(type != eNull)
            {
                auto head = dRight;
                handleMove(i, _player->getY(),head);
                break;
            }
        }
    }
    else
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(SFX_NEGATIVE);
    }
}

void GameScene::swipeUp()
{
    if(_player->canMove(dTop) && hasMoves())
    {
        for(int i = _player->getY() + 1; i < LevelXML::getGridSizeY(); i++)
        {
            auto type = validMove(_player->getX(),i);
            if(type != eNull)
            {
                
                auto head = dTop;
                handleMove(_player->getX(),i,head);
                break;
            }
        }
    }
    else
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(SFX_NEGATIVE);
    }
}
void GameScene::swipeDown()
{
    if(_player->canMove(dBottom) && hasMoves())
    {
        for(int i = _player->getY() - 1; i >=  0; i--)
        {
            auto type = validMove(_player->getX(),i);
            if(type != eNull)
            {
                auto head = dBottom;
                handleMove(_player->getX(),i,head);
                break;
            }
        }
    }
    else
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(SFX_NEGATIVE);
    }
}

void GameScene::updateGame(bool init)
{
    if(!init)
    {
        std::vector<LevelElement>::iterator it;
        for (it = level.begin() ; it != level.end(); ++it)
        {
            switch (it->type) {
                case eIce:
                    if( (it->metaType - _player->getMoves()) <= 0)
                    {
                        auto temp = static_cast<Ice *>(it->ccElement);
                        temp->setActive(true);
                    }
                    break;
                default:
                    break;
            }
        }
    }
    
    if(level.size() == 0lu)
    {
        log("You Win");
        LevelXML::setLevelCompletedAt(LevelXML::curLevelNumber); //TODO: Collect More Data
        _player->setVisible(false); // make the ugly go away.
        //TODO: Animations
        //TODO: Check is to unlock new bundle
    }
    else
    {
        auto ret = hasMoves();
        if(!ret)
            log("You Lose");
    }
    
}


std::vector<LevelElement>::iterator GameScene::captureElement(int x, int y)
{
    std::vector<LevelElement>::iterator it;
    for (it = level.begin() ; it != level.end(); ++it)
    {
        if(it->x == x && it->y == y)
        {
            switch (it->type) {
                case eDingle:
                {
                    it->dots--;
                    auto casting = static_cast<Dingle *>(it->ccElement);
                    casting->updateDots(it->dots);
                    return it;
                    break;
                }
                default:
                    it->dots = 0;
                    return it;
                    break;
            }
        }
    }
    CCASSERT(false, "SOMETHING WENT WRONG in GameScene::captureElement");
    return it;
}

void GameScene::updatePlayer(int x,int y,int head,float deltaTime)
{
    //Move _player to new location, but Animation Happens Later
    _player->setGridPosition(x, y);
    _player->setHead(head);
    _player->setCapturedElements(1); //delta +1
    _player->setMoves(_player->getMoves()+1);
    //End
    
    
    auto screen_coor = getScreenCoordinates(x, y);
    _player->rotateHead(head,deltaTime);
    _player->moveAnimation(screen_coor.x, screen_coor.y, deltaTime,deltaTime);
    
    
}

void GameScene::handleMove(int grid_x,int grid_y,int head)
{
    auto it = captureElement(grid_x,grid_y);
    auto elementCaptured = static_cast<LevelElement>(*it);
    storeMoveForUndo(elementCaptured, dLeft);
    float deltaTime = calculateDeltaTime(elementCaptured.x,elementCaptured.y);
    
    //Exceptions for turner
    switch (elementCaptured.type) {
        case eTurner:
            head = elementCaptured.metaType;
            break;
        default:
            break;
    }
    updatePlayer(elementCaptured.x,elementCaptured.y, head, deltaTime);
    
    if(it->dots == 0)
    {
        auto callFunc = CallFuncN::create(CC_CALLBACK_1(GameScene::deleteCCElementFromLevelNode,this, true));
        auto delay = DelayTime::create(deltaTime);
        it->ccElement->runAction(Sequence::create(delay,callFunc,NULL));
        level.erase(it);
        
    }
}


void GameScene::storeMoveForUndo(LevelElement element, int head)
{
    element.head = head;
    moves.push_back(element);
}

/* ---------------------- Util -----------------------*/

Point GameScene::getScreenCoordinates(int x, int y)
{
    return Point((x+0.5)*_margin + x*_desiredWidth,(y+0.5)*_margin + y*_desiredWidth);
}

LevelElement GameScene::getLevelElementAt(int x, int y)
{
    LevelElement element = LevelElement();
    element.type = eNull;
    for (std::vector<LevelElement>::iterator it = level.begin() ; it != level.end(); ++it)
    {
        if(it->x == x && it->y == y)
        {
            element = static_cast<LevelElement>(*it);
            return element;
        }
    }
    return element;
}

eType GameScene::validMove(int x, int y)
{
    //local copy, doesn't disturb the level vector
    auto element = getLevelElementAt(x,y);
    if(element.type != eNull)
    {
        switch (element.type) {
            case eIce:
                if( (element.metaType - _player->getMoves()) <= 0)
                    return element.type;
                else
                    return eNull;
                break;
                
            default:
                return element.type;
                break;
        }
    }
    return eNull;
}

bool GameScene::hasMoves()
{
    auto x = _player->getX();
    auto y = _player->getY();
    
    for(int i = x - 1; i >= 0; i--)
    {
        auto ret = validMove(i, y);
        if(ret)
            return true;
    }
    for(int i = x + 1; i < LevelXML::getGridSizeX(); i++)
    {
        auto ret = validMove(i,y);
        if(ret)
            return true;
    }
    for(int i = y + 1; i < LevelXML::getGridSizeY(); i++)
    {
        auto ret = validMove(x,i);
        if(ret)
            return true;
    }
    for(int i = y - 1; i >= 0; i--)
    {
        auto ret = validMove(x,i);
        if(ret)
            return true;
    }
    return false;
}

float GameScene::calculateDeltaTime(int x,int y)
{
    auto px = _player->getX();
    auto py = _player->getY();
    
    auto deltaX = abs(px - x) ;
    auto deltaY = abs(py - y) ;
    
    float deltaTime = (deltaX > deltaY ? deltaX : deltaY) * ANIMATION_CONSTANT; // 0.10 is constant
    return deltaTime;
    
}

void GameScene::deleteCCElementFromLevelNode(Node * sender,bool cleanup)
{
    sender->removeAllChildrenWithCleanup(cleanup);
    updateGame(); //also update the game
}