//
//  Rotator.cpp
//  roundels
//
//  Created by Sanchit Gulati on 10/06/14.
//
//

#include "Rotator.h"
#include "Constants.h"
#include "Util.h"

using namespace cocos2d;
enum {kZoomActionTag,kSlideActionTag};

Rotator* Rotator::create(std::string img,Color3B color,std::string text,float percentage,bool locked)
{
    Rotator *pRet = new Rotator(img,color,text,percentage,locked);
    if (pRet && pRet->init())
    {
        pRet->setEnabled(true);
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

Rect Rotator::getBoundingBox()
{
    return outer->getBoundingBox();
}


Rotator::Rotator(std::string img,Color3B color,std::string text,float percentage,bool locked)
{
    setEnabled(true);
    outer = ProgressTimer::create(Sprite::create(img));
    outer->setType( ProgressTimer::Type::RADIAL );
    inner = Sprite::create(img);
    setAnchorPoint(Point(0.5,0.5));
    outer->setAnchorPoint(Point(0.5,0.5));
    inner->setAnchorPoint(Point(0.5,0.5));
    
    
    outer->setColor(color);
//    inner->setColor(color);
    
    outer->setScale(Util::getScreenRatioWidth(outer)*0.70);
    
    outer->setOpacity(0);
    
    inner->setScale(Util::getScreenRatioWidth(inner)*0.65);
    
    
    auto delayTime = DelayTime::create(0.2);
    auto fadeIn = FadeTo::create(0.1, GAME_OPACITY);
    auto progressTo = ProgressTo::create(2*VFX_CONSTANT, 50);
    outer->runAction(Sequence::create(delayTime,fadeIn,progressTo, NULL));
    
    auto action = RepeatForever::create(
                                        Sequence::create(
                                                         ScaleBy::create(3,1.10),
                                                         ScaleBy::create(3,1.10)->reverse(),
                                                         NULL)
                                        );
    
    outer->runAction( action);
    
    inner->runAction( action->clone());
    
    
    this->addChild(outer);
    this->addChild(inner);
    
    _originalScale = this->getScale();
    _originalPosition = this->getPosition();
    auto sizeMenuItem = inner->getBoundingBox().size;
    sizeMenuItem.width /= 2;
    sizeMenuItem.height/= 2;
    this->setContentSize(sizeMenuItem);
    this->getBoundingBox().setRect(0, 0, sizeMenuItem.width, sizeMenuItem.height);
    inner->setPosition(sizeMenuItem.width/2,sizeMenuItem.height/2);
    outer->setPosition(sizeMenuItem.width/2,sizeMenuItem.height/2);
    
    
    if(locked)
    {
        auto lock = Sprite::create(IMG_LOCK);
        lock->setScale((inner->getBoundingBox().size.height/lock->getBoundingBox().size.height)*0.30);
        lock->runAction(action->clone());
        lock->setPosition(sizeMenuItem.width/2,sizeMenuItem.height/2);
        this->addChild(lock);
    }
    else
    {
        
        auto localContent = LocalizedString::localizedString(text.c_str())->getCString();
        auto textLbl = Label::createWithTTF(localContent, Constants::fontName, Constants::fontSize);
        textLbl->setAnchorPoint(Point(0.5,0.5));
        textLbl->setColor(RGB_COLOR1);
        textLbl->getTexture()->setAliasTexParameters();
        textLbl->runAction(action->clone());
        textLbl->setPosition(sizeMenuItem.width/2,sizeMenuItem.height/2);
        this->addChild(textLbl);
        
        
    }
    
//    auto dn = DrawNode::create();
//    dn->drawDot(getPosition(), 30, Color4F::BLUE);
//    this->addChild(dn,99);
    
    setCascadeColorEnabled(true);
    setCascadeOpacityEnabled(true);
}



void Rotator::animateRotation(float val,float time)
{
    auto& children = this->getChildren();
    for(const auto &child : children)
    {
        child->runAction(Sequence::create(RotateBy::create(time, val),NULL));
    }
}

void Rotator::setRotation(float val)
{
    auto& children = this->getChildren();
    for(const auto &child : children)
    {
        child->setRotation(val);
    }
}


void Rotator::selected()
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

void Rotator::unselected()
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

//
//void Rotator::setScale(float val)
//{
//    this->inner->setScale(Util::getScreenRatio(foreSprite)*val);
//}
