//
//  OptionMenu.h
//  roundels
//
//  Created by Sanchit Gulati on 08/06/14.
//
//

#ifndef __roundels__LevelMenu__
#define __roundels__LevelMenu__

#include <iostream>

#include "cocos2d.h"
#include "Constants.h"
#include "LevelXML.h"
#include "Util.h"
#include "TableLevel.h"
#include "types/Button.h"
#include "types/Rectton.h"
#include "types/Header.h"
#include "types/Radio.h"

USING_NS_CC;

class LevelMenu : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCallback(cocos2d::Ref* pSender);
    
    
    //A Scheduler
    void update(float dt);
    
    //Variables
    Size visibleSize;
    Size winSize;
    Point origin;
    float fontSize;
    LayerColor* lbackground;
    
    
    
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
    CREATE_FUNC(LevelMenu);
};

#endif /* defined(__roundels__LevelMenu__) */
