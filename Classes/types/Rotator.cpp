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

Rotator* Rotator::create(Color3B color,std::string text,float percentage,bool locked)
{
    Rotator *pRet = new Rotator(color,text,percentage,locked);
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


Rotator::Rotator(Color3B color,std::string text,float percentage,bool locked)
{
    outer = ProgressTimer::create(Sprite::create(IMG_CIRCLE_WHITE_HI));
    outer->setType( ProgressTimer::Type::RADIAL );
    inner = Sprite::create(IMG_CIRCLE_WHITE_HI);
    
    outer->setAnchorPoint(Point(0.5,0.5));
    inner->setAnchorPoint(Point(0.5,0.5));
    
    outer->setColor(color);
    inner->setColor(color);
    
    outer->setScale(Util::getScreenRatioWidth(outer)*0.70);
    
    outer->setOpacity(0);
    
    inner->setScale(Util::getScreenRatioWidth(inner)*0.65);
    
    
    auto delayTime = DelayTime::create(0.2);
    auto fadeIn = FadeTo::create(0.1, GAME_OPACITY);
    auto progressTo = ProgressTo::create(2*VFX_CONSTANT, 50);
    outer->runAction(Sequence::create(delayTime,fadeIn,progressTo, NULL));
    
    auto action = RepeatForever::create(
                                        Sequence::create(
                                                         ScaleBy::create(3,1.10),
                                                         ScaleBy::create(3,1.10)->reverse(),
                                                         NULL)
                                        );
    
    outer->runAction( action);
    
    inner->runAction( action->clone());
    
    
    this->addChild(outer);
    this->addChild(inner);
    
    
    if(locked)
    {
        auto lock = Sprite::create(IMG_LOCK);
        lock->setScale((inner->getBoundingBox().size.height/lock->getBoundingBox().size.height)*0.30);
        lock->runAction(action->clone());
        this->addChild(lock);
    }
    else
    {
        auto textLbl = Label::create(text, Constants::fontName, Constants::fontSize*1.5);
        textLbl->setAnchorPoint(Point(0.5,0.5));
        textLbl->setColor(RGB_COLOR1);
        textLbl->getTexture()->setAliasTexParameters();
        textLbl->runAction(action->clone());
        this->addChild(textLbl);
    }
}



void Rotator::animateRotation(float val,float time)
{
    auto& children = this->getChildren();
    for(const auto &child : children)
    {
        child->runAction(Sequence::create(RotateBy::create(time, val),NULL));
    }
}

void Rotator::setRotation(float val)
{
    auto& children = this->getChildren();
    for(const auto &child : children)
    {
        child->setRotation(val);
    }
}