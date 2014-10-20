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

Player::Player(const char* image)
: capturedElements(0),
_moves(0),
_animationsRunning(0)
{
    _started = CallFuncN::create(CC_CALLBACK_1(Player::animationStarted,this));
    _started->retain();
    _done = CallFuncN::create(CC_CALLBACK_1(Player::animationDone,this));
    _done->retain();
    
    
    sprite = Sprite::create(image);
    setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    sprite->setColor(LevelXML::getBundleColorInnerAt(LevelXML::curBundleNumber));
    auto eyes = Sprite::create("images/eyes_01.png");
    eyes->setPosition(sprite->getBoundingBox().size.width*0.40,sprite->getBoundingBox().size.height*0.70);
    sprite->addChild(eyes);
    sprite->setFlippedX(true);
    setContentSize(sprite->getContentSize());
    this->addChild(sprite);
}

void Player::setScale(float scale)
{
    sprite->setScale(scale);
    auto size = sprite->getBoundingBox().size;
    sprite->setPosition(size.width/2,size.height/2);
}

Player* Player::create(const char* image)
{
    Player *pRet = new Player(image);
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
//    sprite->setRotation((direction + 1)*90);
}

void Player::setTotalElements(int value)
{
    totalElements = value+1;
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
    auto move_ease_in = EaseQuadraticActionInOut::create(move->clone());
    this->runAction(Sequence::create(_started,move_ease_in,_done, NULL));
}

void Player::rotateHead(int head,float deltaTime)
{
//    arrow->runAction(Sequence::create(_started,RotateTo::create(deltaTime,(head + 1)*90),_done,NULL));
//    sprite->runAction(Sequence::create(_started,RotateTo::create(deltaTime,(head + 1)*90),_done,NULL));
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
