//
//  Radio.cpp
//  roundels
//
//  Created by Sanchit Gulati on 09/06/14.
//
//

#include "Roundles.h"
#include "Constants.h"
#include "Util.h"

USING_NS_CC;
enum {kZoomActionTag,kSlideActionTag};

Roundles::Roundles(std::string heading,std::string message)
{
    this->setEnabled(true);
    this->setAnchorPoint(Point(0.0f, 0.0f));
    
    //localization
    auto localContent = LocalizedString::localizedString(heading.c_str())->getCString();
    auto localContentMessage = LocalizedString::localizedString(message.c_str())->getCString();
    //end
    
    lblText = Label::create(localContentMessage, Constants::fontName, Constants::fontSize*0.50);
    lblText->setAnchorPoint(Point(0.5f,0.5f));
    lblText->setColor(RGB_COLOR7);
    
    
    lblHeading = Label::create(localContent, Constants::fontName, Constants::fontSize*0.50);
    lblHeading->setAnchorPoint(Point(0.5f,0.5f));
    lblHeading->setColor(RGB_COLOR5);
    
    circleLeft = Sprite::create(IMG_CIRCLE_WHITE);
    circleLeft->setScale(Util::getScreenRatio(circleLeft)*0.15);
    
    circleRight = Sprite::create(IMG_CIRCLE_TWITTER);
    circleRight->setScale(Util::getScreenRatio(circleRight)*0.15);
    
    bar = Sprite::create(IMG_RECT_WHITE);
    bar->setScaleY(Util::getScreenRatio(bar)*0.15);
    bar->setScaleX((lblText->getContentSize().width + circleLeft->getBoundingBox().size.width*0.50)/bar->getBoundingBox().size.width);

    
    
    
    auto barSize = bar->getBoundingBox().size;
    
    circleLeft->setPositionX(-1*(barSize.width/2.0f));
    circleRight->setPositionX(1*(barSize.width/2.0f));
    
    
    lblHeading->setPositionY(1*lblText->getContentSize().height*0.5);
    lblText->setPositionY(-1*lblText->getContentSize().height*0.5);
    
    
    lblHeading->setPositionX(-1*circleLeft->getBoundingBox().size.width*0.50);
    lblText->setPositionX(-1*circleLeft->getBoundingBox().size.width*0.50);

    
    circleLeft->setColor(RGB_COLOR4);
    bar->setColor(RGB_COLOR4);
    
    
    _originalScale = this->getScale();
    _originalPosition = this->getPosition();
    
    
    auto sizeMenuItem = this->bar->getBoundingBox().size;
    sizeMenuItem.width += circleRight->getBoundingBox().size.width*2;
    this->setContentSize(sizeMenuItem);
    this->getBoundingBox().setRect(0, 0, sizeMenuItem.width, sizeMenuItem.height);
    
    
    this->addChild(circleLeft);
    this->addChild(bar);
    this->addChild(circleRight);
    this->addChild(lblText);
    this->addChild(lblHeading);
    
    setCascadeColorEnabled(true);
    setCascadeOpacityEnabled(true);
}



Roundles* Roundles::create(std::string heading,std::string message)
{
    Roundles *pRet = new Roundles(heading, message);
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

void Roundles::selected()
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

void Roundles::unselected()
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


