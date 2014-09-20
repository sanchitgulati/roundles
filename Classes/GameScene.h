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
    Point _levelScale;
    Node* levelNode;
    Point origin;
    float fontSize;
    LayerColor* lbackground;
    
    //Player
    Player* _player;
    
    
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
    
    
    cocos2d::Node* createCCElement(LevelElement element);
    bool hasMoves();
    LevelElement getLevelElementAt(int x,int y);
    eType validMove(int x,int y);
    void storeMoveForUndo(LevelElement element, int head);
    
    void handleMove(int grid_x,int grid_y,int head);
    
    std::vector<LevelElement>::iterator captureElement(int x,int y);
    void updatePlayer(int x,int y,int head,float deltaTime);
    
    bool loadLevel(bool reset = false);
    void updateGame(bool init = false); //For Regular Checks
    
    //Util
    void deleteCCElementFromLevelNode(Node * sender,bool cleanup);
    Point getScreenCoordinates(int x,int y);
    void delCocos(Node* node);
    void toggleVisible(cocos2d::Node *node,bool value);
    
    
    float calculateDeltaTime(int x,int y);
    //End
    
    
    
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
};
#endif /* defined(__roundels__GameScene__) */
