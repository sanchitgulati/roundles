//
//  Sideton.cpp
//  roundels
//
//  Created by Sanchit Gulati on 21/06/14.
//
//

#include "Sideton.h"

USING_NS_CC;

enum {kZoomActionTag,kSlideActionTag};

Sideton::Sideton(std::string text,std::string image,Color3B color)
{
    this->setAnchorPoint(Point(0.5f, 0.5f));
    
    this->foreSprite = Sprite::create(image);
    this->backSprite = Sprite::create(IMG_CIRCLE_BORDER);
    this->backSprite->setScale(Util::getScreenRatio(backSprite)*0.10);
    this->foreSprite->setScale(Util::getScreenRatio(foreSprite)*0.08);
    _originalColor = color;
    this->backSprite->setColor(color);
    
    _originalScale = this->getScale();
    _originalPosition = this->getPosition();
    
    auto sizeMenuItem = this->backSprite->getBoundingBox().size;
    this->setContentSize(sizeMenuItem);
    this->getBoundingBox().setRect(0, 0, sizeMenuItem.width, sizeMenuItem.height);
    
    this->addChild(backSprite);
    this->addChild(foreSprite);
    
    auto shadowCorrection = 0;// 8 * backSprite->getScale();
    
    backSprite->setAnchorPoint(Point(0,0));
    foreSprite->setPosition(Point(sizeMenuItem.width/2.0f - shadowCorrection,sizeMenuItem.height/2.0f + shadowCorrection));
    
    setCascadeColorEnabled(true);
    setCascadeOpacityEnabled(true);
}

Sideton* Sideton::create(std::string text,std::string image,Color3B color)
{
    Sideton *pRet = new Sideton(text,image,color);
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

void Sideton::selected()
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

void Sideton::unselected()
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

void Sideton::setEnabled(bool value)
{
    MenuItem::setEnabled(value);
    if(this->backSprite == nullptr)
        return;
    if(value == false)
        this->backSprite->setColor(Color3B::GRAY);
    else
        this->backSprite->setColor(_originalColor);
}
