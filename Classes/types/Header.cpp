//
//  Header.cpp
//  roundels
//
//  Created by Sanchit Gulati on 09/06/14.
//
//

#include "Header.h"

USING_NS_CC;

Header::Header(std::string text)
{
    this->setEnabled(true);
    this->lblText = Label::createWithTTF(text, Constants::fontNameBold, Constants::fontSize*0.75);
    this->lblText->setColor(RGB_COLOR1);
    this->lblText->setAnchorPoint(Point(1.0f, 0.5f));
    this->lblText->setHorizontalAlignment(TextHAlignment::RIGHT);
    this->lblText->setOpacity(0);
    
    auto delta = Point(0, 30); //hack
    
    this->lblText->setPositionY(delta.y);
    
    auto fadeIn = FadeIn::create(VFX_CONSTANT);
    auto moveBy = MoveBy::create(VFX_CONSTANT, Point(delta.x,delta.y*-1));
    this->lblText->runAction(fadeIn);
    this->lblText->runAction(moveBy);
    this->addChild(lblText);
}

Header* Header::create(std::string text)
{
    Header *pRet = new Header(text);
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
