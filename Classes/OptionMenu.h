//
//  OptionMenu.h
//  roundels
//
//  Created by Sanchit Gulati on 08/06/14.
//
//

#ifndef __roundels__OptionMenu__
#define __roundels__OptionMenu__

#include <iostream>

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "Constants.h"
#include "LevelXML.h"
#include "Util.h"

#include "types/types.h"

USING_NS_CC;

class OptionMenu : public cocos2d::Layer
{
protected:
    //Variables
    Size visibleSize;
    Size winSize;
    Point origin;
    float fontSize;
    LayerColor* lbackground;
    int selectedMenu;
    cocos2d::Node* container;
    int _total;
    std::vector<std::string> menuNames;
    Header* _header;
    
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCallback(cocos2d::Ref* pSender);
    
    
    //
    void refreshHeader();
    
    //A Scheduler
    void update(float dt);
    
    //callbacks
    
    
    void soundCallback(Ref* pSender,cocos2d::extension::Control::EventType controlEvent);
    void musicCallback(Ref* pSender,cocos2d::extension::Control::EventType controlEvent);
    void languageCallback(Ref* pSender);
    
    //touch delegated
    bool onTouchBegan(Touch* touch, Event  *event);
    void onTouchEnded(Touch* touch, Event  *event);
    void onTouchMoved(Touch* touch, Event  *event);
    void onTouchCancelled(Touch* touch, Event  *event);
    
    //touch handlers
    Point touchStart;
    void swipeLeft();
    void swipeRight();
    void swipeUp();
    void swipeDown();
    
    // implement the "static create()" method manually
    CREATE_FUNC(OptionMenu);
};

#endif /* defined(__roundels__OptionMenu__) */
