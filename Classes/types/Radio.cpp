//
//  Radio.cpp
//  roundels
//
//  Created by Sanchit Gulati on 09/06/14.
//
//

#include "Radio.h"
#include "Constants.h"
#include "Util.h"

USING_NS_CC;

Radio::Radio(std::string text)
{
    this->setEnabled(true);
    lblText = Label::create(text, Constants::fontName, Constants::fontSize*0.70);
    lblText->setAnchorPoint(Point(0.0f,0.5f));
    lblText->setColor(Color3B(LOGO_RGB));
    
    circle = Sprite::create(IMG_CIRCLE_WHITE);
    circle->setScale(Util::getScreenRatio(circle)*0.1);
    
    bar = Sprite::create(IMG_RECT_WHITE);
    bar->setScaleY(Util::getScreenRatio(bar)*0.1);
    bar->setScaleX(Util::getScreenRatio(bar)*0.70);
    
    
    on = MenuItemImage::create(IMG_CIRCLE_WHITE, IMG_CIRCLE_WHITE);
    off = MenuItemImage::create(IMG_CIRCLE_WHITE, IMG_CIRCLE_WHITE);
    on->setScale(Util::getScreenRatio(on)*0.125);
    off->setScale(Util::getScreenRatio(off)*0.125);
    
    tick = Sprite::create(IMG_TICK_GREEN);
    tick->setScale(Util::getScreenRatio(tick)*0.125);
    
    auto barSize = bar->getBoundingBox().size;
    
    circle->setPositionX(-1*(barSize.width/2.0f));
    lblText->setPositionX(-1*(barSize.width/2.0f));
    on->setPositionX(1*(barSize.width/2.0f));
    off->setPositionX(1*(barSize.width/2.0f));
    
    circle->setColor(Color3B::GRAY);
    bar->setColor(Color3B::GRAY);
    
    
    on->setColor(Color3B(LOGO_RGB));
    off->setColor(Color3B(LOGO_RGB));
    
    this->addChild(circle);
    this->addChild(bar);
    this->addChild(on);
    this->addChild(off);
    this->addChild(lblText);
}

Radio* Radio::create(std::string text)
{
    Radio *pRet = new Radio(text);
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


