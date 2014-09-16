#ifndef __MAINMENU_SCENE_H__
#define __MAINMENU_SCENE_H__

#include "cocos2d.h"
#include "Constants.h"
#include "LevelXML.h"
#include "Util.h"

#include "types/types.h"

USING_NS_CC;

class MainMenu : public cocos2d::Layer
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
    
    //Bundle Related
    Node* bundleNode;
    float step;
    //Pointers to Everything
    ccArray *arrBundle;
    
    //Selected Gameplay
    int selectedBundle;
    
    //Menu Pointers
    Rectton* btnPlay;
    Label* lblGameName;
    
    //touch delegated
    bool onTouchBegan(Touch* touch, Event  *event);
    void onTouchEnded(Touch* touch, Event  *event);
    void onTouchMoved(Touch* touch, Event  *event);
    void onTouchCancelled(Touch* touch, Event  *event);
    
    //touch handlers
    Point touchStart;
    void swipeLeft(Point location);
    void swipeRight(Point location);
    void swipeUp(Point location);
    void swipeDown(Point location);
    
    void changeGameNameLetterColor();
    void changePlayRecttonText();
    
    // implement the "static create()" method manually
    CREATE_FUNC(MainMenu);
};
#endif // __HELLOWORLD_SCENE_H__
