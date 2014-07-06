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
    Node::init();
    return true;
}

Single::Single()
{
    setAnchorPoint(Point(0.5f, 0.5f));
    sprite = Sprite::create(IMG_CIRCLE_WHITE);
    sprite->setAnchorPoint(Point(0, 0));
    sprite->setColor(RGB_COLOR7);
    this->addChild(sprite);
    
    
    dot = Sprite::create(IMG_CIRCLE_WHITE);
    dot->setAnchorPoint(Point(0.5, 0.5));
    dot->setColor(LevelXML::getBundleColorInnerAt(LevelXML::curBundleNumber));
    auto size = sprite->getBoundingBox().size;
    dot->setScale(0.25);
    dot->setPosition(Point(size.width/2.0,size.height/2.0));
    sprite->addChild(dot);
    
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

