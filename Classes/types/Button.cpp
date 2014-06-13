//
//  Button.cpp
//  roundels
//
//  Created by Sanchit Gulati on 08/06/14.
//
//

#include "Button.h"

USING_NS_CC;

enum {kZoomActionTag};

Button::Button(std::string text,std::string image,Color3B color)
{
    this->setEnabled(true);
    this->setAnchorPoint(Point(0.5f, 0.5f));

    this->lblText = Label::create(text, Constants::fontName, Constants::fontSize/2.0);
    this->foreSprite = Sprite::create(image);
    this->backSprite = Sprite::create(IMG_CIRCLE_WHITE);
    this->backSprite->setScale(Util::getScreenRatio(backSprite)*0.2);
    this->foreSprite->setScale(Util::getScreenRatio(foreSprite)*0.15);
    this->backSprite->setColor(color);
    this->lblText->setColor(RGB_COLOR5);
    
    _originalScale = this->getScale();
    
    auto sizeMenuItem = this->backSprite->getBoundingBox().size;
    this->setContentSize(sizeMenuItem);
    this->getBoundingBox().setRect(0, 0, sizeMenuItem.width, sizeMenuItem.height);
    
    this->addChild(backSprite);
    this->addChild(lblText);
    this->addChild(foreSprite);
    
    backSprite->setAnchorPoint(Point(0,0));
    foreSprite->setAnchorPoint(Point(0,0));
    foreSprite->setPosition(Point(sizeMenuItem.width/8.0f,sizeMenuItem.height/8.0f));
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
        }
        
        Action *zoomAction = ScaleTo::create(0.1f, _originalScale * 1.2f);
        zoomAction->setTag(kZoomActionTag);
        this->runAction(zoomAction);
    }
}

void Button::unselected()
{
    // subclass to change the default action
    if(_enabled)
    {
        MenuItem::unselected();
        this->stopActionByTag(kZoomActionTag);
        Action *zoomAction = ScaleTo::create(0.1f, _originalScale);
        zoomAction->setTag(kZoomActionTag);
        this->runAction(zoomAction);
    }
}

