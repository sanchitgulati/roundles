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

Single::Single(const char* image)
{
    sprite = Sprite::create(image);
    sprite->setAnchorPoint(Point(0, 0));
    sprite->setColor(RGB_COLOR7);
    this->addChild(sprite);
    
    light = Sprite::create(IMG_CIRCLE_LIGHT);
    light->setAnchorPoint(Point(0, 0));
    light->setOpacity(50);
    light->setColor(LevelXML::getBundleColorOuterAt(LevelXML::curBundleNumber));
    light->runAction(RepeatForever::create(Sequence::create(FadeTo::create(3.0f,150),FadeTo::create(2.0f,50),NULL)));
    this->addChild(light);
}

void Single::setScale(float scale)
{
    sprite->setScale(scale);
    light->setScale(scale);
}

Single* Single::create(const char * image)
{
    Single *pRet = new Single(image);
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

