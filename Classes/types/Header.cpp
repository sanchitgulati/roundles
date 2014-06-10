//
//  Header.cpp
//  roundels
//
//  Created by Sanchit Gulati on 09/06/14.
//
//

#include "Header.h"

USING_NS_CC;

Header::Header(std::string text,std::string image,Color3B color)
{
    this->setEnabled(true);
    this->lblText = Label::create(text, Constants::fontNameBold, Constants::fontSize*0.75);
    this->foreSprite = Sprite::create(image);
    this->backSprite = Sprite::create(IMG_CIRCLE_WHITE);
    this->backSprite->setScale(Util::getScreenRatio(backSprite)*0.2);
    this->foreSprite->setScale(Util::getScreenRatio(foreSprite)*0.15);
    this->backSprite->setColor(color);
    auto sizeMenuItem = this->backSprite->getBoundingBox().size;
    this->setContentSize(sizeMenuItem);
    this->lblText->setColor(RGB_COLOR5);
    this->lblText->setAnchorPoint(Point(1.0f, 0.5f));
    this->lblText->setPositionX(-1* sizeMenuItem.width*0.60);
    
    this->addChild(backSprite);
    this->addChild(lblText);
    this->addChild(foreSprite);
}

Header* Header::create(std::string text,std::string image,Color3B color)
{
    Header *pRet = new Header(text,image,color);
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
