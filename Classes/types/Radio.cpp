//
//  Radio.cpp
//  roundels
//
//  Created by Sanchit Gulati on 09/06/14.
//
//

#include "Radio.h"
#include "Constants.h"
#include "Util.h"

USING_NS_CC;

Radio::Radio(std::string text)
{
    auto localContent = LocalizedString::localizedString(text.c_str())->getCString();
    lblText = Label::createWithTTF(localContent, Constants::fontName, Constants::fontSize*0.70);
    lblText->setAnchorPoint(Point(0.0f,0.5f));
    lblText->setColor(RGB_COLOR5);
    
    circle = Sprite::create(IMG_CIRCLE_WHITE);
    circle->setScale(Util::getScreenRatio(circle)*0.1);
    
    bar = Sprite::create(IMG_RECT_WHITE);
    bar->setScaleY(Util::getScreenRatio(bar)*0.1);
    bar->setScaleX(Util::getScreenRatio(bar)*0.70);
    
    
    on = MenuItemImage::create(IMG_CIRCLE_WHITE, IMG_CIRCLE_WHITE);
    off = MenuItemImage::create(IMG_CIRCLE_WHITE, IMG_CIRCLE_WHITE);
    
    
    on->setScale(Util::getScreenRatio(on)*0.125);
    off->setScale(Util::getScreenRatio(off)*0.125);
    
    auto barSize = bar->getBoundingBox().size;
    auto onoffsize = on->getBoundingBox().size;
    
    bar->setPositionX(-1*(barSize.width/2.0f) + (onoffsize.width/2.0));
    circle->setPositionX(-1*(barSize.width/1.0f)+ onoffsize.width/2.0);
    lblText->setPositionX(-1*(barSize.width/1.0f)+ (onoffsize.width/2.0));
    
    
    on->setPositionX(1*(barSize.width/1.0f));
    off->setPositionX(1*(barSize.width/1.0f));
    
    
    circle->setPositionY(onoffsize.height/2.0);
    bar->setPositionY(onoffsize.height/2.0);
    lblText->setPositionY(onoffsize.height/2.0);
    

    
    circle->setColor(RGB_COLOR4);
    bar->setColor(RGB_COLOR4);
    
    
    
    on->setColor(RGB_COLOR2);
    off->setColor(Color3B::GRAY);
    
    this->addChild(circle);
    this->addChild(bar);
    this->addChild(lblText);
    
    
    setCascadeColorEnabled(true);
    setCascadeOpacityEnabled(true);

}



Radio* Radio::create(std::string text)
{
    Radio *pRet = new Radio(text);
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

bool Radio::init()
{
    MenuItem::initWithCallback((const ccMenuCallback&)nullptr);
    
    _subItems.pushBack(on);
    _subItems.pushBack(off);
    _selectedIndex = UINT_MAX;
    this->setSelectedIndex(0);
    
    setCascadeColorEnabled(true);
    setCascadeOpacityEnabled(true);
    this->setEnabled(true);
    activate();
    
    return true;
}


/*
 Changing in cocos2dx
*/

/*
 
 void MenuItemToggle::setSelectedIndex(unsigned int index)
 {
 if( index != _selectedIndex && _subItems.size() > 0 )
 {
 _selectedIndex = index;
 MenuItem *currentItem = (MenuItem*)getChildByTag(kCurrentItem);
 if( currentItem )
 {
 currentItem->removeFromParentAndCleanup(false);
 }
 
 MenuItem* item = _subItems.at(_selectedIndex);
 this->addChild(item, 0, kCurrentItem);
 Size s = item->getBoundingBox().size;
 this->setContentSize(s);
 item->setPosition( Point( s.width/2, s.height/2 ) );
 }
 }
 
 
 */

