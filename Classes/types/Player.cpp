//
//  Player.cpp
//  roundels
//
//  Created by Sanchit Gulati on 15/06/14.
//
//

#include "Player.h"
#include "Constants.h"
#include "LevelXML.h"

USING_NS_CC;
using namespace cocos2d;

bool Player::init()
{
    return Node::init();
}

Player::Player()
: capturedElements(0),
_moves(0),
_animationsRunning(0)
{
//    setAnchorPoint(Point(0.5f, 0.5f));
    //Init the element with z-index smallest
    _started = CallFuncN::create(CC_CALLBACK_1(Player::animationStarted,this));
    _started->retain();
    _done = CallFuncN::create(CC_CALLBACK_1(Player::animationDone,this));
    _done->retain();
    
//    arrow = Sprite::create(IMG_ARROW);
//    arrow->setOpacity(220);
//    arrow->setAnchorPoint(Point(0.5, 0.5));
//    arrow->setColor(LevelXML::getBundleColorInnerAt(LevelXML::curBundleNumber));
//    this->addChild(arrow);
    
    
//    sprite = Sprite::create(IMG_CIRCLE_WHITE);
    sprite = Sprite::create("images/charRabbit.png");
//    sprite->setColor(RGB_COLOR7);
    sprite->setAnchorPoint(Point(0.5, 0.5));
    this->addChild(sprite);

    
//    innerSprite = Sprite::create(IMG_CIRCLE_WHITE);
//    innerSprite->setColor(LevelXML::getBundleColorInnerAt(LevelXML::curBundleNumber));
//    innerSprite->setScale(0.5);
//    auto size = sprite->getBoundingBox().size;
//    innerSprite->setPosition(Point(size.width/2.0f,size.height/2.0f));
//    sprite->addChild(innerSprite);
}

void Player::setScale(float scale)
{
    sprite->setScale(scale);
    
//    auto temp = sprite->getBoundingBox().size.width / arrow->getBoundingBox().size.width;
//    arrow->setScale(1.5*temp);
//    
//    //Re-Positioning the Arrow
//    arrow->setPosition(Point(sprite->getBoundingBox().size.width/2.0,sprite->getBoundingBox().size.height/2.0));
}

Player* Player::create()
{
    Player *pRet = new Player();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}



void Player::setHead(int direction)
{
    this->head = direction;
//    arrow->setRotation((direction + 1)*90);
    
    sprite->setRotation((direction + 1)*90);
}

void Player::setTotalElements(int value)
{
    totalElements = value+1;
//    innerSprite->setScale(1.0/value);
}

void Player::setCapturedElements(int delta)
{
    capturedElements += delta;
}

void Player::setGridPosition(int x,int y)
{
    this->x = x;
    this->y = y;
}

int Player::getX()
{
    return x;
}

int Player::getY()
{
    return y;
}

bool Player::canMove(int direction)
{
    if(_animationsRunning != 0)
    {
        log("Animation Still Playing Can't Move");
    }
    switch (direction) {
        case dLeft:
            if(this->head == dRight)
                return false;
            else
                return true;
            break;
        case dRight:
            if(this->head == dLeft)
                return false;
            else
                return true;
        case dBottom:
            if(this->head == dTop)
                return false;
            else
                return true;
            break;
        case dTop:
            if(this->head == dBottom)
                return false;
            else
                return true;
        default:
            return false;
            break;
    }
}

void Player::moveAnimation(int screen_x, int screen_y,float deltaTime)
{
    auto move = MoveTo::create(deltaTime, Point(screen_x,screen_y));
    auto move_ease_in = EaseBounceInOut::create(move->clone());
    this->runAction(Sequence::create(_started,move_ease_in,_done, NULL));
}

void Player::rotateHead(int head,float deltaTime)
{
//    arrow->runAction(Sequence::create(_started,RotateTo::create(deltaTime,(head + 1)*90),_done,NULL));
    sprite->runAction(Sequence::create(_started,RotateTo::create(deltaTime,(head + 1)*90),_done,NULL));
}

void Player::expandSoul(float deltaTime)
{
//    float val = (1.0 / (totalElements-capturedElements == 0 ? 1.0 : totalElements-capturedElements));
//    innerSprite->runAction(Sequence::create(_started,ScaleTo::create(deltaTime, val),_done,NULL));
}

void Player::contractSoul(float deltaTime)
{
//    float val = (1.0 / (totalElements-capturedElements == 0 ? 1.0 : totalElements-capturedElements));
//    innerSprite->runAction(Sequence::create(_started,ScaleTo::create(deltaTime, val),_done,NULL));
}

void Player::animationStarted(Node * sender)
{
    _animationsRunning ++;
}

void Player::animationDone(Node * sender)
{
    _animationsRunning --;
}

int Player::getMoves()
{
    return _moves;
}

void Player::setMoves(int val)
{
    _moves = val;
}
