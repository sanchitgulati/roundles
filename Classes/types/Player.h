//
//  Player.h
//  roundels
//
//  Created by Sanchit Gulati on 15/06/14.
//
//

#ifndef __roundels__Player__
#define __roundels__Player__

#include <iostream>
#include "cocos2d.h"

class Player : public cocos2d::Node
{
protected:
    int x;
    int y;
    int head;
    cocos2d::Sprite* sprite;
    cocos2d::Sprite* innerSprite;
    cocos2d::Sprite* arrow;
    int totalElements;
    int capturedElements;
    int _animationsRunning;
    int _moves;
    
    cocos2d::CallFunc* _started;
    cocos2d::CallFunc* _done;
    
public:
    virtual bool init();
    Player();
    static Player* create();
    
    
    //Getter's and Setter's
    int getX();
    int getY();
    int getMoves();
    void setMoves(int val);
    void setGridPosition(int x,int y);
    void setHead(int direction);
    void setScale(float value);
    void setTotalElements(int value);
    void setCapturedElements(int delta = 1);
    bool canMove(int direction);
    
    //Animations
    void moveAnimation(int screen_x,int screen_y,float deltaTime);
    void rotateHead(int head,float deltaTime);
    void expandSoul(float deltaTime);
    void contractSoul(float deltaTime);
    
    
    //Util
    
    void animationStarted(Node * sender);
    void animationDone(Node * sender);
    
    

};
#endif /* defined(__roundels__Player__) */
