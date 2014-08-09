//
//  OptButton.cpp
//  roundels
//
//  Created by Sanchit Gulati on 09/08/14.
//
//

#include "OptButton.h"
#include "Constants.h"
#include "Util.h"

enum {kZoomActionTag,kSlideActionTag};

OptButton* OptButton::create(std::string text)
{
    OptButton *pRet = new OptButton(text);
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


OptButton::OptButton(std::string text)
{
    setEnabled(true);
    auto localContent = LocalizedString::localizedString(text.c_str())->getCString();
    lblText = Label::create(localContent, Constants::fontName, Constants::fontSize*0.60);
    lblText->setAnchorPoint(Point(0.0f,0.0f));
    lblText->setColor(RGB_COLOR5);
    
    
    auto sizeMenuItem = lblText->getContentSize();
    this->setContentSize(sizeMenuItem);
    this->getBoundingBox().setRect(0, 0, sizeMenuItem.width, sizeMenuItem.height);
    
    _originalScale = this->getScale();
    _originalPosition = this->getPosition();
    
    
    this->addChild(lblText);
    
//    setCascadeColorEnabled(true);
//    setCascadeOpacityEnabled(true);
    
}

void OptButton::selected()
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

void OptButton::unselected()
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


void OptButton::setScale(float val)
{
    lblText->setScale(Util::getScreenRatio(lblText)*val);
}