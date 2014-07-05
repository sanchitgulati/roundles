//
//  Dingle.cpp
//  roundels
//
//  Created by Sanchit Gulati on 05/07/14.
//
//

#include "Dingle.h"
#include "Constants.h"
#include "LevelXML.h"

using namespace cocos2d;

bool Dingle::init()
{
    Node::init();
    _hp = 2;
    return true;
}

Dingle::Dingle(const char* image)
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
    
    
    dot = Sprite::create(IMG_CIRCLE_LIGHT);
    dot->setColor(LevelXML::getBundleColorInnerAt(LevelXML::curBundleNumber));
    sprite->addChild(dot);
}

void Dingle::setScale(float scale)
{
    sprite->setScale(scale);
    light->setScale(scale);
    
    
    auto size = sprite->getBoundingBox().size;
    dot->setScale(0.5);
    dot->setPosition(Point(size.width/2.0f,size.height/2.0f));
}

Dingle* Dingle::create(const char * image)
{
    Dingle *pRet = new Dingle(image);
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

int Dingle::getHP()
{
    return --_hp;
}
