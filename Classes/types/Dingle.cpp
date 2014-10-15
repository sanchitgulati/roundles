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
    return true;
}

Dingle::Dingle()
: _dots(2)
{
    sprite = Sprite::create(IMG_CIRCLE_WHITE);
    sprite->setColor(RGB_COLOR7);
    this->addChild(sprite);
    setContentSize(sprite->getContentSize());
    
    dot = Sprite::create(IMG_CIRCLE_WHITE);
    dot->setColor(LevelXML::getBundleColorInnerAt(LevelXML::curBundleNumber));
    auto size = sprite->getBoundingBox().size;
    dot->setScale(0.5);
    dot->setPosition(Point(size.width/2.0f,size.height/2.0f));
    sprite->addChild(dot);
}

void Dingle::setScale(float scale)
{
    sprite->setScale(scale);
    
}

Dingle* Dingle::create()
{
    Dingle *pRet = new Dingle();
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

void Dingle::updateDots(int value)
{
    _dots = value;
    switch (_dots) {
        case 1:
            dot->setVisible(false);
            break;
        case 2:
            dot->setVisible(true);
        default:
            break;
    }
}
