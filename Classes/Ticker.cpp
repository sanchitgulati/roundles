//  Ticker.cpp
//  OneClosedLoop
//
//  Created by Sanchit Gulati on 23/03/14.
//
//

#include "Ticker.h"

USING_NS_CC;

Ticker::Ticker(std::string *messageArray, int size, const char *fontName, int fontSize, float delay) {
    _messageArray = messageArray;
    _size = size;
    _delay = delay;
    
    lblTicker = Label::createWithTTF(_messageArray[0].c_str(), fontName, fontSize);
    this->addChild(lblTicker);
    ctr = 0;
    
    schedule(schedule_selector(Ticker::updateTicker), _delay);
}



Ticker* Ticker::create(std::string *messageArray, int size, const char* fontName, int fontSize, float delay) {
    Ticker *ticker = new Ticker(messageArray, size, fontName, fontSize, delay);
    ticker->autorelease();
    return ticker;
}

void Ticker::updateTicker(float f) {
    FadeOut *fadeOutAction = FadeOut::create(_delay/4);
    FadeIn *fadeInAction = FadeIn::create(_delay/4);
    
    CallFunc *callAction = CallFunc::create(CC_CALLBACK_0(Ticker::updateString,this));
    lblTicker->runAction(Sequence::create(fadeOutAction, callAction, fadeInAction, NULL));
}

void Ticker::updateString() {
    ctr++;
    if (ctr == _size) {
        ctr = 0;
    }
    
    lblTicker->setString(_messageArray[ctr].c_str());
}

void Ticker::setAnchorPoint(Point p)
{
//    this->setAnchorPoint(p);
    lblTicker->setAnchorPoint(p);
}

void Ticker::setColor(Color3B c)
{
//    this->setColor(c);
    lblTicker->setColor(c);
}
void Ticker::setVisible(bool value)
{
    //    this->setColor(c);
    lblTicker->setVisible(value);
}