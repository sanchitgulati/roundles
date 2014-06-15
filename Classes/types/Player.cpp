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
    return true;
}

Player::Player(const char* image)
{
    sprite = Sprite::create(image);
    sprite->setColor(RGB_COLOR7);
    this->addChild(sprite);
    
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

