//
//  Rotator.cpp
//  roundels
//
//  Created by Sanchit Gulati on 10/06/14.
//
//

#include "Rotator.h"
#include "Constants.h"
#include "Util.h"

using namespace cocos2d;

Rotator* Rotator::create(Color3B outerColor,Color3B innerColor)
{
    Rotator *pRet = new Rotator(outerColor,innerColor);
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

Rect Rotator::getBoundingBox()
{
    return outer->getBoundingBox();
}


Rotator::Rotator(Color3B outerColor,Color3B innerColor)
{
    outer = Sprite::create(IMG_CIRCLE_WHITE);
    inner = Sprite::create(IMG_CIRCLE_WHITE);
    
    outer->setAnchorPoint(Point(0.5,0.5));
    inner->setAnchorPoint(Point(0.5,0.5));
    
    outer->setColor(outerColor);
    inner->setColor(outerColor);
    
    inner->setScale(Util::getScreenRatioWidth(inner)*0.75);
    inner->setOpacity(GAME_OPACITY);
    outer->setOpacity(GAME_OPACITY);
    
    outer->setScale(inner->getScale()*0.30);
    
    
    inner->runAction( RepeatForever::create(
                                              Sequence::create(
                                                               ScaleBy::create(3,1.1),
                                                               ScaleBy::create(3,1.1)->reverse(),
                                                               NULL)
                                              ));
    
    outer->runAction( RepeatForever::create(
                                              Sequence::create(
                                                               ScaleBy::create(3,1.5),
                                                               ScaleBy::create(3,1.5)->reverse(),
                                                               NULL)
                                              ));
    
    this->addChild(outer);
    this->addChild(inner);
    this->setOpacity(GAME_OPACITY);


    
}
