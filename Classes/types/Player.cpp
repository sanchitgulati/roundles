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
    capturedElements = 0;
    return true;
}

Player::Player(const char* image)
{
    
    arrow = Sprite::create(IMG_ARROW);
    arrow->setOpacity(100);
    arrow->setAnchorPoint(Point(0.5, 0.5));
    arrow->setColor(LevelXML::getBundleColorOuterAt(LevelXML::curBundleNumber));

    this->addChild(arrow);
    
    
    
    sprite = Sprite::create(image);
    sprite->setColor(RGB_COLOR7);
    sprite->setAnchorPoint(Point(0, 0));
    this->addChild(sprite);
    
    light = Sprite::create(IMG_CIRCLE_LIGHT);
    light->setAnchorPoint(Point(0, 0));
    light->setOpacity(100);
    light->setColor(LevelXML::getBundleColorOuterAt(LevelXML::curBundleNumber));
    light->runAction(RepeatForever::create(Sequence::create(FadeTo::create(1.5f,200),FadeTo::create(0.5f,100),NULL)));
    sprite->addChild(light);
    


    
    
    innerSprite = Sprite::create(image);
    innerSprite->setColor(LevelXML::getBundleColorInnerAt(LevelXML::curBundleNumber));
    innerSprite->setScale(0.5);
    auto size = sprite->getBoundingBox().size;
    innerSprite->setPosition(Point(size.width/2.0f,size.height/2.0f));
    sprite->addChild(innerSprite);
}

void Player::setScale(float scale)
{
    sprite->setScale(scale);
    auto tempCalc = sprite->getBoundingBox().size.width / arrow->getBoundingBox().size.width;
    arrow->setScale(1.5*tempCalc);
    arrow->setPosition(Point(sprite->getBoundingBox().size.width/2.0,sprite->getBoundingBox().size.height/2.0));
}

Player* Player::create(const char * image)
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

void Player::setTotalElements(int value)
{
    totalElements = value;
    innerSprite->setScale(1.0/value);
}

bool Player::capture(int type,int direction,float animationDelta)
{
    switch (type) {
        case eNull:
            log("Cannot capture NULL");
            return false;
            break;
        case eSingle:
        {
            capturedElements++;
            arrow->runAction(RotateTo::create(animationDelta,(direction + 1)*90));
            animateCircle(animationDelta);
            this->head = direction;
            return true;
            break;
        }
        default:
            return false;
            break;
    }
}

bool Player::setHead(int direction)
{
    this->head = direction;
    arrow->setRotation((direction + 1)*90);
    return true;
}

void Player::animateCircle(float animationDelta)
{
    float val = (1.0 / (totalElements-capturedElements == 0 ? 1.0 : totalElements-capturedElements));
//    val = 0.5 + val;
    innerSprite->runAction(ScaleTo::create(animationDelta, val));
}

void Player::undo(float animationDelta){
    this->capturedElements--;
    animateCircle(animationDelta);
}

