//
//  Single.cpp
//  roundels
//
//  Created by Sanchit Gulati on 15/06/14.
//
//

#include "Single.h"
#include "Constants.h"
#include "LevelXML.h"

using namespace cocos2d;

bool Single::init()
{
    return true;
}

Single::Single()
{
    setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    sprite = Sprite::create(IMG_CIRCLE_WHITE);
    auto c = LevelXML::getBundleColorAt(LevelXML::curBundleNumber);
    sprite->setColor(c);
    sprite->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    this->addChild(sprite);
    setContentSize(sprite->getContentSize());
    
}

void Single::setScale(float scale)
{
    sprite->setScale(scale);
    
}

Single* Single::create()
{
    Single *pRet = new Single();
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

