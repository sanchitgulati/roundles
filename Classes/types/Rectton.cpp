//
//  Rectton.cpp
//  roundels
//
//  Created by Sanchit Gulati on 08/06/14.
//
//

#include "Rectton.h"

USING_NS_CC;

Rectton::Rectton(std::string text,Color3B color)
{
    this->setEnabled(true);
    this->activate();
    this->lblText = Label::create(text, Constants::fontNameBold, Constants::fontSize/2.0);
    
    this->backSprite = Sprite::create(IMG_BUTTON_WHITE);
    this->backSprite->setScale(Util::getScreenRatio(backSprite)*0.4);
    
    this->backSprite->setColor(color);
    auto sizeMenuItem = this->backSprite->getBoundingBox().size;
    this->setContentSize(sizeMenuItem);
    this->lblText->setColor(RGB_COLOR6);
    this->lblText->setAnchorPoint(Point(0.5f, 0.5f));
    
    this->addChild(backSprite);
    this->addChild(lblText);
}

Rectton* Rectton::create(std::string text,Color3B color)
{
    Rectton *pRet = new Rectton(text,color);
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
