//
//  Button.cpp
//  roundels
//
//  Created by Sanchit Gulati on 08/06/14.
//
//

#include "Button.h"

USING_NS_CC;

Button::Button(std::string text,std::string image,Color3B color)
{
    this->setEnabled(true);
    this->lblText = Label::create(text, Constants::fontNameLight, Constants::fontSize/2.0);
    this->foreSprite = Sprite::create(image);
    this->backSprite = Sprite::create(IMG_CIRCLE_WHITE);
    this->backSprite->setScale(Util::getScreenRatio(backSprite)*0.2);
    this->foreSprite->setScale(Util::getScreenRatio(foreSprite)*0.15);
    this->backSprite->setColor(color);
    auto sizeMenuItem = this->backSprite->getBoundingBox().size;
    this->setContentSize(sizeMenuItem);
    this->lblText->setColor(Color3B::BLACK);
    this->lblText->setAnchorPoint(Point(0.5f, 0.5f));
    this->lblText->setPositionY(-1* sizeMenuItem.height*0.70);
    
    this->addChild(backSprite);
    this->addChild(lblText);
    this->addChild(foreSprite);
}

Button* Button::create(std::string text,std::string image,Color3B color)
{
    Button *pRet = new Button(text,image,color);
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


