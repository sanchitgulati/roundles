//
//  Switch.cpp
//  roundels
//
//  Created by Sanchit Gulati on 09/08/14.
//
//

#include "Switch.h"
#include "Constants.h"
#include "Util.h"

USING_NS_CC;

Switch::Switch(std::string text,bool toggle)
{
    auto localContent = LocalizedString::localizedString(text.c_str())->getCString();
    lblText = Label::create(localContent, Constants::fontName, Constants::fontSize*0.60);
    lblText->setAnchorPoint(Point(0.0f,0.5f));
    lblText->setColor(RGB_COLOR5);
    
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto barSize = visibleSize.width*0.70;
    
    btnSwitch = cocos2d::extension::ControlSwitch::create(
     Sprite::create("images/switch-mask.png"),
     Sprite::create("images/switch-on.png"),
     Sprite::create("images/switch-off.png"),
     Sprite::create("images/switch-thumb.png"),
     LabelTTF::create("On", Constants::fontName, Constants::fontSize*0.40),
     LabelTTF::create("Off", Constants::fontName, Constants::fontSize*0.40)
     );
    
    
    btnSwitch->setScale(Util::getScreenRatioWidth(btnSwitch)*0.15);
    
    lblText->setPositionX(-1*(barSize/1.0f));
    
    
    this->addChild(lblText);
    this->addChild(btnSwitch);
    
    setCascadeColorEnabled(true);
    setCascadeOpacityEnabled(true);
    
}

void Switch::setOn(bool val)
{
    btnSwitch->setOn(val);
}

void Switch::addTargetWithActionForControlEvents(cocos2d::Ref *target, cocos2d::extension::Control::Handler action, cocos2d::extension::Control::EventType controlEvents)
{
    
    btnSwitch->addTargetWithActionForControlEvents(target, action, controlEvents);
}

Switch* Switch::create(std::string text,bool toggle)
{
    Switch *pRet = new Switch(text,toggle);
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