//
//  Turner.cpp
//  roundels
//
//  Created by Sanchit Gulati on 06/07/14.
//
//

#include "Turner.h"

#include "Constants.h"
#include "LevelXML.h"

using namespace cocos2d;

bool Turner::init()
{
    Node::init();
    return true;
}

Turner::Turner()
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

void Turner::setScale(float scale)
{
    sprite->setScale(scale);
    
}

Turner* Turner::create()
{
    Turner *pRet = new Turner();
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
