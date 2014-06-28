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
public:
    int x;
    int y;
    int head;
    Player(const char* image);
    cocos2d::Sprite* sprite;
    cocos2d::Sprite* innerSprite;
    cocos2d::Sprite* light;
    cocos2d::Sprite* arrow;
    int totalElements;
    int capturedElements;
    
    
    virtual bool init();
    static Player* create(const char* image);
    void setScale(float);
    void setTotalElements(int);
    bool capture(int type,int direction,float animationDelta);
    bool setHead(int direction);
};
#endif /* defined(__roundels__Player__) */
