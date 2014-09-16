//
//  Dialog.cpp
//  roundels
//
//  Created by Sanchit Gulati on 09/08/14.
//
//

#include "Dialog.h"
#include "Constants.h"
#include "Util.h"

using namespace cocos2d;


Dialog::Dialog(std::string text)
{
    box = Sprite::create(IMG_RECT_WHITE);
    box->setScaleX(Util::getScreenRatioWidth(box));
    box->setScaleY(Util::getScreenRatioHeight(box)*0.3);
    box->setColor(RGB_COLOR7);
    this->addChild(box);
    
    auto localContent = LocalizedString::localizedString(text.c_str())->getCString();
    lblText = Label::createWithTTF(localContent, Constants::fontName, Constants::fontSize/2.0);
    lblText->setHorizontalAlignment(TextHAlignment::CENTER);
    this->addChild(lblText);
    
    
    auto getpos = getPosition();
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto newPosition = Point(getpos.x,visibleSize.height + getBoundingBox().size.height/2 );
    
    auto resetPos = MoveTo::create(0, newPosition);
    auto magic = EaseBounceOut::create(MoveTo::create(1.0, getpos));
    
    this->runAction(Sequence::create(resetPos,magic, NULL));
    
}



Dialog* Dialog::create(std::string text)
{
    Dialog *pRet = new Dialog(text);
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

void Dialog::setCallback(cocos2d::Ref* target)
{
    this->mTarget = target;
}
