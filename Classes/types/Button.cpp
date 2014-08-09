//
//  Button.cpp
//  roundels
//
//  Created by Sanchit Gulati on 08/06/14.
//
//

#include "Button.h"

USING_NS_CC;

enum {kZoomActionTag,kSlideActionTag};

Button::Button(std::string text,std::string image,Color3B color)
{
    this->setEnabled(true);
    this->setAnchorPoint(Point(0.5f, 0.5f));
    
    auto localContent = LocalizedString::localizedString(text.c_str())->getCString();
    this->lblText = Label::create(localContent, Constants::fontName, Constants::fontSize/2.0);
    this->foreSprite = Sprite::create(image);
    this->foreSprite->setScale(Util::getScreenRatio(foreSprite)*0.15);
    this->lblText->setColor(RGB_COLOR5);
    this->foreSprite->setColor(RGB_COLOR5);
    
    _originalScale = this->getScale();
    _originalPosition = this->getPosition();
    
    auto sizeMenuItem = this->foreSprite->getBoundingBox().size;
    this->setContentSize(sizeMenuItem);
    this->getBoundingBox().setRect(0, 0, sizeMenuItem.width, sizeMenuItem.height);
    
    this->addChild(lblText);
    this->addChild(foreSprite);
    
    auto shadowCorrection = 0;
    
    foreSprite->setPosition(Point(sizeMenuItem.width/2.0f - shadowCorrection,sizeMenuItem.height/2.0f + shadowCorrection));
    this->lblText->setAnchorPoint(Point(0.0f, 1.0f));
    this->lblText->setPositionY(-1* sizeMenuItem.height*0.10);
    this->lblText->setPositionX(sizeMenuItem.width*0.50 - (lblText->getContentSize().width/2.0f));
    
    setCascadeColorEnabled(true);
    setCascadeOpacityEnabled(true);
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

void Button::selected()
{
    // subclass to change the default action
    if(_enabled)
    {
        MenuItem::selected();
        
        Action *action = getActionByTag(kZoomActionTag);
        if (action)
        {
            this->stopAction(action);
        }
        else
        {
            _originalScale = this->getScale();
            _originalPosition = this->getPosition();
        }
        
        auto slideDistance = this->getBoundingBox().size.height/16.0f;
        Action *zoomAction = ScaleTo::create(0.2f, _originalScale * 0.95f);
        zoomAction->setTag(kZoomActionTag);
        Action *slideAction = MoveBy::create(0.1f, Point(0, -1*slideDistance));
        slideAction->setTag(kSlideActionTag);
        this->runAction(zoomAction);
        this->runAction(slideAction);
    }
}

void Button::unselected()
{
    // subclass to change the default action
    if(_enabled)
    {
        MenuItem::unselected();
        this->stopActionByTag(kZoomActionTag);
        this->stopActionByTag(kSlideActionTag);
        Action *zoomAction = ScaleTo::create(0.1f, _originalScale);
        zoomAction->setTag(kZoomActionTag);
        this->runAction(zoomAction);
        
        Action *slideActionReverse = MoveTo::create(0.05f, _originalPosition);
        this->runAction(slideActionReverse);
    }
}


void Button::setScale(float val)
{
    this->foreSprite->setScale(Util::getScreenRatio(foreSprite)*val);
//    this->setScale(Util::getScreenRatio(foreSprite)*val);
}
