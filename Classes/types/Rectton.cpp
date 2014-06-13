//
//  Rectton.cpp
//  roundels
//
//  Created by Sanchit Gulati on 08/06/14.
//
//

#include "Rectton.h"

USING_NS_CC;

enum{kZoomActionTag};

Rectton::Rectton(std::string text,Color3B color)
{
    this->setEnabled(true);
    _originalScale = 0;
    this->setAnchorPoint(Point(0.5f, 0.5f));
    
    this->lblText = Label::create(text, Constants::fontNameBold, Constants::fontSize/2.0);
    
    this->backSprite = Sprite::create(IMG_BUTTON_WHITE);
    this->backSprite->setScale(Util::getScreenRatio(backSprite)*0.4);
    
    this->backSprite->setColor(color);
    auto sizeMenuItem = this->backSprite->getBoundingBox().size;
    
    this->setContentSize(sizeMenuItem);
    this->getBoundingBox().setRect(0, 0, sizeMenuItem.width, sizeMenuItem.height);
    this->setScale(Util::getScreenRatio(backSprite)*0.4);
    
    _originalScale = this->getScale();
    
    this->lblText->setColor(RGB_COLOR6);
    
    
    this->backSprite->setAnchorPoint(Point(0.0f,0.0f));
    this->lblText->setPosition(Point(sizeMenuItem.width/8.0f,sizeMenuItem.height/8.0f ));
    this->lblText->setAnchorPoint(Point(0.0f, 0.0f));
    
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

void Rectton::selected()
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

void Rectton::unselected()
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


