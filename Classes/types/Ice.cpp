//
//  Ice.cpp
//  roundels
//
//  Created by Sanchit Gulati on 06/07/14.
//
//

#include "Ice.h"
#include "Constants.h"
#include "LevelXML.h"

using namespace cocos2d;

bool Ice::init()
{
    Node::init();
    return true;
}

Ice::Ice()
{
    sprite = Sprite::create(IMG_CIRCLE_WHITE);
    sprite->setColor(RGB_COLOR7);
    this->addChild(sprite);
    setContentSize(sprite->getContentSize());
    
    
    dot = Sprite::create(IMG_CIRCLE_WHITE);
    dot->setColor(Color3B::WHITE);
    auto size = sprite->getBoundingBox().size;
    dot->setScale(0.25);
    dot->setPosition(Point(size.width/2.0,size.height/2.0));
    sprite->addChild(dot);
    
}

void Ice::setScale(float scale)
{
    sprite->setScale(scale);
    
}

Ice* Ice::create()
{
    Ice *pRet = new Ice();
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


void Ice::setActive(bool value)
{
    if(value)
        dot->setColor(LevelXML::getBundleColorInnerAt(LevelXML::curBundleNumber));
    else
        dot->setColor(Color3B::WHITE);
}

