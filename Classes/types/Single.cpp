//
//  Single.cpp
//  roundels
//
//  Created by Sanchit Gulati on 15/06/14.
//
//

#include "Single.h"
#include "Constants.h"

using namespace cocos2d;

bool Single::init()
{
    return true;
}

Single::Single(const char* image)
{
    sprite = Sprite::create(image);
    sprite->setColor(RGB_COLOR7);
    this->addChild(sprite);
}

void Single::setScale(float scale)
{
    sprite->setScale(scale);
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

