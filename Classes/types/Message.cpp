//
//  Message.cpp
//  roundels
//
//  Created by Sanchit Gulati on 11/06/14.
//
//

#include "Message.h"
USING_NS_CC;

Message* Message::create(std::string text)
{
    Message *pRet = new Message(text);
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


Message::Message(std::string text)
{
    auto localContent = LocalizedString::localizedString(text.c_str())->getCString();
    lblText = Label::create(localContent, Constants::fontName, Constants::fontSize*0.75);
    lblText->setColor(RGB_COLOR5);
    lblText->setAnchorPoint(Point(0.5f, 0.5f));
    this->addChild(lblText);
    auto winSize = Director::getInstance()->getWinSize();
    auto swipeIn = EaseOut::create(MoveBy::create(1.0f, Point(winSize.width/8,0)),1.0f);
    auto swipeOut = EaseOut::create(MoveBy::create(2.0f, Point(-1*winSize.width/4,0)),1.0f);
    lblText->runAction(RepeatForever::create(Sequence::create( FadeOut::create(1.0f),
                                         FadeIn::create(1.0f),
                                         swipeIn,
                                         swipeOut,
                                         swipeIn
                                        , NULL)));
}