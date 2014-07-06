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
    
    levelNode = nullptr; //CrossPlatform Shit
    
    auto ret = loadLevel();
    if(!ret)
        return false;
    
    auto temp = ((origin.x + visibleSize.width) - LevelXML::getGridSizeX()*_size)/2.0f;
    levelNode->setContentSize(Size(Point(LevelXML::getGridSizeX()*_size,LevelXML::getGridSizeY()*_size)));
    levelNode->setAnchorPoint(Point(0, 0));
    levelNode->setPosition(Point(temp,Constants::vEdgeMargin*1.5)); //hack
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
    auto scaleSprite = Sprite::create(IMG_CIRCLE_WHITE);
    // IMG_CIRCLE_WHITE should be same as circle used inside Single,PLayer,Dingle
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
            scale = 0.09f;
            break;
        default:
            log("Invalid Grid Size, raising exception!");
            return false;
            break;
    }
    scaleSprite->setScale(Util::getScreenRatio(scaleSprite)*scale);
    _size = scaleSprite->getBoundingBox().size.width*1.4f;
    _levelScale = Point(scaleSprite->getScaleX(),scaleSprite->getScaleY());
    
    if(levelNode != nullptr || reset == true)
        levelNode->removeAllChildrenWithCleanup(true);
    else
        levelNode = Node::create();
    
    /* Load Up Level */
    level = LevelXML::getCurrentLevel();
    solution = LevelXML::getSolutionLevel(); //TODO: make it like grid numbers
    
    int totalElements = 0;
    std::vector<LevelElement>::iterator toDel;
    for (std::vector<LevelElement>::iterator it = level.begin() ; it != level.end(); ++it)
    {
        switch (it->type) {
            case eStart:
            {
                
                _player = Player::create();
                _player->setGridPosition(it->x, it->y);
                _player->setHead(it->head);
                _player->setPosition(getScreenCoordinates(it->x, it->y));
                _player->setScale(_levelScale.x);
                _player->setLocalZOrder(zPlayer);
                levelNode->addChild(_player);
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
        }
    }
    level.erase(toDel); //Delete _player from Level Vector
    _player->setTotalElements(totalElements); // to be changed with diffrent element types
    
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
            loadLevel(true); //with reset flag
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
            
            
            auto _playerElement = moves.back();
            
            _player->setGridPosition(_playerElement.x, _playerElement.y);
            _player->setHead(_playerElement.head);
            _player->setCapturedElements(-1);
            
            auto deltaTime = calculateDeltaTime(_playerElement.x, _playerElement.y);
            auto screen_coor = getScreenCoordinates(_playerElement.x, _playerElement.y);
            _player->moveAnimation(screen_coor.x, screen_coor.y, deltaTime);
            _player->contractSoul(deltaTime);
            _player->rotateHead(_playerElement.head, deltaTime);
            
            
            switch (lastElement.type)
            {
                case eSingle:
                {
                    lastElement.ccElement = createCCElement(lastElement);
                    level.push_back(lastElement);
                    break;
                }
                case eDingle:
                {
                    auto flag = false;
                    for (std::vector<LevelElement>::iterator it = level.begin() ; it != level.end(); ++it)
                    {
                        if(it->x == lastElement.x && it->y == lastElement.y)
                        {
                            it->dots++;
                            auto cast = static_cast<Dingle*>(it->ccElement);
                            cast->updateDots(it->dots);
                            flag = true;
                            break;
                        }
                    }
                    if(!flag)
                    {
                        lastElement.ccElement = createCCElement(lastElement);
                        lastElement.dots = 1;
                        static_cast<Dingle *>(lastElement.ccElement)->updateDots(0+1);
                        level.push_back(lastElement);
                    }
                }
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
    updateGame();
}

Node* GameScene::createCCElement(LevelElement element)
{
    switch (element.type) {
        case eSingle:
        {
            auto CCElement = Single::create();
            CCElement->setScale(_levelScale.x);
            CCElement->setPosition(getScreenCoordinates(element.x, element.y));
            CCElement->setLocalZOrder(zSingle);
            levelNode->addChild(CCElement);
            return CCElement;
            break;
        }
        case eDingle:
        {
            auto CCElement = Dingle::create();
            CCElement->setScale(_levelScale.x);
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
            if(validMove(i, _player->getY()))
            {
                handleMove(i, _player->getY(),dLeft);
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
            if(validMove(i, _player->getY()))
            {
                handleMove(i, _player->getY(),dRight);
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
            if(validMove(_player->getX(),i))
            {
                handleMove(_player->getX(),i,dTop);
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
            if(validMove(_player->getX(),i))
            {
                handleMove(_player->getX(),i,dBottom);
                break;
            }
        }
    }
    else
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(SFX_NEGATIVE);
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
        //TODO: Animations
        LevelXML::setLevelCompletedAt(LevelXML::curLevelNumber); //TODO: Collect More Data
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
                case eSingle:
                {
                    it->dots = 0;
                    return it;
                    break;
                }
                case eDingle:
                {
                    it->dots--;
                    auto casting = static_cast<Dingle *>(it->ccElement);
                    casting->updateDots(it->dots);
                    return it;
                    break;
                }
                default:
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
    //End
    
    
    auto screen_coor = getScreenCoordinates(x, y);
    _player->moveAnimation(screen_coor.x, screen_coor.y, deltaTime);
    _player->rotateHead(head,deltaTime);
    _player->expandSoul(deltaTime);
    
    
}

void GameScene::handleMove(int grid_x,int grid_y,int head)
{
    auto it = captureElement(grid_x,grid_y);
    auto elementCaptured = static_cast<LevelElement>(*it);
    storeMoveForUndo(elementCaptured, dLeft);
    float deltaTime = calculateDeltaTime(elementCaptured.x,elementCaptured.y);
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
    return Point(x*_size,y*_size);
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

bool GameScene::validMove(int x, int y)
{
    //local copy, doesn't disturb the level vector
    auto element = getLevelElementAt(x,y);
    if(element.type != eNull)
        return true;
    return false;
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
}