//
//  GameScene.h
//  roundels
//
//  Created by Sanchit Gulati on 15/06/14.
//
//

#ifndef __roundels__GameScene__
#define __roundels__GameScene__

#include <iostream>

#include "cocos2d.h"
#include "Constants.h"
#include "LevelXML.h"
#include "Util.h"
#include "TableLevel.h"

#include "types/types.h"

USING_NS_CC;


class GameScene: public cocos2d::Layer
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
    float _size;
    Node* levelNode;
    Point origin;
    float fontSize;
    LayerColor* lbackground;
    int _topCircle;
    bool isAnimation;
    Sprite* scaleSprite;
    //Player
    Player* player;
    
    //Buttons
    Sideton* btnUndo;
    
    //Level
    std::vector<LevelElement> level;
    std::vector<LevelElement> moves;
    std::vector<int> solution;
    
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
    
    LevelElement getLevelElementAt(int x,int y,bool del = false,int head = -1);
    bool captureElementAndAnimate(int x,int y,int direction);
    bool checkMoves();
    bool checkMove(int x,int y);
    void deleteCCElementFromLevelNode(Node * sender,bool cleanup);
    Point getScreenCoordinates(int x,int y);
    cocos2d::Node* createElement(LevelElement element);
    
    bool loadLevel(bool reset = false);
    
    void updateGame();
    
    void delCocos(Node* node);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
};
#endif /* defined(__roundels__GameScene__) */
