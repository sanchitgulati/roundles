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
    sprite = Sprite::create(image);
    sprite->setColor(RGB_COLOR7);
    sprite->setAnchorPoint(Point(0, 0));
    this->addChild(sprite);
    
    light = Sprite::create(IMG_CIRCLE_LIGHT);
    light->setAnchorPoint(Point(0, 0));
    light->setOpacity(100);
    light->setAnchorPoint(Point(0.0, 0.0));
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
//    light->setScale(1.0);
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
    innerSprite->setScale((1.0/totalElements));
}

bool Player::capture(int type,float animationDelta)
{
    switch (type) {
        case eNull:
            log("Cannot capture NULL");
            return false;
            break;
        case eSingle:
        {
            capturedElements ++;
            float val = (1.0 / (totalElements-capturedElements == 0 ? 1.01 : totalElements-capturedElements));
            innerSprite->runAction(ScaleTo::create(animationDelta, val));
            return true;
            break;
        }
        default:
            return false;
            break;
    }
}

